#include "HAL_i2c_rw_functions_BME280.h"

I2C_HandleTypeDef hi2c1;

uint8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	// The BME280 driver from Bosch needs processor specific read, write, and delay functions to operate properly
	// Using mem_read since this is a standard memory register address access based device.
	if (HAL_I2C_Mem_Read(&hi2c1, (id << 1) , reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY) != HAL_OK) {
		return -1;
	}
	
	// Transmit and receive are another way of doing the same thing as mem_read
//	if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), &reg_addr, 1, 10) != HAL_OK) {
//		return -1;
//	}
//	if(HAL_I2C_Master_Receive(&hi2c1, (id << 1), data, len, 10) != HAL_OK) {
//		return -1;
//	}
	
	return 0;
}
	

uint8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	// The BME280 driver from Bosch needs processor specific read, write, and delay functions to operate properly
	if(HAL_I2C_Mem_Write(&hi2c1, id, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY) != HAL_OK) {
		return -1;
	}
	return 0;
}

//int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
//{
//  int8_t *buf;
//  buf = malloc(len +1);
//  buf[0] = reg_addr;
//  memcpy(buf +1, reg_data, len);

//  if(HAL_I2C_Master_Transmit(&hi2c1, (BME280_ADDR), (uint8_t*)buf, len + 1, HAL_MAX_DELAY) != HAL_OK) return -1;

//  free(buf);
//  return 0;
//}

void user_delay_ms(uint32_t period){
	HAL_Delay(period);
}