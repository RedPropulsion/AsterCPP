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

  explicit UARTChannel(UART_HandleTypeDef init, uint32_t timeout_tx = 100, uint32_t timeout_rx = 10000)
      : handler(std::make_unique<UART_HandleTypeDef>(init)), timeout_tx(timeout_tx), timeout_rx(timeout_rx) {};

  /*
   * @brief: Allow to transmit in non-blocking and polling mode implementing the two methods given by the HAL.
   *         The protocol use DMA when transmits in non-blocking mode.
   * @param: Buffer containing the strings to transmit.
   * @param: Specify if non-blocking or polling mode as transmission mode.
   *
   * @retval: HAL status.
   */
  [[nodiscard]]HAL_StatusTypeDef transmit(std::vector<std::string> &buffer, Mode transmit_mode) const;

  /*
  * @brief: Allow reception in non-blocking and polling mode implementing the two methods given by the HAL.
  *         The protocol use DMA when receives in non-blocking mode.
  * @param: Buffer to store the data received as strings.
  * @param: Specify if non-blocking or polling mode as reception mode.
  *
  * @retval: HAL status.
  */
  [[nodiscard]]HAL_StatusTypeDef receive(std::vector<std::string> &buffer, Mode receive_mode) const;

  private:

  /*
   * Callbacks used by the non-blocking modes of the above methods. The name specifies which event call them as the
   * interrupt raised by the transmit/receive method comes.
   *
  */
  void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

  void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);

  void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

  void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);

  void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

  std::unique_ptr<UART_HandleTypeDef> handler;
  uint32_t timeout_tx;
  uint32_t timeout_rx;
};

#endif //REDASTER_UARTCHANNEL_HPP
