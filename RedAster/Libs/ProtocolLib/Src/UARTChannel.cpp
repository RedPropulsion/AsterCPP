//
// Created by Alberto Cardini on 16/12/24.
//
#include "UARTChannel.hpp"

HAL_StatusTypeDef UARTChannel::Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t> &buffer) const {

    HAL_StatusTypeDef status;

    if (role == Identity::N_A && transmit_mode == Mode::POLLING)
        status = HAL_UART_Transmit(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_timeout);

    else if (role == Identity::N_A && transmit_mode == Mode::NON_BLOCKING)
        status = HAL_UART_Transmit_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));

    else
        status = HAL_ERROR;

    return status;
}

HAL_StatusTypeDef UARTChannel::Receive(Identity role, Mode receive_mode, std::vector<uint8_t> &buffer) const {

    HAL_StatusTypeDef status;

    if (role == Identity::N_A && receive_mode == Mode::POLLING)
        status = HAL_UART_Receive(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_timeout);

    else if (role == Identity::N_A && receive_mode == Mode::NON_BLOCKING)
        status = HAL_UART_Receive_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));

    else
        status = HAL_ERROR;

    return status;
}

void UARTChannel::HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
    //TODO implement the logic needed
}

void UARTChannel::HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef* huart) {
    //TODO implement the logic needed
}

void UARTChannel::HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    //TODO implement the logic needed
}

void UARTChannel::HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef* huart) {
    //TODO implement the logic needed
}

void UARTChannel::HAL_UART_ErrorCallback(UART_HandleTypeDef* huart) {
    //TODO implement the logic needed
}