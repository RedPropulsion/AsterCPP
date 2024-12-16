//
// Created by danie on 13/12/2024.
//

#include "SPILink.h"

HAL_StatusTypeDef SPILink::Transmit(std::vector<uint8_t> &buffer) {
    selectChip();
    status = spiChannel.Transmit(Identity::N_A, modeTransmit, buffer);
    deselectChip();
    return status;
}

HAL_StatusTypeDef SPILink::Receive(std::vector<uint8_t> &buffer) {
    selectChip();
    status = spiChannel.Receive(Identity::N_A, modeTransmit, buffer);
    deselectChip();
    return status;
}

HAL_StatusTypeDef SPILink::TransmitReceive(std::vector<uint8_t> &TX_buffer, std::vector<uint8_t> &RX_buffer) {
    selectChip();
    status = spiChannel.TransmitReceive(Identity::N_A, modeTransmit, TX_buffer, RX_buffer);
    deselectChip();
    return status;
}

void SPILink::selectChip() const{
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);   // CS low
}

void SPILink::deselectChip() const{
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);     // CS high
}