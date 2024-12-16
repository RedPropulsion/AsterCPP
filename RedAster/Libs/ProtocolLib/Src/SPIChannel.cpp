//
// Created by Alberto Cardini on 21/11/24.
//

#include "SPIChannel.hpp"


HAL_StatusTypeDef SPIChannel::Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t> &buffer) const {

    HAL_StatusTypeDef status;

    if (role == Identity::N_A && transmit_mode == Mode::POLLING) {
        status = HAL_SPI_Transmit(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    else if (role == Identity::N_A && transmit_mode == Mode::NON_BLOCKING) {
        status = HAL_SPI_Transmit_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        status = HAL_ERROR;
        //throw std::logic_error("Non-valid identity for the SPI Transmit operation");
    return status;

}

HAL_StatusTypeDef SPIChannel::Receive(Identity role, Mode receive_mode, std::vector<uint8_t> &buffer) {

    HAL_StatusTypeDef status;

    if (role == Identity::N_A && receive_mode == Mode::POLLING) {
        status = HAL_SPI_Receive(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    else if (role == Identity::N_A && receive_mode == Mode::NON_BLOCKING) {
        status = HAL_SPI_Receive_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        status = HAL_ERROR;
        //throw std::logic_error("Non-valid identity for the SPI Transmit operation");

    return status;
}

HAL_StatusTypeDef SPIChannel::TransmitReceive(Identity role, Mode transmit_receive_mode, std::vector<uint8_t> &TX_buffer, std::vector<uint8_t> &RX_buffer) {
    HAL_StatusTypeDef status;
    if (size_in_byte(TX_buffer) == size_in_byte(RX_buffer)) {

        if (role == Identity::N_A && transmit_receive_mode == Mode::POLLING) {
            status = HAL_SPI_TransmitReceive(handler.get(), get_valid_ptr(TX_buffer), get_valid_ptr(RX_buffer),
                                             size_in_byte(TX_buffer), polling_t);
        } else if (role == Identity::N_A && transmit_receive_mode == Mode::NON_BLOCKING) {
            status = HAL_SPI_TransmitReceive_DMA(handler.get(), get_valid_ptr(TX_buffer), get_valid_ptr(RX_buffer),
                                                 size_in_byte(TX_buffer));
        } else
            status = HAL_ERROR;
            //throw std::logic_error("Non-valid identity for the SPI Transmit operation");

    } else {
        status = HAL_ERROR;
    }
    return status;
}