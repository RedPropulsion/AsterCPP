/*
 * MS56.hpp
 *
 *  Created on: Jan 16, 2025
 *      Author: guflie
 */

#ifndef MS56_HPP
#define MS56_HPP


#include "Sensor.hpp"
#include "ByteUtils.hpp"

#define PIN GPIO_PIN_0

typedef enum {
    CALIBRATION = 0xA2,
    RESET_REG = 0x1E,
    D1 = 0x40,
    D2 = 0x50,
    ADC = 0x00,
} Register;

class MS56 final : public Sensor {
    private:
        // see "PRESSURE AND TEMPERATURE CALCULATION" on datasheet for more details
        uint16_t c1, c2, c3, c4, c5, c6;
        uint32_t d1, d2;
        uint32_t dT, temp;
        uint64_t off, sens;

    protected:
        HAL_StatusTypeDef readData(uint8_t reg, std::vector<uint8_t>& data) const override;
        HAL_StatusTypeDef writeData(uint8_t reg, uint8_t data) override;

    public:
        explicit MS56(Link& link): Sensor(link) { }

        [[nodiscard]] std::map<std::string, std::string> getConfig() const override;
        HAL_StatusTypeDef init() override; // := reset() in old C implementation
        uint8_t selfTest() override;
        HAL_StatusTypeDef readCalibration();
        HAL_StatusTypeDef read(uint32_t *target);

};



#endif //MS56_HPP
