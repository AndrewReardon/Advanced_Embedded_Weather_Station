//#include "HAL_i2c_rw_functions_BME280.h"

//I2C_HandleTypeDef hi2c1;

//uint8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
//	if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), &reg_addr, 1, 10) != HAL_OK) {
//		return -1;
//	}
//	if(HAL_I2C_Master_Receive(&hi2c1, (id << 1), data, len, 10) != HAL_OK) {
//		return -1;
//	}
//	
//	return 0;
//}
//	

//uint8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
//}

//void user_delay_ms(uint32_t period);