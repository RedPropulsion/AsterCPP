//
// Created by Alberto Cardini on 16/12/24.
//
#include "UARTChannel.hpp"

HAL_StatusTypeDef UARTChannel::transmit(std::vector<std::string> &buffer, Mode transmit_mode) const {

  HAL_StatusTypeDef status;

  if (transmit_mode == Mode::POLLING)
    for (auto &i: buffer) {
      status = HAL_UART_Transmit(handler.get(), reinterpret_cast<const uint8_t *>(i.c_str()),i.size() * sizeof(uint8_t), timeout_tx);
    }
  else
    for (auto &i: buffer) {
      //FIXME: there are still problems in assigning the correct DMA stream to the USART3_TX and USART_RX. Needs correction in the .ioc .
      status = HAL_UART_Transmit_DMA(handler.get(), reinterpret_cast<const uint8_t *>(i.c_str()),i.size() * sizeof(uint8_t));
    }

  return status;
}

HAL_StatusTypeDef UARTChannel::receive(std::vector<std::string> &buffer, Mode receive_mode) const {

  HAL_StatusTypeDef status;
  const int fixed_size = 32;

  if (buffer.capacity() != 0) {

    uint8_t temp_store[fixed_size] = {"\0"};     // UART.receive works only with uint_8 fixed size arrays to store data.
                                                 // In order to create a uniform interface we store the raw data in an
                                                 // uint_8 array, and then we create a string where the raw data are
                                                 // appended. After that, the string is pushed inside the buffer vector.
                                                 // At the end of the acquisition, the buffer has some strings, one for
                                                 // every receiving session.
    std::string merged_values;

    if (receive_mode == Mode::POLLING)
      status = HAL_UART_Receive(handler.get(), temp_store, sizeof(temp_store), timeout_rx);
    else
      //FIXME: there are still problems in assigning the correct DMA stream to the USART3_TX and USART_RX. Needs correction in the .ioc .
      status = HAL_UART_Receive_DMA(handler.get(), temp_store, sizeof(temp_store));

    for (unsigned char i: temp_store) {
      merged_values.push_back(i);
    }
    buffer.push_back(merged_values);

  } else status = HAL_ERROR;

  return status;
}

//FIXME: the correct functioning of this method is directly related to the correct usage of the DMA.
void UARTChannel::HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

  uint8_t msg[] = "The buffer has been sent successfully\r\n";
  HAL_UART_Transmit(handler.get(), msg, sizeof(msg), 1000);
}

void UARTChannel::HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart) {
  //TODO implement the logic needed
}

void UARTChannel::HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  //TODO implement the logic needed
}

void UARTChannel::HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {
  //TODO implement the logic needed
}

void UARTChannel::HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  //TODO implement the logic needed
}