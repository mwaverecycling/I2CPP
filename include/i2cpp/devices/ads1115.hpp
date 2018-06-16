/**
 * @file ads1115.hpp
 * @author Scott Fasone
 */

#ifndef I2CPP_ADS1115_HPP
#define I2CPP_ADS1115_HPP

#include <cstdint>
#include <memory>

#include "i2cpp/device.hpp"

namespace i2cpp
{
	/**
	 * ADS1115 : 16-bit Analog-to-Digital Converter.
	 * Reference Documentation: http://www.ti.com/lit/ds/symlink/ads1115.pdf
	 *
	 * This device implementation is currently a work-in-progress
	 * @ingroup Devices
	 */
    class ADS1115 : public Device
    {

        public:
            using SharedPtr = std::shared_ptr<ADS1115>;

            ADS1115(int bus, uint_fast8_t address);

    };
}

#endif //I2CPP_ADS1115_HPP
