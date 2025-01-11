//
// Created by Alberto Cardini on 16/12/24.
//

#ifndef REDASTER_I2CLINK_HPP
#define REDASTER_I2CLINK_HPP

#include "Link.hpp"
#include "I2CChannel.hpp"

class I2CLink : public Link {
public:
    I2CLink(I2CChannel& channel, uint8_t address, Identity id, Mode mode)
    : i2c_channel(channel), address(address), Link(id, mode) {}

    [[nodiscard]]HAL_StatusTypeDef Transmit(std::vector<uint8_t>& buffer) override;
    [[nodiscard]]HAL_StatusTypeDef Receive(std::vector<uint8_t>& buffer) override;

private:
    I2CChannel& i2c_channel;
    uint8_t address;

    void select_address(std::vector<uint8_t>& buffer) const;
};

#endif //REDASTER_I2CLINK_HPP
