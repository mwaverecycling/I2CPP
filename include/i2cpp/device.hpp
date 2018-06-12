#ifndef I2CPP_DEVICE_HPP
#define I2CPP_DEVICE_HPP

#include <cstdint>
#include <cstddef>

namespace i2cpp
{
    class Device
    {
        public:
            Device(int bus, uint8_t address);
            virtual ~Device() = default;

            uint_fast8_t get_address() const;

        protected:
            std::size_t write_i2c(uint_fast8_t* buffer, std::size_t length);
            std::size_t read_i2c(uint_fast8_t* buffer, std::size_t length);

        private:
            int bus;
            uint_fast8_t address;
    };
}

#endif //I2CPP_DEVICE_HPP
