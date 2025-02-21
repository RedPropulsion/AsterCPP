//
// Created by danie on 13/12/2024.
//

#ifndef LINK_HPP
#define LINK_HPP

#include "SPIChannel.hpp"
#include <cstdint>

class Link{

protected:
    HAL_StatusTypeDef status {HAL_OK};
    Identity id;
    Mode modeTransmit;

public:

    explicit Link(Identity id, Mode mode_transmit) : id(id), modeTransmit(mode_transmit) {}
    virtual ~Link() = default;

    virtual HAL_StatusTypeDef Transmit(std::vector<uint8_t>& buffer) = 0;
    virtual HAL_StatusTypeDef Receive(std::vector<uint8_t>& buffer) = 0;
};

#endif // LINK_HPP