//
// Created by guflie on 17/01/25.
//

#include "BMI088Gyroscope.hpp"

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Gyroscope::writeData(uint8_t reg, uint8_t data) {
  std::vector<uint8_t> buffer {static_cast<uint8_t>(FN_WRITE+reg), data};
  return link->Transmit(buffer);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Gyroscope::readData(uint8_t reg, std::vector<uint8_t>& data) const {
  std::vector<uint8_t> buffer {static_cast<uint8_t>(FN_WRITE+reg)};
  HAL_StatusTypeDef comStatus = link->Transmit(buffer);
  if(comStatus != HAL_OK)
    return comStatus;
  return link->Receive(data);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
uint8_t BMI088Gyroscope::selfTest() {
   HAL_StatusTypeDef comStatus = writeData(RegisterAddress::SELF_TEST, 0x01); // TODO hard-coded?
   uint8_t counter = 0;
   std::vector<uint8_t> res {};
   while(counter < 10 && (res[0] & 0x02)) {
       readData(RegisterAddress::SELF_TEST, res);
       if(comStatus != HAL_OK)
         return comStatus;
       counter++;
   }
   return res[0];
}

// TODO add comments
HAL_StatusTypeDef BMI088Gyroscope::setConfig() {
  HAL_StatusTypeDef comStatus = HAL_OK;
  comStatus = writeData(RegisterAddress::LPM1, pwr);
  if(comStatus != HAL_OK)
    return comStatus;
  comStatus = writeData(RegisterAddress::RANGE, range);
  if(comStatus != HAL_OK)
    return comStatus;
  return writeData(RegisterAddress::BANDWIDTH, band);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef BMI088Gyroscope::init() {
  HAL_StatusTypeDef comStatus = HAL_OK;

  std::vector<uint8_t> chipIdBuff {0};
  comStatus = readData(RegisterAddress::CHIP_ID, chipIdBuff);
  if(comStatus != HAL_OK)
    return comStatus;
  if(chipIdBuff[0] != CHIP_ID_VAL)
    return HAL_ERROR;

  selfTest();

  comStatus = softReset();
  if(comStatus != HAL_OK)
    return comStatus;
  HAL_Delay(60);
  comStatus = setConfig();
  if(comStatus != HAL_OK)
    return comStatus;
  HAL_Delay(1);
  return comStatus;
}

/*
 * @brief read sensor value
 */
vec3s16 BMI088Gyroscope::getMeasure() const {
  std::vector<uint8_t> buffer;
  HAL_StatusTypeDef comStatus = readData(RegisterAddress::RATE_X_LSB, buffer);
  if(comStatus != HAL_OK)
    return {0,0,0};

  return {
    static_cast<int16_t>(aggregate8to16({buffer[0], buffer[1]}) *1000 / (1<<(14+range)))
    ,static_cast<int16_t>(aggregate8to16({buffer[2], buffer[3]}) *1000 / (1<<(14+range)))
    ,static_cast<int16_t>(aggregate8to16({buffer[4], buffer[5]}) *1000 / (1<<(14+range)))
  };
}

/*
 * @brief starts softreset procedure
 */
HAL_StatusTypeDef BMI088Gyroscope::softReset() {
  HAL_StatusTypeDef comStatus = writeData(RegisterAddress::SOFT_RESET, SOFTRESET_COMM);
  HAL_Delay(1);
  return comStatus;
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
std::map<std::string, std::string> BMI088Gyroscope::getConfig() const {
  return {
      {"powerMode",std::to_string(pwr)}
    , {"bandwidth",std::to_string(band)}
    , {"range", std::to_string(range)}
  };
}

