#include "i2cpp/device.hpp"
#include "i2cpp/i2cpp.hpp"

namespace i2cpp
{
    Device::Device(int bus, uint_fast8_t address): address(address)
    {
        this->fd = I2CPP::open_adapter(bus);
    }
    Device::Device(std::string filename, uint_fast8_t address): address(address)
    {
        this->fd = I2CPP::open_adapter(filename);
    }
    uint_fast8_t Device::get_address() const { return this->address; }

    std::size_t Device::write_i2c(uint_fast8_t* buffer, std::size_t length)
    {
        return I2CPP::write_i2c(this->fd, this->address, buffer, length);
    }
    std::size_t Device::read_i2c(uint_fast8_t* buffer, std::size_t length)
    {
        return I2CPP::read_i2c(this->fd, this->address, buffer, length);
    }
}