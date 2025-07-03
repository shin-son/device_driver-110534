#pragma once
#include "flash_memory_device.h"
#include "gmock/gmock.h"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};