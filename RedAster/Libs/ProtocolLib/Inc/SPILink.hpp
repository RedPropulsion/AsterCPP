//
// Created by danie on 13/12/2024.
//

#ifndef SPILINK_H
#define SPILINK_H


#include "Link.hpp"
#include "SPIChannel.hpp"

/*
 * SPILink.h
 *
 * Definition of SPILink class, which implements a link interface for an
 * SPI communication. The class uses an SPIChannel object to facilitate communication
 * and provides methods for transmitting data over an SPI bus.
 * It also manages the chip select (CS) pin to enable and disable communication with
 * the connected device. More than one instance of this class can use the same channel.
 *
 * Dependencies:
 * - HAL library.
 * - SPIChannel.hpp.
 *
 * Usage example:
 *
 * SPIChannel channel(&handler, 10);
 * SPILink spiLink(&channel, GPIOA, GPIO_PIN_4, Mode::POLLING);
 * std::vector<uint8_t> data = {0x01, 0x02, 0x03};
 * HAL_StatusTypeDef status = spiLink.Transmit(data);
 *
 */
class SPILink : public Link{
public:
    SPILink(SPIChannel& channel, GPIO_TypeDef csPort, uint16_t csPin, Mode modeTransmit)
        : spiChannel(channel), csPort(csPort), csPin(csPin), Link(Identity::N_A, modeTransmit) {}

    /*
     * @brief: Allow to transmit data to the e2e connection
     * @param: Buffer to transmit.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef transmit(std::vector<uint8_t> &buffer) override;

    /*
     * @brief: Allow to receive data from the e2e connection
     * @param: Buffer to store received data.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef receive(std::vector<uint8_t> &buffer) override;

    /*
     * @brief: Transmit and receive data from the e2e connection
     * @param: Buffer to transmit.
     * @param: Buffer to store received data.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef transmit_receive(std::vector<uint8_t>& TX_buffer, std::vector<uint8_t>& RX_buffer);

private:
    SPIChannel& spiChannel;
    GPIO_TypeDef csPort;
    uint16_t csPin;
};

#endif //SPILINK_H
