//
// Created by Alberto Cardini on 16/12/24.
//

#ifndef REDASTER_I2CLINK_HPP
#define REDASTER_I2CLINK_HPP

#include "Link.hpp"
#include "I2CChannel.hpp"

class I2CLink : public Link {
public:
    I2CLink(I2CChannel& channel, uint8_t address, Identity id = Identity::MASTER, Mode mode = Mode::POLLING)
    : i2c_channel(channel), chip_address(address), id(id), Link(mode) {}

    HAL_StatusTypeDef transmit(std::vector<uint8_t>& buffer) override;
    HAL_StatusTypeDef receive(std::vector<uint8_t>& buffer) override;
    void set_target_reg(uint8_t new_reg) { target_reg = new_reg;};

private:
    I2CChannel& i2c_channel;
    Identity id;
    uint8_t chip_address;
    uint8_t target_reg;
};

#endif //REDASTER_I2CLINK_HPP
