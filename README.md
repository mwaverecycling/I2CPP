

# I2CPP

A C++ Library for interfacing with I2C Devices on Linux systems, particularly aimed at microcontrollers like Raspberry Pi and Beaglebone

## Usage Example

```cpp
#include <i2cpp/devices/pca9555.hpp>

int main()
{
    i2cpp::PCA9555 io_exp(1, 0x20);
    io_exp.write_config(0x0000);
    io_exp.write_output_pin(0, true);
}
```
Include the library when you compile
```bash
g++ your_source.cpp -li2cpp
```

## Dependencies

There are no runtime dependencies, but the project requires [CMake](https://cmake.org/download/) to build and [Doxygen](http://www.stack.nl/~dimitri/doxygen/download.html) for documentation

## Building and Installation

Clone the repository, then run CMake and Make in a build directory:
```bash
git clone https://github.com/mwaverecycling/I2CPP
mkdir I2CPP/build
cd I2CPP/build
cmake ..
make
```
The default install location is `/usr/local`. To change this, run cmake with the desired prefix (e.g. `cmake -DCMAKE_INSTALL_PREFIX=/usr ..`)

Install with `sudo make install`

## Documentation

Documentation is hosted on [GitHub Pages](https://mwaverecycling.github.io/I2CPP/), but you can also build documentation from source using Doxygen.

After installing Doxygen, build the documentation from the build directory:
```bash
cd build
make doc
```

