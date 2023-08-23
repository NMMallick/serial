#pragma once

#include <mutex>

namespace serial
{
    template<typename T>
    class Buffer
    {
    public:
	Buffer(const Buffer &rhs) = delete;

	// Constructor
	Buffer()
	{
	    static_assert(std::is_trivial<T>::value && std::is_standard_layout<T>::value, "Invalid type for serialization (non-POD type)");
	}

	/**
	 * @brief Returns a copy of the data
	 */
	T get(void);

	/**
	 * @brief Sets the data in the buffer
	 */
	void set(const T data);

    private:
	friend class Serial;

	// We want to be thread safe
	std::mutex mtx;

	// void pointer
	void *buf;
    };

} // namespace serial
