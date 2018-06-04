#include "i2cdevice.hpp"
#include "i2cpp.hpp"

namespace i2cpp
{
        I2CDevice::I2CDevice(int bus, uint8_t address): bus(bus), address(address) {  }

        std::size_t I2CDevice::write_i2c(uint8_t* buffer, std::size_t length)
        {
            return I2CNetwork::write_i2c(this->bus, this->address, buffer, length);
        }
        std::size_t I2CDevice::read_i2c(uint8_t* buffer, std::size_t length)
        {
            return I2CNetwork::read_i2c(this->bus, this->address, buffer, length);
        }
}