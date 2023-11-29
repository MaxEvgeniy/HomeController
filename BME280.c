#include "BME280.h"

//------------------------------------------------

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart2;

extern char str1[100];

//------------------------------------------------


uint8_t value = BME280_ReadReg(BME280_REG_ID);

//sprintf(str1, "rnrnID: 0x%02Xrn", value);

HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);

void BME280_Init(void)

{

  //uint8_t value=0;
  value=0;

  //uint32_t value32=0;

}

static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)

{

  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);

  if(status != HAL_OK) Error();

}

//------------------------------------------------

static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)

{

  HAL_StatusTypeDef status = HAL_OK;

  uint8_t value = 0;

  status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);

  if(status != HAL_OK) Error();

  return value;

}

//------------------------------------------------

static void I2Cx_ReadData16(uint16_t Addr, uint8_t Reg, uint16_t *Value)

{

  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)Value, 2, 0x10000);

  if(status != HAL_OK) Error();

}

//------------------------------------------------

static void I2Cx_ReadData24(uint16_t Addr, uint8_t Reg, uint32_t *Value)

{

  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)Value, 3, 0x10000);

  if(status != HAL_OK) Error();

}

//------------------------------------------------

//------------------------------------------------

void BME280_WriteReg(uint8_t Reg, uint8_t Value)

{

  I2Cx_WriteData(BME280_ADDRESS, Reg, Value);

}

//------------------------------------------------

//------------------------------------------------

uint8_t BME280_ReadReg(uint8_t Reg)

{

  uint8_t res = I2Cx_ReadData(BME280_ADDRESS,Reg);

  return res;

}

//------------------------------------------------
