#include <catch2/catch_test_macros.hpp>

#include <serial/Serial.hh>
#include <cmath>
#include <iostream>

TEST_CASE( "Test Construction", "[Constructor]")
{
    // These required ttyUSB20 and ttyUSB21 to be
    // available device files or simlinks
    serial::Serial usb_20("/dev/ttyUSB20");
    serial::Serial usb_21("/dev/ttyUSB21");
}

TEST_CASE( "Create Buffer <Types>" , "[Buffer<uint8_t>]")
{
    const auto buffer = serial::create_buffer<uint8_t>();

    for (uint8_t i = 0; i < pow(2, sizeof(uint8_t)*8)-1; i++)
    {
	buffer->setData(i);
	REQUIRE(buffer->getData() == i);
	REQUIRE(buffer->size() == sizeof(uint8_t));

	buffer->setData(std::move(i));
	REQUIRE(buffer->getData() == i);
	REQUIRE(buffer->size() == sizeof(uint8_t));
    }
}

TEST_CASE( "Create Buffer <Types>" , "[Buffer<uint16_t>]")
{
    const auto buffer = serial::create_buffer<uint16_t>();

    for (size_t i = 0; i < pow(2, sizeof(uint16_t)*8); i++)
    {
	buffer->setData(i);
	REQUIRE(buffer->getData() == i);
	REQUIRE(buffer->size() == sizeof(uint16_t));

	buffer->setData(std::move(i));
	REQUIRE(buffer->getData() == i);
	REQUIRE(buffer->size() == sizeof(uint16_t));
    }
}
