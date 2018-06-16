/**
 * @file pca9555.hpp
 * @author Scott Fasone
 */

#ifndef I2CPP_PCA9555_HPP
#define I2CPP_PCA9555_HPP

#include <cstdint>
#include <memory>

#include "i2cpp/i2cpp.hpp"
#include "i2cpp/device.hpp"


namespace i2cpp
{
    /**
     * PCA9555 : 16-bit I/O Expander.
     * Reference Documentation: http://www.ti.com/lit/ds/symlink/pca9555.pdf
     *
     * All 16-bit parameters are treated as bitmasks for pins on the PCA9555 board.
     * The bitmask maps to pins in a big-endian format as follows:
     * <pre>
     * |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
     * | bit |  15 |  14 |  13 |  12 |  11 |  10 |   9 |   8 |   7 |   6 |   5 |   4 |   3 |   2 |   1 |   0 |
     * | pin | 1.7 | 1.6 | 1.5 | 1.4 | 1.3 | 1.2 | 1.1 | 1.0 | 0.7 | 0.6 | 0.5 | 0.4 | 0.3 | 0.2 | 0.1 | 0.0 |
     * |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
     * </pre>
     * @ingroup Devices
     */
    class PCA9555 : public Device
    {
        public:
            /** Convenience name to get a Shared Pointer */
            using SharedPtr = std::shared_ptr<PCA9555>;

            /**
             * Construct a PCA9555 with the given bus and address.
             * @param bus I2C interface number to use
             * @param address Address of the device on the I2C network
             */
            PCA9555(int bus, uint_fast8_t address);

            /**
             * Get a saved state from the PCA9555 object.
             * Returns a 16-bit value previously set by set_state().
             * @note This class never changes its state variable, it is read and written exclusively by the caller
             *
             * @returns Saved state of the PCA9555
             */
            uint_fast16_t get_state() const;
            /**
             * Set tbe saved state of the PCA9555 object.
             * @note This class never changes its state variable, it is read and written exclusively by the caller
             *
             * @param state The new 16-bit state variable
             */
            void set_state(uint_fast16_t state);

            /** @name Read data from the PCA9555 board */
            //@{
            /**
             * Read the 16-bit input from the PCA9555 board.
             * @returns The read input from the board
             */
            uint_fast16_t read_input();
            /**
             * Read a single input pin from the PCA9555 board.
             * @param pin The pin number to read from
             * @returns True if the pin is powered, false otherwise
             */
            bool read_input_pin(uint_fast8_t pin);
            /**
             * Read the 16-bit output from the PCA9555 board.
             * This returns what the board has stored as output.
             * @note Only useful for pins in output mode
             *
             * @returns The read output from the board
             */
            uint_fast16_t read_output();
            /**
             * Read a single pin's output from the PCA9555 board.
             * @note Only useful for pins in output mode
             *
             * @param pin The pin number to read from
             * @returns True if the pin is powered, false otherwise
             */
            bool read_output_pin(uint_fast8_t pin);
            /**
             * Read the 16-bit polarity inversion register from the PCA9555 board.
             * This returns what the board has stored as polarity.
             * @note Only useful for pins in input mode
             *
             * @returns The read polarity from the board
             */
            uint_fast16_t read_polarity();
            /**
             * Read a single pin's polarity inversion state from the PCA9555 board.
             * @note Only useful for pins in input mode
             *
             * @param pin The pin number to read from
             * @returns True if the pin's polarity is inverted, false otherwise
             */
            bool read_polarity_pin(uint_fast8_t pin);
            /**
             * Read the 16-bit configuration of the PCA9555 board.
             * @returns The current configuration of the board
             */
            uint_fast16_t read_config();
            /**
             * Read a single pin's configuration from the PCA9555 board.
             * @param pin The pin number to read from
             * @returns True if the current pin is configured as input, false for output
             */
            bool read_config_pin(uint_fast8_t pin);
            //@}

