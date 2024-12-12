//
// Created by Alberto Cardini on 27/11/24.
//

#ifndef REDASTER_UTILS_HPP
#define REDASTER_UTILS_HPP

#include <iostream>
#include <vector>
#include <memory>

enum class Mode {
    NON_BLOCKING, POLLING
}typedef Mode;

enum class Identity {
    MASTER, SLAVE, N_A
}typedef Identity;

template <typename T>
T* get_valid_ptr(std::vector<T>& vec){
    if (vec.empty()){
        throw std::runtime_error("NULL pointer to data vector");
    }
    return vec.data();
}

template <typename T>
int size_in_byte(std::vector<T>& vec){
    return vec.capacity() * sizeof(T);
}

#endif //REDASTER_UTILS_HPP
