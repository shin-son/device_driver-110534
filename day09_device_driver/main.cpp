#include "gmock/gmock.h"
#include "device_driver.h"
#include "mock_flash_memory_device.h"
#include "custom_exceptions.h"

TEST(DeviceDriver, ReadFromHw) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read(0xFF))
		.WillRepeatedly(::testing::Return(0xFF));

	DeviceDriver driver(&mockFlashMemoryDevice);
	int data = driver.read(0xFF);
	EXPECT_EQ(0xFF, data);
}

TEST(DeviceDriver, ReadFromHwFailed) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read(0xFF))
		.WillOnce(::testing::Return(0xFA))
		.WillRepeatedly(::testing::Return(0xFF));

	DeviceDriver driver(&mockFlashMemoryDevice);
	EXPECT_THROW(driver.read(0xFF), ReadFailException);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}