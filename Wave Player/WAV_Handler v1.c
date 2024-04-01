/**
  ******************************************************************************
  * @file		WAV_Handler.c
  ******************************************************************************
  */  
		#include "WAV_Handler.h"

/********************/
/********///variables:

	/* file handling variables */
	FATFS FatFs;		/* File system */
	FIL fil;        /* File object */
	FRESULT fr;     /* FatFs return code */
	FILINFO filinf;	/* File info object */
	
	UINT br, bw;		//file read/write count
	
	/* capacity related variables */
	FATFS *pfs;
	DWORD fre_clust;
	float total, free_space;
	
	/* wave handling variables */
	struct Wave_file wav1;
	uint8_t headerBuffer[60];					  	// to read the header
	uint8_t wavBuffer[WavebufferLength];		  	// DMA buffer
	uint8_t tempBuffer[WavebufferLength/2];		  	// temporary buffer to reverse Endianness
	volatile uint32_t *DACRegADS = &DAC1->DHR8R1;	// Address of DAC register
	uint32_t waveBitPerSampleM, waveBitPerSampleP;	// bits per sample for setting Memory and Peripheral data alignment
	uint32_t DMA_DataLength;						// Data length of DMA transfer
	volatile uint32_t playCount;					// to count number of bytes remaining to read
	uint8_t BytesPS = 1;							// Bytes per sample
	uint16_t headerEnd = 0;							// pointer to the end of header of wav file
	volatile uint8_t BufferAction = 0;				// indicator to what buffer action is needed
	volatile bool EndofFile = false;				// indicator of the end of the file


