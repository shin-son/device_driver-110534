#include "device_driver.h"
#include "custom_exceptions.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    unsigned char value = m_hardware->read(address);

    for (int i = 1; i < 5; ++i) {
        if (value != m_hardware->read(address)) {
            throw ReadFailException();
        }
    }

    return static_cast<int>(value);
}

void DeviceDriver::write(long address, int data)
{
    if (m_hardware->read(address) != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}