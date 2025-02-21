//
// Created by Alberto Cardini on 16/12/24.
//
#include "I2CLink.hpp"

HAL_StatusTypeDef I2CLink::Transmit(std::vector<uint8_t> &buffer) {
    select_address(buffer);
    status = i2c_channel.Transmit(id, modeTransmit, buffer);
    return status;
}

HAL_StatusTypeDef I2CLink::Receive(std::vector<uint8_t> &buffer) {
    select_address(buffer);
    status = i2c_channel.Receive(id, modeTransmit, buffer);
    return status;
}

void I2CLink::select_address(std::vector<uint8_t>& buffer) const {
    buffer.insert(buffer.begin(),address);
}