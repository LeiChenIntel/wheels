#include <iostream>

#include "Calculations.h"

int main() {
    std::cout << "CMake Sample 2:" << std::endl;
    std::cout << "Add value : " << add(1.2, 3.4) << std::endl;
    std::cout << "Subtract value: " << subtract(1.2, 3.4) << std::endl;
    std::cout << "Multiple value: " << multiple(1.2, 3.4) << std::endl;
    std::cout << "Divide value: " << divide(1.2, 3.4) << std::endl;
    return 0;
}
