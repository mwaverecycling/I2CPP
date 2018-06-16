/**
 * @file device.hpp
 * @author Scott Fasone
 */

#ifndef I2CPP_DEVICE_HPP
#define I2CPP_DEVICE_HPP

#include <cstdint>
#include <cstddef>
#include <string>

/**
 * @defgroup Devices
 * Included I2C Devices and their parent class, i2cpp::Device
 */
namespace i2cpp
{
    /**
     * @brief Parent interface for I2C Device Classes.
     * @ingroup Devices
     * Provides shorthand methods for reading from and writing to I2C on the device's configured bus and address
     */
    class Device
    {
        public:
            /**
             * Construct a device based on its network's bus number.
             * Given a bus number, fetches and stores the relevant file descriptor from i2cpp::I2CPP.
             * @see i2cpp::I2CPP::open_adapter(int)
             * @see Device(std::string, uint_fast8_t)
             *
             * @param bus I2C interface number to use
             * @param address Address of the device on the I2C network
             */
            Device(int bus, uint_fast8_t address);
            /**
             * Construct a device based on its network's device file.
             * Given a device filename, fetches and stores the relevant file descriptor from i2cpp::I2CPP.
             * @see i2cpp::I2CPP::open_adapter(std::string)
             *
             * @param filename Path to I2C device file
             * @param address Address of the device on the I2C network
             */
            Device(std::string filename, uint_fast8_t address);
            virtual ~Device() = default;
            /**
             * Get this device's address on the I2C network.
             * @returns Device's I2C address
             */
            uint_fast8_t get_address() const;

        protected:
            /**
             * Read from the I2C network using this device's bus and address
             * @see i2cpp::I2CPP::read_i2c()
             *
             * @param[in] buffer Array of bytes to write to from the bus
             * @param length Length of buffer
             * @returns Number of byte read into buffer
             */
            std::size_t read_i2c(uint_fast8_t* buffer, std::size_t length);
            /**
             * Write to the I2C network using this device's bus and address
             * @see i2cpp::I2CPP::write_i2c()
             *
             * @param[out] buffer Array of bytes to write to the bus
             * @param length Length of buffer
             * @returns Number of bytes written to the bus
             */
            std::size_t write_i2c(uint_fast8_t* buffer, std::size_t length);

        private:
            /** File Descriptor for this device's I2C interface */
            int fd;
            /** Address of this device on the I2C bus */
            uint_fast8_t address;
    };
}
/** @} */

#endif //I2CPP_DEVICE_HPP
