//
// Created by danie on 13/12/2024.
//

#include "SPILink.hpp"

HAL_StatusTypeDef SPILink::transmit(std::vector<uint8_t> &buffer) {
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_RESET);
  status = spiChannel.transmit(buffer, modeTransmit);
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_SET);
  return status;
}

HAL_StatusTypeDef SPILink::receive(std::vector<uint8_t> &buffer) {
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_RESET);
  status = spiChannel.receive(buffer, modeTransmit);
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_SET);
  return status;
}

HAL_StatusTypeDef SPILink::transmit_receive(std::vector<uint8_t> &tx_buffer, std::vector<uint8_t> &rx_buffer) {
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_RESET);
  status = spiChannel.transmit_receive(tx_buffer, rx_buffer, modeTransmit);
  HAL_GPIO_WritePin(csPort.get(), csPin, GPIO_PIN_SET);
  return status;
}