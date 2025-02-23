//
// Created by Alberto Cardini on 21/11/24.
//

#ifndef REDASTER_I2C_HPP
#define REDASTER_I2C_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx.h"

#ifdef __cplusplus
}
#endif

#include "Utils.hpp"

class I2CChannel {
public:
    explicit I2CChannel(I2C_HandleTypeDef init, uint32_t sData = 32, uint32_t timeout_tx = 100, uint32_t timeout_rx = 100)
    : handler(std::make_unique<I2C_HandleTypeDef>(init)), sData(sData), timeout_tx(timeout_tx), timeout_rx(timeout_rx) {}

    /*
     * @brief: Allow to transmit in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when transmits in non-blocking mode.
     * @param: Specify if SLAVE or MASTER as transmission role.
     * @param: Specify if non-blocking or polling mode as transmission mode.
     * @param: Buffer to transmit. THE FIRST ELEMENT OF THE BUFFER MUST BE THE TARGET DEVICE REGISTER.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef transmit(uint8_t &chip_address, std::vector<uint8_t>& buffer, Mode transmit_mode = Mode::POLLING, Identity role = Identity::MASTER) const;

    /*
     * @brief: Allow reception in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when receives in non-blocking mode.
     * @param: Specify if SLAVE or MASTER as reception role.
     * @param: Specify if non-blocking or polling mode as reception mode.
     * @param: Buffer to store the data received. THE FIRST ELEMENT OF THE BUFFER MUST BE THE TARGET DEVICE ADDRESS.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef receive(uint8_t &chip_address, std::vector<uint8_t>& buffer, Mode receive_mode = Mode::POLLING, Identity role = Identity::MASTER);

private:
    std::unique_ptr<I2C_HandleTypeDef> handler;
    const uint32_t sData;
    uint32_t timeout_tx;
    uint32_t timeout_rx;
};

#endif //REDASTER_I2C_HPP
