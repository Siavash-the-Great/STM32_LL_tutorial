  /* USER CODE BEGIN 2 */
//configure DMA channel 4

    LL_DMA_ConfigAddresses(DMA1,
                           LL_DMA_CHANNEL_5,
													 LL_USART_DMA_GetRegAddr(USART1),													 
                           (uint32_t)message_buffer,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
												 
		LL_DMA_SetDataLength(DMA1,
												 LL_DMA_CHANNEL_5,
												 ARRAYSIZE);		
	
    LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_5);
		
//		while(!LL_USART_IsActiveFlag_RXNE(USART1))
//			__NOP();
		
		int index = 0;
		for(int i = 0; i < ARRAYSIZE; i++)
		{
		while(!LL_USART_IsActiveFlag_RXNE(USART1))
			__NOP();
		
    LL_USART_EnableDMAReq_RX(USART1);
		LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_5);	
//		
		if((message_buffer[index] == '\n') || (message_buffer[index-1] == '\n') || (message_buffer[index+1] == '\n'))
			break;
		
		index++;
		}
///////////////////////////////////////////////////////		
    LL_DMA_ConfigAddresses(DMA1,
                           LL_DMA_CHANNEL_4,
                           (uint32_t)message_buffer,
													 LL_USART_DMA_GetRegAddr(USART1),
                           LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
												 
		LL_DMA_SetDataLength(DMA1,
                         LL_DMA_CHANNEL_4,
												 ARRAYSIZE);		
	
    LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_4);
											 
    LL_USART_EnableDMAReq_TX(USART1);			
  /* USER CODE END 2 */