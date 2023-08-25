#include <iostream>

#include <serial/Serial.hh>

int main(int argc, char **argv)
{
    struct MyStruct {
	float one,
	    two,
	    three,
	    four;
    };

    MyStruct data = { .one=1.0, .two=2.1, .three=3.0, .four=4.0};

    // Instance the serial interface object
    serial::Serial serial("/dev/ttyACM0");

    // Create a unique pointer to a thread safe buffer object
    const auto buffer = serial::create_buffer<MyStruct>();

    // Set the personalized data in the buffer
    buffer->setData(data);

    // Write then read the serial port "/dev/ttyACM0"
    serial.write(buffer.get());
    serial.read(buffer.get());

    // Get the data returned from read()
    const auto ret = buffer->getData();

    // Go on about your life <(*.*<)
    std::cout << "one : " << ret.one << std::endl
	      << "two point one : " << ret.two << std::endl
	      << "three : " << ret.three << std::endl
	      << "four : " << ret.four << std::endl;

    return 0;
}
