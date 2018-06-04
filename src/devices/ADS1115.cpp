//
// Created by Scott Fasone on 6/4/18.
//

#include "devices/ADS1115.hpp"

namespace i2cpp
{
    ADS1115::ADS1115(int bus, uint8_t address) : I2CDevice(bus, address)
    {

    }
}