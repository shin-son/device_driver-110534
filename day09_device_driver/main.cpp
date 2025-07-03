#include "gmock/gmock.h"
#include "device_driver.h"
#include "mock_flash_memory_device.h"
#include "custom_exceptions.h"

using namespace testing;

class DeviceDrvierFixture : public Test {
protected:
	DeviceDriver driver;
	MockFlashMemoryDevice mockFlashMemoryDevice;

	DeviceDrvierFixture() : driver(&mockFlashMemoryDevice) {}

public:

private:

};

TEST_F(DeviceDrvierFixture, ReadFromHw) {

	EXPECT_CALL(mockFlashMemoryDevice, read(0xFF))
		.WillRepeatedly(::testing::Return(0xFF));

	EXPECT_EQ(0xFF, driver.read(0xFF));
}

TEST_F(DeviceDrvierFixture, ReadFromHwFailed) {

	EXPECT_CALL(mockFlashMemoryDevice, read(0xFF))
		.WillOnce(::testing::Return(0xFA))
		.WillRepeatedly(::testing::Return(0xFF));

	EXPECT_THROW(driver.read(0xFF), ReadFailException);
}

TEST_F(DeviceDrvierFixture, WriteToHw) {

	EXPECT_CALL(mockFlashMemoryDevice, read(0x30))
		.WillRepeatedly(::testing::Return(0xFF));


	EXPECT_CALL(mockFlashMemoryDevice, write(0x30, 0x55))
		.Times(1);

	driver.write(0x30, 0x55);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}