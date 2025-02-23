//
// Created by Alberto Cardini on 21/11/24.
//

#include "I2CChannel.hpp"
// Remember that the first element of the transmitted buffer has to be the register in which you want to write the info.
HAL_StatusTypeDef I2CChannel::transmit(uint8_t &chip_address, std::vector<uint8_t> &buffer, Mode transmit_mode, Identity role) const {

  HAL_StatusTypeDef status;

  if (HAL_I2C_GetState(handler.get()) == HAL_I2C_STATE_READY) {

    if (role == Identity::MASTER && transmit_mode == Mode::POLLING)
      status = HAL_I2C_Master_Transmit(handler.get(), chip_address << 1, buffer.data(), buffer.size() * sizeof(uint8_t),timeout_tx);

    else if (role == Identity::MASTER && transmit_mode == Mode::NON_BLOCKING)
      status = HAL_I2C_Master_Transmit_DMA(handler.get(), chip_address << 1, buffer.data(), buffer.size() * sizeof(uint8_t));

    else if (role == Identity::SLAVE && transmit_mode == Mode::POLLING)
      status = HAL_I2C_Slave_Transmit(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t), timeout_tx);

    else if (role == Identity::SLAVE && transmit_mode == Mode::NON_BLOCKING)
      status = HAL_I2C_Slave_Transmit_DMA(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t));
    else status = HAL_ERROR;

  } else status = HAL_ERROR;

  return status;
}

HAL_StatusTypeDef I2CChannel::receive(uint8_t &chip_address, std::vector<uint8_t> &buffer, Mode receive_mode, Identity role) {

  HAL_StatusTypeDef status;
  buffer.resize(sData);

  if (HAL_I2C_GetState(handler.get()) == HAL_I2C_STATE_READY) {

    if (role == Identity::MASTER && receive_mode == Mode::POLLING)
      status = HAL_I2C_Master_Receive(handler.get(), (chip_address << 1) | 0x01, buffer.data(), buffer.size() * sizeof(uint8_t), timeout_rx);

    else if (role == Identity::MASTER && receive_mode == Mode::NON_BLOCKING)
      status = HAL_I2C_Master_Receive_DMA(handler.get(), (chip_address << 1) | 0x01, buffer.data(), buffer.size() * sizeof(uint8_t));

    else if (role == Identity::SLAVE && receive_mode == Mode::POLLING)
      status = HAL_I2C_Slave_Receive(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t), timeout_rx);

    else if (role == Identity::SLAVE && receive_mode == Mode::NON_BLOCKING)
      status = HAL_I2C_Slave_Receive_DMA(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t));

    else status = HAL_ERROR;

  }else status = HAL_ERROR;

  return status;
}