/********************/
/********///Functions:
	
		/*********************** Utility ***********************/	
	// to convert arrays to int
	uint16_t array2Short (uint8_t *c) {
			return c[1] * 256 + c[0];
	}

	uint32_t array2Int (uint8_t *c) {
			return ((c[3] * 16777216) + (c[2] * 65536) + (c[1] * 256) + c[0]);
	}
	
		/*********************** Initialization ***********************/	
	void wave_Init(void)
	{
		printf("Initializing wave player\n\r");	
		SD_Card_Init();
		LL_DAC_Enable(DAC, waveDAC_Channel1);			//Enable DAC channel 1
		LL_DAC_Enable(DAC, waveDAC_Channel2);			//Enable DAC channel 2
		Print_SD_Card_space();
	}

	void SD_Card_Init(void)
	{
		SysTick_Config(SystemCoreClock / 1000);
		LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
		LL_SYSTICK_EnableIT();
		
		int stat = 	f_mount(&FatFs, "", 0);
		if(stat)
			printf("failed to mount the SD Card \r\n");
		else
			printf("successfully mounted the SD Card\r\n");

		stat = disk_initialize(0);
		printf("initialization status: %d\r\n", stat);
	}
	
	/*********************** Card capacity details ***********************/	
	void Print_SD_Card_space(void)
	{	
	/* Check storage size and free space */
	f_getfree("0:", &fre_clust, &pfs);
		
	total = (float)((pfs->n_fatent - 2) * pfs->csize  * 0.5  / (1024));
	printf("SD CARD Total Size: \t%.2f Mega Bytes\r\n", total);


	free_space = (float)(fre_clust * pfs->csize  * 0.5 / (1024));
	printf("SD CARD Free SPACE: \t%.2f Mega Bytes\r\n", free_space);
	}

	/********************* opening and reading the WAV file *********************/
	//opening the file
	void wave_open(char *fileName)
	{
		fr = f_open(&fil, fileName, FA_READ);
		if(fr)
		{
			printf("Can not open the file\r\n -> %d \r\n", fr);
			while(true);
		}
		
		else
		{
			printf("Successfully opened the file\r\n");
			fr = f_stat(fileName, &filinf);
		}
	}

	//reading and parsing the Header of the WAV file	
	void wave_readHeader(void)
	{
		fr = f_read(&fil, headerBuffer, sizeof(headerBuffer), &br);

		if(fr)
		{
			printf("Can not read the file\r\n -> %d \r\n", fr);
			while(true);
		}
		
		else
		{
			printf("reading the file..\r\n");
			uint8_t temp[4];	//auxiliary variable for setting the wav1 variables
		
			//setting the wav1 variables:
				//The "RIFF" chunk descriptor
			memcpy(wav1.ChunkID, &headerBuffer[0], 4);
			memcpy(temp, &headerBuffer[4], 4);
			wav1.ChunkSize = array2Int(temp);
			memcpy(wav1.Format, &headerBuffer[8], 4);
				//The "fmt" sub-chunk	
			memcpy(wav1.Subchunk1ID, &headerBuffer[12], 4);
			memcpy(temp, &headerBuffer[16], 4);
			wav1.Subchunk1Size = array2Int(temp);
			memcpy(temp, &headerBuffer[20], 2);
			wav1.AudioFormat = array2Short(temp);	
			memcpy(temp, &headerBuffer[22], 2);
			wav1.NumChannels = array2Short(temp);	
			memcpy(temp, &headerBuffer[24], 4);
			wav1.SampleRate = array2Int(temp);
			memcpy(temp, &headerBuffer[28], 4);
			wav1.ByteRate = array2Int(temp);	
			memcpy(temp, &headerBuffer[32], 2);
			wav1.BlockAlign	= array2Short(temp);	
			memcpy(temp, &headerBuffer[34], 2);
			wav1.BitsPerSample = array2Short(temp);	
				//The "data" sub-chunk
			memcpy(wav1.Subchunk2ID, &headerBuffer[16 + wav1.Subchunk1Size + 4], 4);
			memcpy(temp, &headerBuffer[16 + wav1.Subchunk1Size + 8], 4);
			wav1.Subchunk2Size	= array2Int(temp);	

			
			headerEnd = 16 + wav1.Subchunk1Size + 12;
			
			/******************* Determine DMA transfer data length, addrees of DAC register and 
			* memory/peripheral data alignment, based on bits per sample & Number of channels */
			if((wav1.BitsPerSample == 8) && (wav1.NumChannels == 1))
			{
				DACRegADS = &DAC1->DHR8R1;
				waveBitPerSampleM = LL_DMA_MDATAALIGN_BYTE;
				waveBitPerSampleP = LL_DMA_PDATAALIGN_BYTE;
				DMA_DataLength = WavebufferLength;
			}
			else if((wav1.BitsPerSample == 16) && (wav1.NumChannels == 1))
			{
				DACRegADS = &DAC1->DHR12L1;
				waveBitPerSampleM = LL_DMA_MDATAALIGN_HALFWORD;
				waveBitPerSampleP = LL_DMA_PDATAALIGN_HALFWORD;
				DMA_DataLength = WavebufferLength / 2;
			}
			else if((wav1.BitsPerSample == 8) && (wav1.NumChannels == 2))
			{
				DACRegADS = &DAC1->DHR8RD;;
				waveBitPerSampleM = LL_DMA_MDATAALIGN_HALFWORD;
				waveBitPerSampleP = LL_DMA_PDATAALIGN_HALFWORD;
				DMA_DataLength = WavebufferLength / 2;
			}
			else if((wav1.BitsPerSample == 16) && (wav1.NumChannels == 2))
			{
				DACRegADS = &DAC1->DHR12LD;
				waveBitPerSampleM = LL_DMA_MDATAALIGN_WORD;
				waveBitPerSampleP = LL_DMA_PDATAALIGN_WORD;
				DMA_DataLength = WavebufferLength / 4;
			}
			
			/**** print properties of the wav file, extracted from the header ****/
			printf("number of bytes in the file(header excluded): %x\r\n", wav1.Subchunk2Size);
			printf("number of channels: %d\r\n", wav1.NumChannels);
			printf("sample rate: %d\r\n", wav1.SampleRate);
			printf("byte rate: %d\r\n", wav1.ByteRate);
			printf("bits per sample: %d\r\n", wav1.BitsPerSample);
			printf("data ID: %c%c%c%c\r\n", wav1.Subchunk2ID[0],wav1.Subchunk2ID[1],wav1.Subchunk2ID[2],wav1.Subchunk2ID[3]);
			printf("DMA_DataLength: %d\r\n\n", DMA_DataLength);
			BytesPS = wav1.BitsPerSample / 8;
		}
	 
	}

	/********************* Handling the playing of the WAV file *********************/	
	void wave_read(void)
	{
		// set read/write pointer after the header information to read data 
		fr = f_lseek(&fil, headerEnd);
		fr = f_read(&fil, wavBuffer, WavebufferLength, &br);
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

		printf("playing the file...\r\n");
		LL_DAC_EnableDMAReq(DAC, LL_DAC_CHANNEL_1);
											
		/********************** initializing timer2 **********************/	
		LL_TIM_EnableCounter(waveTimer);
		LL_TIM_EnableUpdateEvent(waveTimer);
	}
	
	void wave_setSampleRate(void)							//set Timer update frequency according to SampleRate of the file
	{
		LL_TIM_InitTypeDef TIM_InitStruct = {0};

		TIM_InitStruct.Prescaler = (SystemCoreClock/1000000) - 1;
		TIM_InitStruct.Autoreload = (SystemCoreClock / ((TIM_InitStruct.Prescaler + 1) * wav1.SampleRate) ) - 1;
		LL_TIM_Init(waveTimer, &TIM_InitStruct);		
	}

	void wave_setBitsPerSample(void)						//set DMA  Data width for peripheral and memory according to Bits per Sample of the file
	{
		LL_DMA_SetPeriphSize(waveDMA, waveDMA_Channel, waveBitPerSampleP);
		LL_DMA_SetMemorySize(waveDMA, waveDMA_Channel, waveBitPerSampleM);		
	}
	
	void wave_play(char *fileName)
	{
		wave_open(fileName);
		wave_readHeader();
		wave_setSampleRate();
		wave_setBitsPerSample();
		wave_read();
	}
	
	void wave_IsEndofFile(void)
	{
//		if(BufferAction == 0)

		
		if(BufferAction==3)						//if both of DMA HT and TC buffer action flags have risen before one of them is cleared
		{
			printf("Low reading\r\n");
		}
		
		if(BufferAction&0x1)					//in case of DMA HT buffer action flag have risen
		{
			br = 0;
			f_read(&fil, wavBuffer, WavebufferLength / 2, &br);		//first half of the wavbuffer must be updated	
			if(wav1.BitsPerSample == 16)	//if bits per sample is 16 (else it's 8)
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
			f_read(&fil, wavBuffer + (WavebufferLength / 2), WavebufferLength / 2, &br);	//second half of the wavbuffer must be updated			
			if(wav1.BitsPerSample == 16)		//if bits per sample is 16 (else it's 8)	
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

