//
// Created by guflie on 17/01/25.
//

#ifndef BMI088GYROSCOPE_HPP
#define BMI088GYROSCOPE_HPP

// --------------------------------- INCLUDES
#include "Sensor.hpp"
#include "DataTypes.hpp"
#include "ByteUtils.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32h7xx.h"
#ifdef __cplusplus
}
#endif

// --------------------------------- DEFINE
#define ACC_GYR         	GPIO_PIN_3
#define GPIO            	GPIOC
#define CHIP_ID_VAL     	0x1E

#define SOFTRESET_COMM		0xB6
#define FN_READ             0x80
#define FN_WRITE            0x00

// --------------------------------- ENUMS
typedef enum {
  SOFT_RESET = 0x14,
  LP1 = 0x11,
  BW = 0x10,
  RANGE = 0x0F,
  CHIP_ID = 0x00,
  FIFO_DATA = 0x3F,
  FIFO_CONFIG_1 = 0x3F,
  FIFO_CONFIG_0 = 0x3D,
  SELF_TEST = 0X3C,
  FIFO_EXT_INT_S = 0x34,
  FIFO_WM_EN = 0x1E,
  INT3_INT4_IO_MAP = 0x18,
  INT3_INT4_IO_CONF = 0x16,
  INT_CTRL = 0x15,
  LPM1 = 0x11,
  BANDWIDTH = 0x10,
  FIFO_STATUS = 0x0E,
  INT_STAT_1 = 0x0A,
  RATE_Z_MSB = 0x07,
  RATE_Z_LSB = 0x06,
  RATE_Y_MSB = 0x05,
  RATE_Y_LSB = 0x04,
  RATE_X_MSB = 0x03,
  RATE_X_LSB = 0x02,
} RegisterAddress;

typedef enum {
	BAND_2000_FILTER_532 =  0x00,
	BAND_2000_FILTER_230 =  0x01,
	BAND_1000_FILTER_116 =  0x02,
	BAND_400_FILTER_47 =  0x03,
	BAND_200_FILTER_64 =  0x06,
	BAND_200_FILTER_23 =  0x04,
	BAND_100_FILTER_32 =  0x07,
	BAND_100_FILTER_12 =  0x05,
} BandWidth;

typedef enum {
	RANGE_2000 = 0x00,
  	RANGE_1000 = 0x01,
 	RANGE_500 = 0x02,
  	RANGE_250 = 0x03,
  	RANGE_125 = 0x04,
} Dynamic;

typedef enum {
	NORMAL = 0x00,
  	SUSPEND = 0x80,
  	DEEP_SUSPEND = 0x80,
} PowerMode;

class BMI088Gyroscope final : public Sensor {
	private:
          PowerMode pwr {NORMAL};
          BandWidth band {BAND_2000_FILTER_532};
          Dynamic range {RANGE_500};

	protected:
      	HAL_StatusTypeDef readData(uint8_t reg, std::vector<uint8_t>& data) const override;
      	HAL_StatusTypeDef writeData(uint8_t reg, uint8_t data) override;

    public:
      	explicit BMI088Gyroscope(Link& link): Sensor(link) { }
      	[[nodiscard]] std::map<std::string, std::string> getConfig() const override;
      	HAL_StatusTypeDef init() override;
      	uint8_t selfTest() override;
      	[[nodiscard]] HAL_StatusTypeDef setConfig();
      	vec3s16 getMeasure() const;
      	HAL_StatusTypeDef softReset();
};



#endif //BMI088GYROSCOPE_HPP
