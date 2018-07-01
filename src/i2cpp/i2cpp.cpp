#include "i2cpp/i2cpp.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


namespace i2cpp
{
    I2CPP &I2CPP::instance() {
        static I2CPP inst;
        return inst;
    }

    int I2CPP::open_adapter(int bus) {
        return I2CPP::open_adapter("/dev/i2c-" + std::to_string(bus));
    }

    int I2CPP::open_adapter(std::string filename) {
        return instance()._open_adapter(filename);
    }
    int I2CPP::_open_adapter(std::string filename) {
        if (this->fds.find(filename) == this->fds.end()) {
            int fd = open(filename.c_str(), O_RDWR);
            this->fds.insert(std::make_pair(filename, fd));
            this->fd_mutexes.insert(std::make_pair(fd, new std::mutex()));
            return fd;
        } else {
            return this->fds.at(filename);
        }
    }

    std::size_t I2CPP::write_i2c(int adapter, int address, uint_fast8_t *buffer, std::size_t length) {
        return instance()._write(adapter, address, buffer, length);
    }

    std::size_t I2CPP::read_i2c(int adapter, int address, uint_fast8_t *buffer, std::size_t length) {
        return instance()._read(adapter, address, buffer, length);
    }


    I2CPP::I2CPP() {}

    I2CPP::~I2CPP() {
        std::map<int, std::mutex*>::iterator fdm_itr;
        for (fdm_itr = this->fd_mutexes.begin(); fdm_itr != this->fd_mutexes.end(); fdm_itr++) {
            delete fdm_itr->second;
        }

        std::map<std::string, int>::iterator fd_itr;
        for (fd_itr = this->fds.begin(); fd_itr != this->fds.end(); fd_itr++) {
            close(fd_itr->second);
        }
    }

    /** Instance version of read_i2c() */
    std::size_t I2CPP::_write(int adapter, int address, uint_fast8_t* buffer, std::size_t length) {
        this->fd_mutexes[adapter]->lock();
        this->_set_address(adapter, address);
        this->fd_mutexes[adapter]->unlock();
        return write(adapter, buffer, length);
    }

    /** Instance version of write_i2c() */
    std::size_t I2CPP::_read(int adapter, int address, uint_fast8_t* buffer, std::size_t length) {
        this->fd_mutexes[adapter]->lock();
        this->_set_address(adapter, address);
        this->fd_mutexes[adapter]->unlock();
        return read(adapter, buffer, length);
    }

    /** Conditionally reconfigures ioctl and updates this->regs */
    void I2CPP::_set_address(int adapter, int address) {
        if (this->regs[adapter] != address) {
            if (ioctl(adapter, I2C_SLAVE, address) < 0) {
                this->regs[adapter] = -1;
            } else {
                this->regs[adapter] = address;
            }
        }
    }
}