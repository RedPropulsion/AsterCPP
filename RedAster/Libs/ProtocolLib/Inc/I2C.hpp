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

class I2C {
public:
    explicit I2C(I2C_HandleTypeDef init, uint32_t polling_timeout = 0) : handler(std::make_unique<I2C_HandleTypeDef>(init)), polling_t(polling_timeout) {}

    /*
     * @brief: Allow to transmit in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when transmits in non-blocking mode.
     * @param: Specify if SLAVE or MASTER as transmission role.
     * @param: Specify if non-blocking or polling mode as transmission mode.
     * @param: Buffer to transmit. THE FIRST ELEMENT OF THE BUFFER MUST BE THE TARGET DEVICE ADDRESS.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t>& buffer) const;

    /*
     * @brief: Allow reception in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when receives in non-blocking mode.
     * @param: Specify if SLAVE or MASTER as reception role.
     * @param: Specify if non-blocking or polling mode as reception mode.
     * @param: Buffer to store the data received . THE FIRST ELEMENT OF THE BUFFER MUST BE THE TARGET DEVICE ADDRESS.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef Receive(Identity role, Mode receive_mode, std::vector<uint8_t>& buffer);

private:
    std::unique_ptr<I2C_HandleTypeDef> handler;
    uint32_t polling_t;
};

#endif //REDASTER_I2C_HPP
