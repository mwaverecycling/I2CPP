/**
 * @file i2cpp.hpp
 * @author Scott Fasone
 */

#ifndef I2C_LIBRARY_H
#define I2C_LIBRARY_H

#include <cstdint>
#include <string>
#include <map>

namespace i2cpp
{
    /**
     * @brief Manager for all I2C transactions.
     * A singleton class for reading from and writing to a given I2C adapter.
     * Keeps track of all currently open interfaces to reduce redundency and release resources safely.
     *
     * Most users will not use this static API, instead prefering to use an I2C Device object
     * @see i2cpp::Device
     */
    class I2CPP
    {
        public:
            // Make sure only a single instance can be made.
            I2CPP(I2CPP const&) = delete;
            void operator=(I2CPP const&) = delete;

            /**
             * Open a given I2C adapter by number.
             * Just a shortcut to open_adapter("/dev/i2c-" + bus).
             * @see open_adapter(std::string)
             *
             * @param bus I2C Bus Number
             * @returns File Descriptor for I2C device file
             */
            static int open_adapter(int bus);
            /**
             * Open a given I2C adapter by filename.
             * Opens a passed in device file path for reading and writing.
             * @see open_adapter(int)
             *
             * @param filename Path to I2C device file
             * @returns File Descriptor for I2C device file
             */
            static int open_adapter(std::string filename);

            /**
             * Read bytes from I2C to a buffer.
             * Given an adapter file descriptor and address on the I2C bus, reads bytes into the given buffer
             *
             * @param adapter File Descriptor of the desired I2C Adapter
             * @param address Address of the I2C device on the bus
             * @param[in] buffer Array of bytes to write to from the bus
             * @param length Length of buffer
             */
            static std::size_t read_i2c(int adapter, int address, uint_fast8_t* buffer, std::size_t length);
            /**
             * Write a buffer of bytes to I2C.
             * Given an adapter file descriptor and address on the I2C bus, writes the given buffer to it
             *
             * @param adapter File Descriptor of the desired I2C Adapter
             * @param address Address of the I2C device on the bus
             * @param[out] buffer Array of bytes to write to the bus
             * @param length Length of buffer
             */
            static std::size_t write_i2c(int adapter, int address, uint_fast8_t* buffer, std::size_t length);

        private:
            I2CPP();
            ~I2CPP();
            static I2CPP& instance();

            /**
             * Map of currently allocated File Descriptors
             * Used to ensure only one instance of each file descriptor is used,
             * then used to free each allocated fd
             */
            std::map<std::string, int> fds;
            /**
             * Map of each File Descriptor's currently set I2C address.
             * Since ioctl is wierd, we have to reconfigure IO each time we want to send to a different address.
             * This map keeps track of the previously addressed device to avoid resetting every time.
             */
            std::map<int, uint_fast8_t> regs;

            std::size_t _read(int adapter, int address, uint_fast8_t* buffer, std::size_t length);
            std::size_t _write(int adapter, int address, uint_fast8_t* buffer, std::size_t length);
            void _set_address(int bus, int address);
    };
}

#endif