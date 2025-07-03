#include "gmock/gmock.h"
#include "device_driver.h"
#include "mock_flash_memory_device.h"
#include "custom_exceptions.h"

using namespace testing;

class DeviceDrvierFixture : public Test {
protected:
	MockFlashMemoryDevice mockFlashMemoryDevice;
	DeviceDriver driver;

	DeviceDrvierFixture() : driver(&mockFlashMemoryDevice) {}

public:

private:

};

TEST_F(DeviceDrvierFixture, ReadFromHw) {

	EXPECT_CALL(mockFlashMemoryDevice, read(0xFF))
		.Times(5)
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
		.WillOnce(::testing::Return(0xFF));


	EXPECT_CALL(mockFlashMemoryDevice, write(0x30, 0x55))
		.Times(1);

	driver.write(0x30, 0x55);
}

TEST_F(DeviceDrvierFixture, WriteToHwFailed) {

	EXPECT_CALL(mockFlashMemoryDevice, read(0x31))
		.WillRepeatedly(::testing::Return(0x20));


	EXPECT_CALL(mockFlashMemoryDevice, write(_, _))
		.Times(0);

	EXPECT_THROW(driver.write(0x31, 0x55), WriteFailException);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}