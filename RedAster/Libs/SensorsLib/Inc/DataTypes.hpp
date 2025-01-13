/*
* DataTypes.hpp
 *
 *  Created on: Dec 14, 2024
 *       Author: guflie
 *
 *  Based on the C dataTypes.h defined by Danie, set of usefull data type definitions.
*/

#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include "stdint.h"

/*
 * @description 3-D unsigned vector
 * */
typedef struct __attribute__((__packed__)) {
    uint16_t x, y, z;
} vec3u16;

/*
 * @description 3-D signed vector
 * */
typedef struct __attribute__((__packed__)) {
    int16_t x, y, z;
} vec3s16;

/*
 * @description pair accelerometer, gyroscope
 * */
typedef struct {
    vec3s16 acc;
    vec3s16 gyr;
} imu6;

/*
 * @description triplette accelerometer, gyroscope, magnetometer
 * */
typedef struct {
    vec3s16 acc;
    vec3s16 gyr;
    vec3s16 mag;
} imu9;

#endif //DATATYPES_HPP