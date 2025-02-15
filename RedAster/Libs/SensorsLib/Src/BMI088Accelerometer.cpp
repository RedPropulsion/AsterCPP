//
// Created by guflie on 14/01/25.
//

#include "BMI088Accelerometer.hpp"

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Accelerometer::readData(const uint8_t reg, std::vector<uint8_t>& data) const {
  std::vector<uint8_t> buffer {static_cast<uint8_t>(FN_READ + reg), DUMMY_PLACEHOLDER};
  HAL_StatusTypeDef comStatus = link->Transmit(buffer);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  return link->Receive(data);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Accelerometer::writeData(const uint8_t reg, const uint8_t data) {
  std::vector<uint8_t> buffer {static_cast<uint8_t>(FN_WRITE + reg), data};
  return link->Transmit(buffer);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
std::map<std::string, std::string> BMI088Accelerometer::getConfig() const {
  return {
      {"powerMode",std::to_string(powerMode)}
      , {"range",std::to_string(range)}
      , {"ODR_OSR", std::to_string(ODR_OSR)}
  };
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Accelerometer::init() {
  HAL_StatusTypeDef comStatus = HAL_OK;

  // init physic accelerometer
  std::vector<uint8_t> buffer {FN_READ};
  HAL_GPIO_WritePin(GPIO, ACC_PIN, GPIO_PIN_RESET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(GPIO, ACC_PIN, GPIO_PIN_SET);
  HAL_Delay(1);
  comStatus = readData(RegisterAddress::CHIP_ID, buffer);
  if (comStatus != HAL_OK) {
    return comStatus;
  }

  // chipId check
  std::vector<uint8_t> chipIdBuff {0};
  comStatus = readData(RegisterAddress::CHIP_ID, chipIdBuff);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  if(chipIdBuff[0] != CHIP_ID_VAL)
    return HAL_ERROR;

  // self test
  selfTest();
  comStatus = softReset();
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  HAL_Delay(60);

  comStatus = setConfig();
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  HAL_Delay(1);
  return comStatus;
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
uint8_t BMI088Accelerometer::selfTest() {
  vec3s16 offsetTest {};
  uint8_t res = 0;
  HAL_StatusTypeDef comStatus = HAL_OK;

  // save actual configuration
  PowerMode powerModeBackup = powerMode;
  Range rangeBackup = range;
  uint8_t ODR_OSRBackup = ODR_OSR;

  range = Range::RANGE24;
  ODR_OSR = ODR::ODR1600 + OSR::BW_LP_NORMAL;
  comStatus = setConfig();
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }
  HAL_Delay(3);

  comStatus = writeData(RegisterAddress::SELF_TEST, SelfTest::TEST_POSITIVE);
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }
  HAL_Delay(55);
  vec3s16 offsetDataPositiveTest = getMeasure();

  comStatus = writeData(RegisterAddress::SELF_TEST, SelfTest::TEST_NEGATIVE);
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }
  HAL_Delay(55);
  vec3s16 offsetDataNegativeTest = getMeasure();

  comStatus = writeData(RegisterAddress::SELF_TEST, SelfTest::TEST_OFF);
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }
  comStatus = softReset();
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }
  HAL_Delay(10);
  range = rangeBackup;
  ODR_OSR = ODR_OSRBackup;
  comStatus = setConfig();
  if (comStatus != HAL_OK) {
    range = rangeBackup;
    ODR_OSR = ODR_OSRBackup;
    return comStatus;
  }

  offsetTest.x = offsetDataNegativeTest.x + offsetDataPositiveTest.x;
  offsetTest.y = offsetDataNegativeTest.y + offsetDataPositiveTest.y;
  offsetTest.z = offsetDataNegativeTest.z + offsetDataPositiveTest.z;
  if (offsetTest.x < BMI088_SELF_X) { res |= 0x04; }
  if (offsetTest.x < BMI088_SELF_Y) { res |= 0x02; }
  if (offsetTest.x < BMI088_SELF_Z) { res |= 0x01; }
  return res;
}

/* @brief set range of accelerometer
 * @param range, new range to set
 */
HAL_StatusTypeDef BMI088Accelerometer::setRange(Range range) {
  this->range = range;
  return writeData(RegisterAddress::RANGE, range);
}

/*
 * @brief write abstract sensor configuration into real sensor
 */
HAL_StatusTypeDef BMI088Accelerometer::setConfig() {
  HAL_StatusTypeDef comStatus = writeData(RegisterAddress::PWR_CNF, 0x00);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  HAL_Delay(1);

  comStatus = writeData(RegisterAddress::PWR_CTR, powerMode);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  HAL_Delay(1);

  comStatus = writeData(RegisterAddress::RANGE, range);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  comStatus = writeData(RegisterAddress::CONF, ODR_OSR);
  if (comStatus != HAL_OK) {
    return comStatus;
  }
  HAL_Delay(1);

  return comStatus;
}

/*
 * @brief read sensor value
 */
vec3s16 BMI088Accelerometer::getMeasure() const{
  std::vector<uint8_t> buffer;
  HAL_StatusTypeDef comStatus = readData(RegisterAddress::X_LSB, buffer);
  if (comStatus != HAL_OK) {
    return {0,0,0};
  }
  uint16_t cost = 1000*((1<<(range+1)));
  cost += cost>>1;
  return {
    static_cast<int16_t>(aggregate8to16({buffer[0], buffer[1]}) * cost/32768)
    ,static_cast<int16_t>(aggregate8to16({buffer[2], buffer[3]}) * cost/32768)
    ,static_cast<int16_t>(aggregate8to16({buffer[4], buffer[5]}) * cost/32768)
  };
}

/*
 * @brief starts softreset procedure
 */
HAL_StatusTypeDef BMI088Accelerometer::softReset() {
  HAL_StatusTypeDef comStatus = writeData(RegisterAddress::SOFTERESET, SOFTRESET_COMM);
  HAL_Delay(1);
  return comStatus;
}