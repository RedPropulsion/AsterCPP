//
// Created by Alberto Cardini on 21/11/24.
//

#include "I2C.hpp"

HAL_StatusTypeDef I2C::Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t> &buffer) const {
    if (role == Identity::MASTER && transmit_mode == Mode::POLLING) {
        return HAL_I2C_Master_Transmit(handler.get(), buffer.front(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::MASTER && transmit_mode == Mode::NON_BLOCKING) {
        return HAL_I2C_Master_Transmit_DMA(handler.get(), buffer.front(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    if (role == Identity::SLAVE && transmit_mode == Mode::POLLING) {
        return HAL_I2C_Slave_Transmit(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::SLAVE && transmit_mode == Mode::NON_BLOCKING) {
        return HAL_I2C_Slave_Transmit_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        throw std::logic_error("I2C transmission failed");
}

HAL_StatusTypeDef I2C::Receive(Identity role, Mode receive_mode, std::vector<uint8_t> &buffer) {
    if (role == Identity::MASTER && receive_mode == Mode::POLLING) {
        return HAL_I2C_Master_Receive(handler.get(), buffer.front(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::MASTER && receive_mode == Mode::NON_BLOCKING) {
        return HAL_I2C_Master_Receive_DMA(handler.get(), buffer.front(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    if (role == Identity::SLAVE && receive_mode == Mode::POLLING) {
        return HAL_I2C_Slave_Receive(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer), polling_t);
    }

    if (role == Identity::SLAVE && receive_mode == Mode::NON_BLOCKING) {
        return HAL_I2C_Slave_Receive_DMA(handler.get(), get_valid_ptr(buffer), size_in_byte(buffer));
    }

    else
        throw std::logic_error("I2C transmission failed");
}
