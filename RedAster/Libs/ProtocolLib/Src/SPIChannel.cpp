//
// Created by Alberto Cardini on 21/11/24.
//

#include "SPIChannel.hpp"

HAL_StatusTypeDef SPIChannel::transmit(std::vector<uint8_t> &buffer, Mode transmit_mode) const {

  HAL_StatusTypeDef status;

  if (HAL_SPI_GetState(handler.get()) == HAL_SPI_STATE_READY) {

    if (transmit_mode == Mode::POLLING)
      status = HAL_SPI_Transmit(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t), timeout_tx);

    else
      status = HAL_SPI_Transmit_DMA(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t));

  } else status = HAL_ERROR;

  return status;
}

HAL_StatusTypeDef SPIChannel::receive(std::vector<uint8_t> &buffer, Mode receive_mode) {

  HAL_StatusTypeDef status;

  if (HAL_SPI_GetState(handler.get()) == HAL_SPI_STATE_READY) {

    buffer.resize(sData);

    if (receive_mode == Mode::POLLING)
      status = HAL_SPI_Receive(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t), timeout_rx);

    else
      status = HAL_SPI_Receive_DMA(handler.get(), buffer.data(), buffer.size() * sizeof(uint8_t));

  } else status = HAL_ERROR;

  return status;
}

HAL_StatusTypeDef SPIChannel::transmit_receive(std::vector<uint8_t> &buffer_tx, std::vector<uint8_t> &buffer_rx, Mode transmit_receive_mode) {

  HAL_StatusTypeDef status;

  if (HAL_SPI_GetState(handler.get()) == HAL_SPI_STATE_READY) {

    buffer_rx.resize(buffer_tx.size());

    if (transmit_receive_mode == Mode::POLLING)
      status = HAL_SPI_TransmitReceive(handler.get(), buffer_tx.data(), buffer_rx.data(),buffer_rx.size() * sizeof(uint8_t), timeout_rx);

    else
      status = HAL_SPI_TransmitReceive_DMA(handler.get(), buffer_tx.data(), buffer_rx.data(),buffer_rx.size() * sizeof(uint8_t));

  } else status = HAL_ERROR;

  return status;
}