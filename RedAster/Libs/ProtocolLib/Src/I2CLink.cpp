//
// Created by Alberto Cardini on 16/12/24.
//
#include "I2CLink.hpp"

HAL_StatusTypeDef I2CLink::transmit(std::vector<uint8_t> &buffer) {
  buffer.insert(buffer.begin(), target_reg);
  status = i2c_channel.transmit(chip_address, buffer, modeTransmit, id);
  buffer.erase(buffer.begin());
  return status;
}

HAL_StatusTypeDef I2CLink::receive(std::vector<uint8_t> &buffer) {
  buffer.insert(buffer.begin(), target_reg);
  status = i2c_channel.receive(chip_address, buffer, modeTransmit, id);
  buffer.erase(buffer.begin());
  return status;
}