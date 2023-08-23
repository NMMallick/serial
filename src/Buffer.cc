#include <serial/Buffer.hh>

namespace serial
{
    template<typename T>
    T Buffer<T>::get(void)
    {
	T dest;

	std::lock_guard<std::mutex>(mtx);

	memcpy(&dest, buf, sizeof(T));
	return dest;
    }

    template<typename T>
    void Buffer<T>::set(const T data)
    {
    	std::lock_guard<std::mutex>(mtx);
    	buf = reinterpret_cast<void *>(&data);
    }
}
