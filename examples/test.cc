/**
 *
 */

// For std::cout
#include <iostream>

// Include for the serial library
#include <serial/Serial.hh>

int main(int argc, char **argv)
{
    // Create a custom POD datatype
    struct MyStruct {
	float one,
	    two_point_one,
	    three,
	    four;
    };
    MyStruct data = { .one=1.0, .two_point_one=2.1, .three=3.0, .four=4.0};

    // Instance the serial interface object
    //
    // @note This will fail if "/dev/ttyACM0" device file does not exist
    //        or if the device file is already open
    serial::Serial serial("/dev/ttyACM0");

    // Create a unique pointer to a thread safe buffer object
    const auto buffer = serial::create_buffer<MyStruct>();

    // Set the personalized data in the buffer
    buffer->setData(data);

    // Write then read the serial port "/dev/ttyACM0"
    serial.write(buffer.get());
    serial.read(buffer.get());

    // Get the data returned from reading the serial buffer
    const auto ret = buffer->getData();

    // Go on about your life <(*.*<)
    std::cout << "one : " << ret.one << std::endl
	      << "two point one : " << ret.two_point_one << std::endl
	      << "three : " << ret.three << std::endl
	      << "four : " << ret.four << std::endl;

    return 0;
}
