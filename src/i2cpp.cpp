#include "i2cpp.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


namespace i2cpp
{
    I2CNetwork &I2CNetwork::instance() {
        static I2CNetwork inst;
        return inst;
    }

    int I2CNetwork::open_adapter(int bus) {
        return I2CNetwork::open_adapter("/dev/i2c-" + std::to_string(bus));
    }

    int I2CNetwork::open_adapter(std::string filename) {
        if (instance().fds.find(filename) == instance().fds.end()) {
            int fd = open(filename.c_str(), O_RDWR);
            instance().fds.insert(std::make_pair(filename, fd));
            return fd;
        } else {
            return instance().fds.at(filename);
        }
    }

    std::size_t I2CNetwork::write_i2c(int adapter, int address, uint8_t *buffer, std::size_t length) {
        return instance()._write(adapter, address, buffer, length);
    }

    std::size_t I2CNetwork::read_i2c(int adapter, int address, uint8_t *buffer, std::size_t length) {
        return instance()._read(adapter, address, buffer, length);
    }


    I2CNetwork::I2CNetwork() {}

    I2CNetwork::~I2CNetwork() {
        std::map<std::string, int>::iterator fd_itr;
        for (fd_itr = this->fds.begin(); fd_itr != this->fds.end(); fd_itr++) {
            close(fd_itr->second);
        }
    }

    std::size_t I2CNetwork::_write(int adapter, int address, uint8_t* buffer, std::size_t length) {
        this->_set_address(adapter, address);
        return write(adapter, buffer, length);
    }

    std::size_t I2CNetwork::_read(int adapter, int address, uint8_t* buffer, std::size_t length) {
        this->_set_address(adapter, address);
        return read(adapter, buffer, length);
    }

    void I2CNetwork::_set_address(int adapter, int address) {
        if (this->regs[adapter] != address) {
            if (ioctl(adapter, I2C_SLAVE, address) < 0) {
                this->regs[adapter] = -1;
            } else {
                this->regs[adapter] = address;
            }
        }
    }
}