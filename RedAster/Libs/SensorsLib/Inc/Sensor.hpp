/*
* Sensor.h
 *
 *  Created on: Nov 18, 2024
 *      Author: danie
 *      Contributors: guflie
 */

#ifndef SENSORSLIB_SENSOR_H_
#define SENSORSLIB_SENSOR_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "../../ProtocolLib/Inc/Link.hpp"

class Sensor {

public:
    virtual ~Sensor() = default;
    [[nodiscard]] virtual HAL_StatusTypeDef readData(uint8_t reg, std::vector<uint8_t>& data) const = 0;
    virtual HAL_StatusTypeDef writeData(uint8_t reg, uint8_t data) = 0;
    [[nodiscard]] virtual std::map<std::string, std::string>& getConfig() const = 0;
    virtual void init() = 0;
    virtual void selfTest() = 0;

};

#endif /* SENSORSLIB_SENSOR_H_ */
