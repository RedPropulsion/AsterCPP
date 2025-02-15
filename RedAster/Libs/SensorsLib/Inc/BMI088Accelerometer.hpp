//
// Created by guflie on 14/01/25.
//

#ifndef BMI088ACCELEROMETER_HPP
#define BMI088ACCELEROMETER_HPP

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
#define ACC_PIN         GPIO_PIN_2
#define GPIO            GPIOC

#define FN_READ               0x80
#define FN_WRITE              0x00
#define DUMMY_PLACEHOLDER     0X00

#define CHIP_ID_VAL					  0x1E
#define SOFTRESET_COMM	    	0xB6

/*
 *  x-axis signal 		y-axis signal 	z-axis signal
 *  ≥1000 mg		 	≥1000 mg 			≥500 mg
 */
#define BMI088_SELF_X 	1000
#define BMI088_SELF_Y 	1000
#define BMI088_SELF_Z 	500

// --------------------------------- ENUMS
typedef enum{
  ON = 0x04,
  OFF = 0x00,
  SUSPEND = 0x03,
  ACTIVE = 0x00,
}  PowerMode;

typedef enum {
  RANGE3 = 0x00,
  RANGE6 = 0x01,
  RANGE12 = 0x02,
  RANGE24 = 0x03,
} Range;

typedef enum {
  ODR12 = 0x05,
  ODR25 = 0x06,
  ODR50 = 0x07,
  ODR100 = 0x08,
  ODR200 = 0x09,
  ODR400 = 0x0A,
  ODR800 = 0x0B,
  ODR1600 = 0x0C,
} ODR;

typedef enum {
  BW_LP_OSR4 = 0x80,   // 4-fold oversampling
  BW_LP_OSR2 = 0x90,   // 2-fold oversampling
  BW_LP_NORMAL = 0xA0, // 4-fold oversampling
} OSR;

typedef enum {
  SOFTERESET = 0X7E,
  PWR_CTR = 0X7D,
  PWR_CNF = 0X7C,
  INT_MAP_DATA = 0X58,
  INT2_IO_CTRL = 0X54,
  INT1_IO_CTRL = 0X53,
  FIFO_CONFIG_1 = 0X49,
  FIFO_CONFIG_0 = 0X48,
  FIFO_WTM_1 = 0X47,
  FIFO_WTM_0 = 0X46,
  FIFO_DOWNS = 0X45,
  RANGE = 0X41,
  CONF = 0X40,
  FIFO_DATA = 0X26,
  FIFO_LENGTH_1 = 0X25,
  FIFO_LENGTH_0 = 0X24,
  TEMP_LSB = 0X23,
  TEMP_MSB = 0X22,
  INT_STAT_1 = 0X1D,
  SENSORTIME_2 = 0X1A,
  SENSORTIME_1 = 0X19,
  SENSORTIME_0 = 0X18,
  Z_MSB = 0X17,
  Z_LSB = 0X16,
  Y_MSB = 0X15,
  Y_LSB = 0X14,
  X_MSB = 0X13,
  X_LSB = 0X12,
  STATUS = 0X03,
  ERR = 0X02,
  CHIP_ID = 0X00,
  SELF_TEST = 0X6D,
} RegisterAddress;

typedef enum {
  TEST_POSITIVE = 0X0D,
  TEST_NEGATIVE = 0X09,
  TEST_OFF = 0X00,
} SelfTest;

class BMI088Accelerometer final : public Sensor {
    private:
      PowerMode powerMode {PowerMode::ON};
      Range range {Range::RANGE12};
      uint8_t ODR_OSR {ODR::ODR400 + OSR::BW_LP_OSR2};

    protected:
      HAL_StatusTypeDef readData(uint8_t reg, std::vector<uint8_t>& data) const override;
      HAL_StatusTypeDef writeData(uint8_t reg, uint8_t data) override;

    public:
      explicit BMI088Accelerometer(Link& link): Sensor(link) { }
      [[nodiscard]] std::map<std::string, std::string> getConfig() const override;
      HAL_StatusTypeDef init() override;
      uint8_t selfTest() override;

      [[nodiscard]] HAL_StatusTypeDef setRange(Range range);
      [[nodiscard]] HAL_StatusTypeDef setConfig();
      vec3s16 getMeasure() const;
      HAL_StatusTypeDef softReset();
};



#endif //BMI088ACCELEROMETER_HPP
