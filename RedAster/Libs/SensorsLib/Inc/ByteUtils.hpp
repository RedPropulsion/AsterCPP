/*
* ByteUtils.hpp
 *
 *  Created on: Dec 22, 2024
 *       Author: guflie
 *
 * Set of utility function to convert bytes
*/

#ifndef BYTE_UTILS_HPP
#define BYTE_UTILS_HPP

#include <cstdint>
#include <vector>
#include "DataTypes.hpp"

inline uint16_t aggregate8to16(const std::vector<uint8_t>& data) {
    return static_cast<uint16_t>(data[1]) << 8 | data[0];
}

inline uint32_t aggregate16to32(const std::vector<uint16_t>& data) {
    return static_cast<uint32_t>(data[1]) << 16 | data[0];
}

inline uint32_t aggregate8to32(const std::vector<uint8_t>& data) {
    return static_cast<uint32_t>(data[3]) << 24 | static_cast<uint32_t>(data[2]) << 16 | static_cast<uint16_t>(data[1]) << 8 | data[0];
}

inline std::vector<uint8_t> divide16to8(const uint16_t data) {
    return {static_cast<uint8_t>(data & 0x00FF) , static_cast<uint8_t>(data >> 8)};
}

inline std::vector<uint8_t> divide32to8(const uint32_t data) {
    return { static_cast<uint8_t>(data & 0x000000FF)
            , static_cast<uint8_t>(data & 0x0000FF00 >> 8)
            , static_cast<uint8_t>(data & 0x00FF0000 >> 16)
            , static_cast<uint8_t>(data & 0xFF000000 >> 24) };
}

inline std::vector<uint16_t> divide32to16(const uint32_t data) {
    return {static_cast<uint16_t>(data & 0x0000FFFF)
            , static_cast<uint16_t>(data >> 16)};
}

inline std::vector<int16_t> fromVec3ToVector(const vec3s16& data){
    return {data.x, data.y, data.z};
}

inline vec3s16 fromVectorToVec3(const std::vector<uint16_t>& data){
    vec3s16 vec;
    vec.x = data[0];
    vec.y = data[1];
    vec.z = data[2];
    return vec;
}

inline uint16_t wordSwitch(uint16_t word){
    return ((word >> 8) & 0x00FF) | ((word << 8) & 0xFF00);
}

inline uint32_t doubleWordSwitch( uint32_t dword){
    return ((dword & 0xFF000000) >> 24) |
            ((dword & 0x00FF0000) >> 8) |
            ((dword & 0x0000FF00) << 8) |
            ((dword & 0x000000FF) << 24);
}


#endif