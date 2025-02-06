/*
 * MS56.hpp
 *
 *  Created on: Jan 16, 2025
 *      Author: guflie
 */

#include "MS56.hpp"

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef MS56::readData(const uint8_t reg, std::vector<uint8_t>& data) const {
    std::vector<uint8_t> buffer {reg};
    HAL_StatusTypeDef comStatus = link->Transmit(buffer);
    if (comStatus != HAL_OK) {
        return comStatus;
    }
    return link->Receive(data);
}

/*
 * @brief: see ABC Sensor.hpp for more details
 * */
HAL_StatusTypeDef MS56::writeData(const uint8_t reg, uint8_t data) {
    std::vector<uint8_t> buffer {reg};
    return link->Transmit(buffer);
}

/*
 * @brief: see ABC Sensor.hpp and "FUNCTIONAL DESCRIPTION, SPI MODE" chapter on datasheet for more details
 * */
HAL_StatusTypeDef MS56::init() {
    HAL_GPIO_WritePin(GPIOC, PIN, GPIO_PIN_RESET); // activate MS56 bus interface
    HAL_StatusTypeDef comStatus = writeData(Register::RESET_REG, 0);
    // TODO add delay functionality to Link class
    HAL_Delay(2);
    HAL_GPIO_WritePin(GPIOC, PIN, GPIO_PIN_RESET); // deactivate MS56 bus interface
    return comStatus;
}

/*
 * @brief: read the real compensation coefficients and update the actual configuration, see
 *      "PRESSURE AND TEMPERATURE CALCULATION" on datasheet for more info
 * @return: communication status
 * */
HAL_StatusTypeDef MS56::readCalibration() {
    HAL_StatusTypeDef comStatus = HAL_OK;
    const std::vector<uint16_t> calBackup {c1, c2, c3, c4, c5, c6};

    std::vector<uint8_t> buffer { }; // buffer to act as proxy between object member & SPI vectorized methods
    comStatus = readData(Register::CALIBRATION, buffer);
    if (comStatus != HAL_OK) {
        return comStatus;
    }
    c1 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    comStatus = readData(Register::CALIBRATION+2, buffer);
    if (comStatus != HAL_OK) {
        c1 = calBackup[0];
        return comStatus;
    }
    c2 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    comStatus = readData(Register::CALIBRATION+4, buffer);
    if (comStatus != HAL_OK) {
        c1 = calBackup[0];
        c2 = calBackup[1];
        return comStatus;
    }
    c3 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    comStatus = readData(Register::CALIBRATION+6, buffer);
    if (comStatus != HAL_OK) {
        c1 = calBackup[0];
        c2 = calBackup[1];
        c3 = calBackup[2];
        return comStatus;
    }
    c4 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    comStatus = readData(Register::CALIBRATION+8, buffer);
    if (comStatus != HAL_OK) {
        c1 = calBackup[0];
        c2 = calBackup[1];
        c3 = calBackup[2];
        c4 = calBackup[3];
        return comStatus;
    }
    c5 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    comStatus = readData(Register::CALIBRATION+10, buffer);
    if (comStatus != HAL_OK) {
        c1 = calBackup[0];
        c2 = calBackup[1];
        c3 = calBackup[2];
        c4 = calBackup[3];
        c5 = calBackup[4];
        return comStatus;
    }
    c6 = wordSwitch(aggregate8to16(buffer));
    HAL_Delay(1);

    return comStatus;
}

/*
* @brief: read and compensate data, see "PRESSURE AND TEMPERATURE CALCULATION" on datasheet for more info
* @param "target": variable to put read and compensated data
* @return: compensated data
* */
HAL_StatusTypeDef MS56::read(uint32_t *target) {
    HAL_StatusTypeDef comStatus = HAL_OK;
    const std::vector<uint32_t> dBackup {d1, d2};

    comStatus = writeData(Register::D1, 0);
    if (comStatus != HAL_OK) {
        return comStatus;
    }
    HAL_Delay(5);
    std::vector<uint8_t> buffer { };
    comStatus = readData(Register::ADC, buffer);
    if (comStatus != HAL_OK) {
        return comStatus;
    }
    d1 = doubleWordSwitch(aggregate8to32(buffer)) >> 8;

    comStatus = writeData(Register::D2, 0);
    if (comStatus != HAL_OK) {
        return comStatus;
    }
    HAL_Delay(5);
    comStatus = readData(Register::ADC, buffer);
    if (comStatus != HAL_OK) {
        d1 = dBackup[0];
        return comStatus;
    }
    d2 =  doubleWordSwitch(aggregate8to32(buffer)) >> 8;

    dT = d2 - (static_cast<uint32_t>(c5) << 8);
    temp = 2000 + ((dT*c6) >> 23);
    off = (static_cast<uint32_t>(c2) << 16) + ((c4*dT) >> 7);
    sens = (static_cast<uint32_t>(c1) << 15) + ((c4*dT) >> 8);

    *target = static_cast<uint32_t>((((d1*sens) >> 21) - off) >> 15);
    return comStatus;
}

/*
 * @brief see ABC Sensor.hpp for more details
 * */
std::map<std::string, std::string> MS56::getConfig() const {
    return {
          {"C1", std::to_string(c1)}
        , {"C2", std::to_string(c2)}
        , {"C3", std::to_string(c3)}
        , {"C4", std::to_string(c4)}
        , {"C5", std::to_string(c5)}
        , {"C6", std::to_string(c6)}
        , {"D1", std::to_string(d1)}
        , {"D2", std::to_string(d2)}
        , {"dT", std::to_string(dT)}
        , {"temperature", std::to_string(temp)}
        , {"off", std::to_string(off)}
        , {"sens", std::to_string(sens)}
    };
}

/*
 * @brief not implemented
 * */
uint8_t MS56::selfTest() { return 0x00; }

