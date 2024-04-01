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


		#define SystemCoreClock 8000000
		#define WavebufferLength 2048
		#define waveDAC_Channel LL_DAC_CHANNEL_1
		#define waveFile "Colors.wav"
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
		uint16_t reverseShort (uint8_t *);
		uint32_t reverseInt (uint8_t *);
  
	// Initialization
		void SD_Card_Init(void);
		void wave_Init(void);
	
	//SD_Utility
	  void Print_SD_Card_space(void);		

  //Handling wave file
	void wave_open(char *);
	void wave_readHeader(void);
	void wave_read(void);
	void wave_play(char *);
	void wave_IsEndofFile(void);
	void wave_EndofFile_Callback(void);
	void wave_DMA_TC_Callback(void);
	void wave_DMA_HT_Callback(void);	
/********************************* END OF FILE ********************************/
/******************************************************************************/

