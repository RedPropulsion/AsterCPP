//
// Created by Alberto Cardini on 21/11/24.
//

#ifndef REDASTER_SPI_HPP
#define REDASTER_SPI_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx.h"

#ifdef __cplusplus
}
#endif

#include "Utils.hpp"

class SPI {
public:
    explicit SPI(SPI_HandleTypeDef init, uint32_t polling_timeout = 0) : handler(std::make_unique<SPI_HandleTypeDef>(init)), polling_t(polling_timeout) {}

    /*
     * @brief: Allow to transmit in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when transmits in non-blocking mode.
     * @param: This param MUST be set as N_A, otherwise throw an exception.
     * @param: Specify if non-blocking or polling mode as transmission mode.
     * @param: Buffer to transmit.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef Transmit(Identity role, Mode transmit_mode, std::vector<uint8_t>& buffer) const;

    /*
     * @brief: Allow reception in non-blocking and polling mode implementing the two methods given by the HAL.
     *         The protocol use DMA when receives in non-blocking mode.
     * @param: This param MUST be set as N_A, otherwise throw an exception.
     * @param: Specify if non-blocking or polling mode as reception mode.
     * @param: Buffer to store the data received.
     *
     * @retval: HAL status.
     */
    HAL_StatusTypeDef Receive(Identity role, Mode receive_mode, std::vector<uint8_t>& buffer);

private:
    std::unique_ptr<SPI_HandleTypeDef> handler;
    uint32_t polling_t;
};


#endif //REDASTER_SPI_HPP
