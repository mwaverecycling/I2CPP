#ifndef I2CPP_PCA9555_HPP
#define I2CPP_PCA9555_HPP

#include <cstdint>

#include "i2cpp.hpp"
#include "i2cdevice.hpp"


namespace i2cpp
{
    class PCA9555 : public I2CDevice
    {
        public:
            PCA9555(int bus, uint8_t address);
            PCA9555(int bus, uint8_t address, bool output);
            PCA9555(int bus, uint8_t address, uint16_t config);

            uint16_t read_input();
            bool read_input_pin(uint8_t pin);
            uint16_t read_output();
            bool read_output_pin(uint8_t pin);
            uint16_t read_polarity();
            bool read_polarity_pin(uint8_t pin);
            uint16_t read_config();
            bool read_config_pin(uint8_t pin);

            bool write_output(uint16_t data);
            bool write_output_pin(uint8_t pin, bool value);
            bool write_output_range(uint8_t start_pin, uint8_t end_pin, uint16_t values);
            bool flip_output_pin(uint8_t pin);
            bool write_polarity(uint16_t data);
            bool write_polarity_pin(uint8_t pin, bool value);
            bool write_polarity_range(uint8_t start_pin, uint8_t end_pin, uint16_t values);
            bool flip_polarity_pin(uint8_t pin);
            bool write_config(uint16_t data);
            bool write_config_pin(uint8_t pin, bool value);
            bool write_config_range(uint8_t start_pin, uint8_t end_pin, uint16_t values);
            bool flip_config_pin(uint8_t pin);

        private:
            uint16_t read_register(uint8_t reg);
            bool read_register_pin(uint8_t reg, uint8_t pin);

            bool write_register(uint8_t reg, uint16_t data);
            bool write_register_pin(uint8_t reg, uint8_t pin, bool value);
            bool write_register_range(uint8_t reg, uint8_t start_pin, uint8_t end_pin, uint16_t values);
            bool flip_register_pin(uint8_t reg, uint8_t pin);
    };
}

#endif //I2CPP_PCA9555_HPP
