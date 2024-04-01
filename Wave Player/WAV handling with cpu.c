// WAV handling with cpu

	// set read/write pointer after the header information to read data 
  fr = f_lseek(&fil, headerEnd);


	while(play){
		if(playCount > 100){
			fr = f_read(&fil, readBuffer, BytesPS * 100, &br);
			fr = f_lseek(&fil, f_tell(&fil) + BytesPS * 100);
			for(int i = 0; i<100; i++){
				if(BytesPS == 2){
					sample = readBuffer[i+1] * 256 + readBuffer[i];
				}
				else if(BytesPS == 1){
					sample = readBuffer[i];
				}
				LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, sample*(0xfff)/((BytesPS == 2) ? 0xffff : 0xff));
				printf("current playing sample: %x\r\n", sample);
			}
			playCount -= 100;
			printf("just read 100 samples!\r\n\n");
		}
		else{
			fr = f_read(&fil, readBuffer, playCount, &br);
			for(int i = 0; i<playCount; i++){
				if(BytesPS == 2){
					sample = readBuffer[i+1] * 256 + readBuffer[i];
				}
				else if(BytesPS == 1){
					sample = readBuffer[i];
				}
				LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, sample*(0xfff)/((BytesPS == 2) ? 0xffff : 0xff));
				printf("current playing sample: %x\r\n", sample);
			}
			play = false;
			printf("reading the file is complete!\r\n");
		}
	}