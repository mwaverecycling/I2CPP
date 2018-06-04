//
// Created by Scott Fasone on 6/4/18.
//

#ifndef I2CPP_I2CDEVICE_HPP
#define I2CPP_I2CDEVICE_HPP

#include <cstdint>
#include <cstddef>

namespace i2cpp
{
    class I2CDevice
    {
        public:
            I2CDevice(int bus, uint8_t address);
            virtual ~I2CDevice() = default;

        protected:
            std::size_t write_i2c(uint8_t* buffer, std::size_t length);
            std::size_t read_i2c(uint8_t* buffer, std::size_t length);

        private:
            int bus;
            uint8_t address;
    };
}

#endif //I2CPP_I2CDEVICE_HPP
