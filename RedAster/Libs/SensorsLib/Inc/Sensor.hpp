/*
* Sensor.h
 *
 *  Created on: Nov 18, 2024
 *      Author: danie
 *      Contributors: guflie
 *
 *  This abstract class defines the basic functionalities and attributes that the representation of a sensor must have.
 *  A class that implements this abstract class will be the abstract representation of that sensor on the
 *  microcontroller, and acts as middleware between the physical sensor and the logic algorithm.
 */

#ifndef SENSORSLIB_SENSOR_H_
#define SENSORSLIB_SENSOR_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "../../ProtocolLib/Inc/Link.hpp"

class Sensor {

protected:
    Link& link;

    /*
     * @brief: read/write some data from/on the physical sensor, all communications with it should be implemented with
     *          those methods, which should be written for the specific sensor and its communication necessities
     *
     * @param reg: specifies the target register
     * @param &data: where to put the read data
     * @param data: data to write
     * @return: status of the communication, allows errors check
     * */
    [[nodiscard]] virtual HAL_StatusTypeDef readData(uint8_t reg, std::vector<uint8_t>& data) const = 0;
    virtual HAL_StatusTypeDef writeData(uint8_t reg, uint8_t data) = 0;

public:
    explicit Sensor(Link& link): link(link) { }
    virtual ~Sensor() = default;

    /*
     * @brief: runs the actual configuration of the sensor's representation
     * @return: dict that contains configuration description
     * */
    [[nodiscard]] virtual std::map<std::string, std::string> getConfig() const = 0;

    /*
     * @brief: runs the steps for sensor initialization phase
     * @return: status of the communication, allows errors check
     * */
    virtual HAL_StatusTypeDef init() = 0;

    /*
     * @brief: runs the self-test procedure, if expected (otherwise use return 0;)
     * @return: selftest result
     * */
    virtual uint8_t selfTest() = 0;
};

#endif /* SENSORSLIB_SENSOR_H_ */
