//
// Created by danie on 13/12/2024.
//

#include "SPILink.hpp"

HAL_StatusTypeDef SPILink::transmit(std::vector<uint8_t> &buffer) {
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  status = spiChannel.transmit(buffer, modeTransmit);
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  return status;
}

HAL_StatusTypeDef SPILink::receive(std::vector<uint8_t> &buffer) {
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  status = spiChannel.receive(buffer, modeTransmit);
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  return status;
}

HAL_StatusTypeDef SPILink::transmit_receive(std::vector<uint8_t> &TX_buffer, std::vector<uint8_t> &RX_buffer) {
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  status = spiChannel.transmit_receive(TX_buffer, RX_buffer, modeTransmit);
  HAL_GPIO_WritePin(&csPort, csPin, GPIO_PIN_SET);
  return status;
}