while(temp_buffer != '\n')
{
	while(!LL_USART_IsActiveFlag_RXNE(USART1))
		__NOP();

    LL_USART_EnableDMAReq_RX(USART1);
	LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_5);			
		
	message_buffer[index++] = temp_buffer;	
}

/////////////////////////////////
  /* USER CODE BEGIN 2 */
//configure DMA channel 4

    LL_DMA_ConfigAddresses(DMA1,
							LL_DMA_CHANNEL_5,
							LL_USART_DMA_GetRegAddr(USART1),													 
							(uint32_t)temp_buffer,
							`LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
												 
		LL_DMA_SetDataLength(DMA1,
												 LL_DMA_CHANNEL_5,
												 4);		
	
    LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_5);
		
//		while(!LL_USART_IsActiveFlag_RXNE(USART1))
//			__NOP();
		
		int index = 0;
	while(1)
	{
		while(!LL_USART_IsActiveFlag_RXNE(USART1))
			__NOP();

		LL_USART_EnableDMAReq_RX(USART1);
		LL_DMA_EnableChannel(DMA1,
													 LL_DMA_CHANNEL_5);			
			
		message_buffer[index] = temp_buffer[index];	
		
		
		if(temp_buffer[index] == '\n')
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
												 index-1);		
	
    LL_DMA_EnableChannel(DMA1,
                         LL_DMA_CHANNEL_4);
											 
    LL_USART_EnableDMAReq_TX(USART1);			
  /* USER CODE END 2 */

