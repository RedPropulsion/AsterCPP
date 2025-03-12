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

class SPIChannel {
  public:
  explicit SPIChannel(SPI_HandleTypeDef init, uint32_t sData, uint32_t timeout_tx = 100, uint32_t timeout_rx = 100) :
      handler(std::make_unique<SPI_HandleTypeDef>(init)), timeout_rx(timeout_rx), timeout_tx(timeout_tx), sData(sData) {}

  /*
   * @brief: Allow to transmit in non-blocking and polling mode implementing the two methods given by the HAL.
   *         The protocol use DMA when transmits in non-blocking mode.
   * @param: Buffer to transmit.
   * @param: Specify if non-blocking or polling mode as transmission mode.
   *
   * @retval: HAL status.
   */
  HAL_StatusTypeDef transmit(std::vector<uint8_t> &buffer, Mode transmit_mode) const;

  /*
   * @brief: Allow reception in non-blocking and polling mode implementing the two methods given by the HAL.
   *         The protocol use DMA when receives in non-blocking mode.
   * @param: Buffer to store the data received. The data are stored in chunks of sData size.
   * @param: Specify if non-blocking or polling mode as reception mode.
   *
   * @retval: HAL status.
   */
  HAL_StatusTypeDef receive(std::vector<uint8_t> &buffer, Mode receive_mode);

  HAL_StatusTypeDef transmit_receive(std::vector<uint8_t> &buffer_tx, std::vector<uint8_t> &buffer_rx, Mode transmit_receive_mode);

  private:
  std::unique_ptr<SPI_HandleTypeDef> handler;
  uint32_t timeout_rx;
  uint32_t timeout_tx;
  const uint32_t sData;         //Size of the buffer that store the raw data
};


#endif //REDASTER_SPI_HPP
