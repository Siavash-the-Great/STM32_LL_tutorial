/**
  ******************************************************************************
  * @file		dot_matrix_stm32f1_spi.c
  ******************************************************************************
  */
  
#define SPI_CH	1	/* SPI channel to use = 1: SPI1, 11: SPI1/remap, 2: SPI2 */

#define FCLK_SLOW() { SPIx_CR1 = (SPIx_CR1 & ~0x38) | 0x28; }	/* Set SCLK = PCLK / 64 */
#define FCLK_FAST() { SPIx_CR1 = (SPIx_CR1 & ~0x38) | 0x00; }	/* Set SCLK = PCLK / 2 */

#if SPI_CH == 1	/* PB0:MMC_CS, PA5:MMC_SCLK, PA6:MMC_DO, PA7:MMC_DI, PC4:MMC_CD */
#define CS_HIGH()	GPIOB_BSRR = _BV(0)
#define CS_LOW()	GPIOB_BSRR = _BV(0+16)