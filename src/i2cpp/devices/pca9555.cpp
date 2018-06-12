#include "i2cpp/devices/pca9555.hpp"


namespace i2cpp
{
    PCA9555::PCA9555(int bus, uint8_t address) : Device(bus, address) {  }
    PCA9555::PCA9555(int bus, uint8_t address, bool output) : Device(bus, address)
    {
        this->write_config(output ? 0x0000 : 0xffff);
    }
    PCA9555::PCA9555(int bus, uint8_t address, uint16_t config) : Device(bus, address)
    {
        this->write_config(config);
    }
    uint_fast16_t PCA9555::get_state() const { return this->prev_state; }
    void PCA9555::set_state(uint_fast16_t state) { this->prev_state = state; }


    uint16_t PCA9555::read_input() { return this->read_register(0x00); }
    bool PCA9555::read_input_pin(uint8_t pin) { return this->read_register_pin(0x00, pin); }

    uint16_t PCA9555::read_output() { return this->read_register(0x02); }
    bool PCA9555::read_output_pin(uint8_t pin) { return this->read_register_pin(0x02, pin); }

    uint16_t PCA9555::read_polarity() { return this->read_register(0x04); }
    bool PCA9555::read_polarity_pin(uint8_t pin) { return this->read_register_pin(0x04, pin); }

    uint16_t PCA9555::read_config() { return this->read_register(0x06); }
    bool PCA9555::read_config_pin(uint8_t pin) { return this->read_register_pin(0x06, pin); }


    bool PCA9555::write_output(uint16_t data) { return this->write_register(0x02, data); }
    bool PCA9555::write_output_pin(uint8_t pin, bool value) { return this->write_register_pin(0x02, pin, value); }
    bool PCA9555::write_output_range(uint8_t start_pin, uint8_t end_pin, uint16_t values) { return this->write_register_range(0x02, start_pin, end_pin, values); }
    bool PCA9555::flip_output_pin(uint8_t pin) { return this->flip_register_pin(0x02, pin); }

    bool PCA9555::write_polarity(uint16_t data) { return this->write_register(0x04, data); }
    bool PCA9555::write_polarity_pin(uint8_t pin, bool value) { return this->write_register_pin(0x04, pin, value); }
    bool PCA9555::write_polarity_range(uint8_t start_pin, uint8_t end_pin, uint16_t values) { return this->write_register_range(0x04, start_pin, end_pin, values); }
    bool PCA9555::flip_polarity_pin(uint8_t pin) { return this->flip_register_pin(0x04, pin); }

    bool PCA9555::write_config(uint16_t data) { return this->write_register(0x06, data); }
    bool PCA9555::write_config_pin(uint8_t pin, bool value) { return this->write_register_pin(0x06, pin, value); }
    bool PCA9555::write_config_range(uint8_t start_pin, uint8_t end_pin, uint16_t values) { return this->write_register_range(0x06, start_pin, end_pin, values); }
    bool PCA9555::flip_config_pin(uint8_t pin) { return this->flip_register_pin(0x06, pin); }



    uint16_t PCA9555::read_register(uint8_t reg)
    {
        uint8_t buffer[3] = { reg, 0x00, 0x00 };
        this->read_i2c(buffer, 3);
        return uint16_t((buffer[1] << 8) | buffer[0]);
    }
    bool PCA9555::read_register_pin(uint8_t reg, uint8_t pin)
    {
        uint16_t pins = this->read_register(reg);
        return (pins & (1 << pin)) > 0;
    }

    bool PCA9555::write_register(uint8_t reg, uint16_t data)
    {
        uint8_t buffer[3] = { reg, uint8_t(data & 0xff), uint8_t(data >> 8) };
        return this->write_i2c(buffer, 3) == 3;
    }
    bool PCA9555::write_register_pin(uint8_t reg, uint8_t pin, bool value)
    {
        uint16_t old = this->read_register(reg);
        if(value) {
            old |= (1 << pin);
        } else {
            old &= ~(1 << pin);
        }
        return this->write_register(reg, old);
    }
    bool PCA9555::write_register_range(uint8_t reg, uint8_t start_pin, uint8_t end_pin, uint16_t values)
    {
        uint16_t old = this->read_register(reg);
        for(uint8_t i = start_pin; i < end_pin; i++)
        {
            if((values & (1 << (i - start_pin))) > 0) {
                old |= (1 << i);
            } else {
                old &= ~(1 << i);
            }
        }
        return this->write_register(reg, old);
    }
    bool PCA9555::flip_register_pin(uint8_t reg, uint8_t pin)
    {
        uint16_t old = this->read_register(reg);
        if((old & (1 << pin)) == 0) {
            old |= (1 << pin);
        } else {
            old &= ~(1 << pin);
        }
        return this->write_register(reg, old);
    }
}