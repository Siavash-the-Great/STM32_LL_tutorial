/**
  ******************************************************************************
  * @file		WAV_Handler.c
  ******************************************************************************
  */  
		#include "WAV_Handler.h"

/********************/
/********///variables:

	uint8_t headerBuffer[60];						// to read the header	
	uint8_t wavBuffer[WavebufferLength];		  	// DMA buffer
	/* capacity related variables */

	volatile uint8_t BufferAction = 0;				// indicator to what buffer action is needed
	volatile bool EndofFile = false;				// indicator of the end of the file


/********************/
/********///Functions:

	
	/*********************** Initialization ***********************/	
	void wave_Init()
	{
		printf("Initializing wave player\n\r");	
		SD_Card_Init();
		LL_DAC_Enable(DAC, waveDAC_Channel1);			//Enable DAC channel 1
		LL_DAC_Enable(DAC, waveDAC_Channel2);			//Enable DAC channel 2
		Print_SD_Card_space();
	}

	/********************* opening and reading the WAV file *********************/
	//opening the file
	bool wave_open(FIL *filptr, char *fileName)
	{
		FRESULT fr;     /* FatFs return code */
		fr = f_open(filptr, fileName, FA_READ);
		if(fr)
		{
			printf("Can not open the file\r\n -> %d \r\n", fr);
			return false;
		}
		
		else
		{
			printf("Successfully opened the file\r\n");
			return true;
		}
	}

	//reading and parsing the Header of the WAV file	
	bool wave_readHeader(FIL *filptr, wave_header_t *wav1HeaderPtr, volatile uint32_t **DACRegADS, uint32_t *DMA_DataLength)
	{
		FRESULT fr;     /* FatFs return code */
		UINT br;		//file read
		fr = f_read(filptr, headerBuffer, sizeof(headerBuffer), &br);

		if(fr)
		{
			printf("Can not read header of the file\r\n -> %d \r\n", fr);
			while(true);
		}
		
		else
		{
			printf("reading the file..\r\n");
			//setting the wav1's Header variables:
			//The "RIFF" chunk and The "fmt" sub-chunk descriptors
			memcpy(&wav1HeaderPtr->signatureHeader, headerBuffer, sizeof(wave_header_t1));
			//The "data" sub-chunk
			memcpy(&wav1HeaderPtr->dataHeader,
						 &headerBuffer[wav1HeaderPtr->signatureHeader.Subchunk1Size + 16 + 4],
						 sizeof(wave_header_t2));


		
			if( (strncmp(wav1HeaderPtr->signatureHeader.ChunkID, "RIFF", 4) != 0) ||  (strncmp(wav1HeaderPtr->signatureHeader.Format , "WAVE", 4) != 0) ){
				return false;
			}
			else
			{
				// set read/write pointer after the header information to read data 
				uint16_t headerEnd = 16 + wav1HeaderPtr->signatureHeader.Subchunk1Size + 12;		// pointer to the end of header of wav file	
				fr = f_lseek(filptr, headerEnd);
				fr = f_read(filptr, wavBuffer, WavebufferLength, &br);

			
			
				/******************* Determine DMA transfer data length, addrees of DAC register and 
				* memory/peripheral data alignment, based on bits per sample & Number of channels */
				uint32_t waveBitPerSampleM, waveBitPerSampleP;	// bits per sample for setting Memory and Peripheral
				if((wav1HeaderPtr->signatureHeader.BitsPerSample == 8) && (wav1HeaderPtr->signatureHeader.NumChannels == 1))
				{
					*DACRegADS = &DAC1->DHR8R1;
					waveBitPerSampleM = LL_DMA_MDATAALIGN_BYTE;
					waveBitPerSampleP = LL_DMA_PDATAALIGN_BYTE;
					*DMA_DataLength = WavebufferLength;
				}
				else if((wav1HeaderPtr->signatureHeader.BitsPerSample == 16) && (wav1HeaderPtr->signatureHeader.NumChannels == 1))
				{
					*DACRegADS = &DAC1->DHR12L1;
					waveBitPerSampleM = LL_DMA_MDATAALIGN_HALFWORD;
					waveBitPerSampleP = LL_DMA_PDATAALIGN_HALFWORD;
					*DMA_DataLength = WavebufferLength / 2;
				}
				else if((wav1HeaderPtr->signatureHeader.BitsPerSample == 8) && (wav1HeaderPtr->signatureHeader.NumChannels == 2))
				{
					*DACRegADS = &DAC1->DHR8RD;;
					waveBitPerSampleM = LL_DMA_MDATAALIGN_HALFWORD;
					waveBitPerSampleP = LL_DMA_PDATAALIGN_HALFWORD;
					*DMA_DataLength = WavebufferLength / 2;
				}
				else if((wav1HeaderPtr->signatureHeader.BitsPerSample == 16) && (wav1HeaderPtr->signatureHeader.NumChannels == 2))
				{
					*DACRegADS = &DAC1->DHR12LD;
					waveBitPerSampleM = LL_DMA_MDATAALIGN_WORD;
					waveBitPerSampleP = LL_DMA_PDATAALIGN_WORD;
					*DMA_DataLength = WavebufferLength / 4;
				}
			
			
				//set DMA  Data width for peripheral and memory according to Bits per Sample of the file
				LL_DMA_SetPeriphSize(waveDMA, waveDMA_Channel, waveBitPerSampleP);
				LL_DMA_SetMemorySize(waveDMA, waveDMA_Channel, waveBitPerSampleM);		

			
				/**** print properties of the wav file, extracted from the header ****/
//				printf("file ID: %s\r\n", wav1ptr->ChunkID);
//				printf("file format: %s\r\n", wav1ptr->Format);
				printf("number of bytes in the file(header excluded): %x\r\n", wav1HeaderPtr->dataHeader.Subchunk2Size);
				printf("number of channels: %d\r\n", wav1HeaderPtr->signatureHeader.NumChannels);
				printf("sample rate: %d\r\n", wav1HeaderPtr->signatureHeader.SampleRate);
				printf("byte rate: %d\r\n", wav1HeaderPtr->signatureHeader.ByteRate);
				printf("bits per sample: %d\r\n", wav1HeaderPtr->signatureHeader.BitsPerSample);
				printf("data ID: %c%c%c%c\r\n", wav1HeaderPtr->dataHeader.Subchunk2ID[0],
						 	 wav1HeaderPtr->dataHeader.Subchunk2ID[1],
							 wav1HeaderPtr->dataHeader.Subchunk2ID[2],
							 wav1HeaderPtr->dataHeader.Subchunk2ID[3]);
				printf("DMA_DataLength: %d\r\n\n", *DMA_DataLength);
				return true;
			}
	 
		}
	}

	/********************* Handling the playing of the WAV file *********************/	
	void wave_read(FIL *filptr, uint8_t *wavBuffer, volatile uint32_t *DACRegADS, uint32_t DMA_DataLength)
	{

		
		/********************** configuring DMA **********************/
		LL_DMA_ConfigAddresses(waveDMA,
                         waveDMA_Channel,
                         (uint32_t)wavBuffer,
						 (uint32_t) DACRegADS,
                         LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
												 
		LL_DMA_SetDataLength(waveDMA, waveDMA_Channel, 
							DMA_DataLength);		
												 
		LL_DMA_EnableIT_TC(waveDMA, waveDMA_Channel);
		LL_DMA_EnableIT_HT(waveDMA, waveDMA_Channel);
		LL_DMA_EnableIT_TE(waveDMA, waveDMA_Channel);
		LL_DMA_EnableChannel(waveDMA, waveDMA_Channel);	

		LL_DAC_EnableDMAReq(DAC, LL_DAC_CHANNEL_1);
											
		/********************** initializing timer2 **********************/	
		LL_TIM_EnableCounter(waveTimer);
		LL_TIM_EnableUpdateEvent(waveTimer);
	}
	
	void wave_setSampleRate(uint32_t SampleRate)		//set Timer update frequency according to SampleRate of the file
	{
		LL_TIM_InitTypeDef TIM_InitStruct = {0};

		TIM_InitStruct.Prescaler = (SystemCoreClock/1000000) - 1;
		TIM_InitStruct.Autoreload = (SystemCoreClock / ((TIM_InitStruct.Prescaler + 1) * SampleRate) ) - 1;
		LL_TIM_Init(waveTimer, &TIM_InitStruct);		
	}


	
	void wave_IsEndofFile(FIL *filptr, uint8_t *wavBuffer, uint16_t BitsPerSample)
	{
		UINT br;		//file read
//		if(BufferAction == 0)

		
		if(BufferAction==3)						//if both of DMA HT and TC buffer action flags have risen before one of them is cleared
		{
			printf("Low reading\r\n");
		}
		
		if(BufferAction&0x1)					//in case of DMA HT buffer action flag have risen
		{
			br = 0;
			f_read(filptr, wavBuffer, WavebufferLength / 2, &br);		//first half of the wavbuffer must be updated	
			if(BitsPerSample == 16)	//if bits per sample is 16 (else it's 8)
			{	
				for(uint16_t i = 1;  i<WavebufferLength/2;  i += 2)
				{
					wavBuffer[i] ^= 0x80;									//required for 16 bits per sample mode
				}
			}			
			BufferAction &=~0x1;				//Clear the buffer action flag
			if(br<WavebufferLength/2)
			{
				EndofFile = true;
			}
		}
		
		if(BufferAction&0x2)					//in case of DMA TC buffer action flag have risen
		{
			br = 0;
			f_read(filptr, wavBuffer + (WavebufferLength / 2), WavebufferLength / 2, &br);	//second half of the wavbuffer must be updated			
			if(BitsPerSample == 16)		//if bits per sample is 16 (else it's 8)	
			{
				for(uint16_t i = WavebufferLength/2 + 1;  i<WavebufferLength;  i += 2)
				{
					wavBuffer[i] ^= 0x80;									//required for 16 bits per sample mode
				}
			}			
			BufferAction &=~0x2;				//Clear the buffer action flag
			if(br<WavebufferLength/2)			//to indicate end of the file
			{
				EndofFile = true;
			}
		}	
	}
	
	void wave_play(char *fileName)
	{

		FIL fil;      						    /* File object */
		/* wave handling variables */
		wave_header_t wavHeader1;						//struct a new header		

		volatile uint32_t *DACRegADS = &DAC1->DHR8R1;	// Address of DAC register
		uint32_t DMA_DataLength;						// Data length of DMA transfer
		bool isWAV = false;
		wave_Init();
		if(!wave_open(&fil, fileName)){
			while(1);
		}
		isWAV = wave_readHeader(&fil, &wavHeader1, &DACRegADS, &DMA_DataLength);
		
		if(isWAV){
		printf("playing the file... \r\n");	
		wave_setSampleRate(wavHeader1.signatureHeader.SampleRate);
		wave_read(&fil, wavBuffer, DACRegADS, DMA_DataLength);
		while(1)
		{
			wave_IsEndofFile(&fil, wavBuffer, wavHeader1.signatureHeader.BitsPerSample);	
		}
		}
		else{
			printf("file is not in WAV format!\r\n");
			while(true);
		}
	}
	
	
	void wave_EndofFile_Callback(void)
	{
		if(EndofFile)
		{
			LL_DMA_DisableChannel(waveDMA, waveDMA_Channel);
			BufferAction = 0;
		}
	}

	void wave_DMA_TC_Callback(void)
	{
		BufferAction |= 0x2;
	}
	
	void wave_DMA_HT_Callback(void)	
	{
		BufferAction |= 0x1;		
	}
	
/********************************* END OF FILE ********************************/
/******************************************************************************/

