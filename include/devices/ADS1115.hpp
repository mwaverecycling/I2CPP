#ifndef I2CPP_ADS1115_HPP
#define I2CPP_ADS1115_HPP

#include <cstdint>

#include "i2cdevice.hpp"

namespace i2cpp
{
    class ADS1115 : public I2CDevice
    {
        public:
            ADS1115(int bus, uint8_t address);

    };
}

#endif //I2CPP_ADS1115_HPP
