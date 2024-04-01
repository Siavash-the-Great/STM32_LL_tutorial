/**
  ******************************************************************************
  * @file		WAV_Handler.h
  ******************************************************************************
  */  




		#include <string.h>
		#include <stdio.h>
		#include <stdint.h>
		#include <stdbool.h>
		#include "stm32f1xx_ll_dac.h"
		#include "stm32f1xx_ll_cortex.h"
		#include "stm32f1xx_ll_dma.h"
		#include "stm32f1xx_ll_tim.h"
		#include "ff.h"
		#include "diskio.h"
		#include "stdio_usart1.h"


		#define SystemCoreClock 72000000
		#define waveTimer	TIM2
		#define WavebufferLength 2048								//DMA will transfer buffer of size 1KB to DAC
		#define waveDAC_Channel1 LL_DAC_CHANNEL_1
		#define waveDAC_Channel2 LL_DAC_CHANNEL_2		
		#define waveDMA	DMA2
		#define	waveDMA_Channel LL_DMA_CHANNEL_3
		#define waveFile "sin.wav"

/********************/
/********///WAV file structure:

struct Wave_file {
	//The "RIFF" chunk descriptor
   char			ChunkID[4];
   uint32_t		ChunkSize;
   char  		Format[4];
    //The "fmt" sub-chunk
   char			Subchunk1ID[4];
   uint32_t		Subchunk1Size;
   uint16_t		AudioFormat;
   uint16_t		NumChannels;
   uint32_t		SampleRate;
   uint32_t		ByteRate;
   uint16_t		BlockAlign;
   uint16_t		BitsPerSample; 
	//The "data" sub-chunk
	 char				Subchunk2ID[4];
	 uint32_t		Subchunk2Size;

}; 



/********************/
/********///Functions:
	
	// to reverse endianness
		uint16_t array2Short (uint8_t *);
		uint32_t array2Int (uint8_t *);

	// Initialization
//		void SD_Card_Init(FATFS *);
		void SD_Card_Init(void);
		void wave_Init(void);
	
	//SD_Utility
	  void Print_SD_Card_space(void);		

  //Handling wave file
	bool wave_open(FIL *, char *);
	bool wave_readHeader(FIL *, struct Wave_file *, volatile uint32_t **, uint32_t *);
	void wave_read(FIL *, uint8_t *, volatile uint32_t *, uint32_t);
	void wave_setSampleRate(uint32_t);
	void wave_IsEndofFile(FIL *, uint8_t *, uint16_t);
	void wave_play(char *);
	void wave_EndofFile_Callback(void);
	void wave_DMA_TC_Callback(void);
	void wave_DMA_HT_Callback(void);	
/********************************* END OF FILE ********************************/
/******************************************************************************/