            /**
             * @name Write data to the PCA9555 board
             * @returns True if successful, false otherwise
             */
            //@{
            /**
             * Write 16-bits to the board's output register.
             * @param data Bitmask to write to the output register
             */
            bool write_output(uint_fast16_t data);
            /**
             * Write a single output pin on the board.
             * @param pin The pin number to write
             * @param value Power if true, ground otherwise
             */
            bool write_output_pin(uint_fast8_t pin, bool value);
            /**
             * Write a range of output pins to the board.
             * The given bitmask is applied with the Least Significant Bit mapped to start_pin.
             * @param start_pin Start of the range, inclusive
             * @param end_pin End of the range, exclusive
             * @param values Bitmask to write to the pins
             */
            bool write_output_range(uint_fast8_t start_pin, uint_fast8_t end_pin, uint_fast16_t values);
            /**
             * Toggle an output pin's state.
             * @param pin The pin number to toggle
             */
            bool flip_output_pin(uint_fast8_t pin);
            /**
             * Write 16-bits to the board's polarity inversion register.
             * @note Only useful for pins in input mode
             *
             * @param data Bitmask to write to the polarity inversion register
             */
            bool write_polarity(uint_fast16_t data);
            /**
             * Write a single pin's polarity to the board.
             * @note Only useful for pins in input mode
             *
             * @param pin The pin number to write
             * @param value Inverse Polarity if true, normal operation otherwise
             */
            bool write_polarity_pin(uint_fast8_t pin, bool value);
            /**
             * Write a range of polarities to the board.
             * The given bitmask is applied with the Least Significant Bit mapped to start_pin.
             * @note Only useful for pins in input mode
             *
             * @param start_pin Start of the range, inclusive
             * @param end_pin End of the range, exclusive
             * @param values Bitmask to write to the polarity inversion register
             */
            bool write_polarity_range(uint_fast8_t start_pin, uint_fast8_t end_pin, uint_fast16_t values);
            /**
             * Toggle an input pin's polarity.
             * @note Only useful for pins in input mode
             *
             * @param pin The pin number to toggle
             */
            bool flip_polarity_pin(uint_fast8_t pin);
            /**
             * Write 16-bits to the board's configuration register.
             * 0's are output mode, 1's are input mode.
             * @param data Bitmask to write to the configuration register
             */
            bool write_config(uint_fast16_t data);
            /**
             * Write a single pin's configuration to the board.
             * @param pin The pin number to configure
             * @param value Input Mode if true, Output Mode otherwise
             */
            bool write_config_pin(uint_fast8_t pin, bool value);
            /**
             * Write a range of configurations to the board.
             * The given bitmask is applied with the Least Significant Bit mapped to start_pin.
             * 0's are output mode, 1's are input mode.
             * @param start_pin Start of the range, inclusive
             * @param end_pin End of the range, exclusive
             * @param values Bitmask to write to the polarity inversion register
             */
            bool write_config_range(uint_fast8_t start_pin, uint_fast8_t end_pin, uint_fast16_t values);
            /**
             * Toggle a pin's configuration bit.
             * @param pin The pin number to toggle
             */
            bool flip_config_pin(uint_fast8_t pin);
            //@}

        private:
            uint_fast16_t prev_state;
            uint_fast16_t read_register(uint_fast8_t reg);
            bool read_register_pin(uint_fast8_t reg, uint_fast8_t pin);

            bool write_register(uint_fast8_t reg, uint_fast16_t data);
            bool write_register_pin(uint_fast8_t reg, uint_fast8_t pin, bool value);
            bool write_register_range(uint_fast8_t reg, uint_fast8_t start_pin, uint_fast8_t end_pin, uint_fast16_t values);
            bool flip_register_pin(uint_fast8_t reg, uint_fast8_t pin);
    };
}

#endif //I2CPP_PCA9555_HPP
