/**
 * @brief     Read some bytes from slave device.
 *
 * @param[in] owp       pointer to the @p onewireDriver object
 * @param[out] rxbuf    pointer to the buffer for read data
 * @param[in] rxbytes   amount of data to be received
 *
 * @return              Bool read success.
 */
bool onewireRead(onewireDriver *owp, uint8_t *rxbuf, size_t rxbytes) {
  osalDbgCheck((NULL != owp) && (NULL != rxbuf));
  osalDbgCheck((rxbytes > 0) && (rxbytes < 65536));
  osalDbgAssert(owp->reg.state == ONEWIRE_READY, "Invalid state");

  bool lock = chMtxTryLock(&owp->owMtx);
  memset(rxbuf, 0, rxbytes);
  for (size_t i=0; i<rxbytes; i++) {
	  rxbuf[i] = ds2482_read_byte(owp);
	  if (owp->error != ONEWIRE_SUCCESS)
		  break;
  }
  if (lock)
	  chMtxUnlock(&owp->owMtx);
  return (owp->error == ONEWIRE_SUCCESS);
}


// read byte from 1-wire bus
static uint8_t ds2482_read_byte(onewireDriver *owp) {
  uint8_t cmd = CMD_1WRB;
  // STM32F1 I2C hack
#if defined(STM32F1XX_I2C)
  uint8_t n = 2;
#else
  uint8_t n = 1;
#endif
  uint8_t rcvbuf[n];

  owp->error = ds2482_write(owp, &cmd, 1);
  if (owp->error != ONEWIRE_SUCCESS)
    return 0;

  owp->error = ds2482_read(owp, rcvbuf, n);
  if (owp->error != ONEWIRE_SUCCESS)
	return 0;

  return rcvbuf[0];
}


// read len bytes from 1-wire to rxbuf
static onewire_error_t ds2482_read(onewireDriver *owp, uint8_t *rxbuf, uint8_t len) {
  msg_t state = MSG_OK;
  uint8_t cmd[2] = { CMD_SRP, REG_DATA };

#if defined(STM32F1XX_I2C)
  osalDbgAssert(len != 1, "STM32F1XX I2C can't read 1 byte");
#endif

#if I2C_USE_MUTUAL_EXCLUSION
  i2cAcquireBus(owp->config->i2cd);
#endif
  state = i2cMasterTransmitTimeout(owp->config->i2cd, DS2482_ADDR, cmd, 2, rxbuf, len, MS2ST(OW_CMD_MS));
#if I2C_USE_MUTUAL_EXCLUSION
  i2cReleaseBus(owp->config->i2cd);
#endif

  if (state == MSG_TIMEOUT) {
    return ONEWIRE_I2C_TIMEOUT;
  }

  return ONEWIRE_SUCCESS;
}


