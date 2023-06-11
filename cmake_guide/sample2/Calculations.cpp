#include "Calculations.h"

#include <iostream>

float add(float value1, float value2) {
    return value1 + value2;
}

float subtract(float value1, float value2) {
    return value1 - value2;
}

float multiple(float value1, float value2) {
    return value1 * value2;
}

float divide(float value1, float value2) {
    if (value2 == 0.0) {
        std::cout << "Illegal input. Divide a zero." << std::endl;
        return 0;
    }
    return value1 / value2;
}
