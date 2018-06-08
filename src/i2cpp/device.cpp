#include "i2cpp/device.hpp"
#include "i2cpp/i2cpp.hpp"

namespace i2cpp
{
        Device::Device(int bus, uint8_t address): bus(bus), address(address) {  }

        std::size_t Device::write_i2c(uint8_t* buffer, std::size_t length)
        {
            return I2CPP::write_i2c(this->bus, this->address, buffer, length);
        }
        std::size_t Device::read_i2c(uint8_t* buffer, std::size_t length)
        {
            return I2CPP::read_i2c(this->bus, this->address, buffer, length);
        }
}