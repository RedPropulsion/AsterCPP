//
// Created by Alberto Cardini on 21/11/24.
//

#include "SPI.hpp"


HAL_StatusTypeDef SPI::Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t> &buffer) const {
    if (role == Identity::N_A && transmit_mode == Mode::POLLING) {
        return HAL_SPI_Transmit(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::N_A && transmit_mode == Mode::NON_BLOCKING) {
        return HAL_SPI_Transmit_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        throw std::logic_error("Non-valid identity for the SPI Transmit operation");
}

HAL_StatusTypeDef SPI::Receive(Identity role, Mode receive_mode, std::vector<uint8_t> &buffer) {
    if (role == Identity::N_A && receive_mode == Mode::POLLING) {
        return HAL_SPI_Receive(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::N_A && receive_mode == Mode::NON_BLOCKING) {
        return HAL_SPI_Receive_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        throw std::logic_error("Non-valid identity for the SPI Transmit operation");
}