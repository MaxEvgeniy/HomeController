#ifndef BME280_H_

#define BME280_H_

//------------------------------------------------

#include "stm32f1xx_hal.h"

#include <string.h>

#include <math.h>

#define BME280_ADDRESS 0xEC //BME280 I2C ADDRES (0x76<<1)

#define BME280_REG_ID 0xD0 //BME280 ID REGISTER

#define BME280_ID 0x60 //BME280 I2C ID




void BME280_Init(void);

static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);

static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg);

static void I2Cx_ReadData16(uint16_t Addr, uint8_t Reg, uint16_t *Value);

static void I2Cx_ReadData24(uint16_t Addr, uint8_t Reg, uint32_t *Value);

void BME280_WriteReg(uint8_t Reg, uint8_t Value);

uint8_t BME280_ReadReg(uint8_t Reg);


//------------------------------------------------

//------------------------------------------------

//------------------------------------------------

#endif /* BME280_H_ */