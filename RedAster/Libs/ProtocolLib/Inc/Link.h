//
// Created by danie on 13/12/2024.
//

#ifndef LINK_H
#define LINK_H

#include "SPIChannel.hpp"
#include <cstdint>

class Link{

protected:
    HAL_StatusTypeDef status {HAL_OK};
    Mode modeTransmit {};

public:

    explicit Link(Mode mode_transmit) : modeTransmit(mode_transmit) {}
    virtual ~Link() = default;

    virtual void Transmit() = 0;
    virtual void Receive() = 0;
    virtual void TransmitReceive() = 0;
};

#endif // CONNECTION_H