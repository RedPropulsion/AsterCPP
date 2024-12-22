//
// Created by Alberto Cardini on 16/12/24.
//

#ifndef REDASTER_UARTCHANNEL_HPP
#define REDASTER_UARTCHANNEL_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx.h"

#ifdef __cplusplus
}
#endif

#include "Utils.hpp"

class UARTChannel {
public:

    explicit UARTChannel(UART_HandleTypeDef init, uint32_t polling_timeout = 0)
    : handler(std::make_unique<UART_HandleTypeDef>(init)), polling_timeout(polling_timeout) {};

    [[nodiscard]]HAL_StatusTypeDef Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t>& buffer) const;
    [[nodiscard]]HAL_StatusTypeDef Receive(Identity role, Mode transmit_mode, std::vector<uint8_t>& buffer) const;

private:
    std::unique_ptr<UART_HandleTypeDef> handler;
    uint32_t polling_timeout;
};

#endif //REDASTER_UARTCHANNEL_HPP
