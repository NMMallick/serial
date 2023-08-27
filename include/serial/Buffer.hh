#pragma once

#include <mutex>
#include <cstring>
#include <memory>

#include <iostream>

namespace serial
{
    template<typename T>
    class Buffer
    {
    public:
	Buffer(const Buffer &rhs) = delete;
	Buffer() : buf(nullptr)
	{
	    static_assert(std::is_trivial<T>::value && std::is_standard_layout<T>::value, "Invalid type for serialization (non-POD type)");
	}

	/**
	 * @brief Returns a copy of the data
	 */
	T getData();

	/**
	 * @brief Sets the data in the buffer
	 */
	void setData(T &data);

	/**
	 * @brief Sets the data in the buffer with an rvalue input
	 */
	void setData(T &&data);

	/**
	 * @brief Returns the size of the buffer
	 */
	size_t size();

    private:
	friend class Serial;

	// We want to be thread safe
	std::mutex mtx;

	// void pointer
	uint8_t *buf;

	// Copy of the data in buffer
	T copy;
    };

    template <typename T>
    T Buffer<T>::getData()
    {
	std::lock_guard<std::mutex> lk(mtx);
	copy  = *(T*)(buf);
	return copy;
    }

    template <typename T>
    void Buffer<T>::setData(T &data)
    {
	copy = data;
    	std::lock_guard<std::mutex> lk(mtx);
    	buf = (uint8_t *)(&copy);
    }

    template <typename T>
    void Buffer<T>::setData(T &&data)
    {
	copy = std::move(data);
	std::lock_guard<std::mutex> lk(mtx);
	buf = (uint8_t *)(&copy);
    }

    template <typename T>
    size_t Buffer<T>::size()
    {
	return sizeof(T);
    }

    template <typename T>
    std::unique_ptr<Buffer<T>>create_buffer()
    {
	return std::move(std::make_unique<Buffer<T>>());
    }

} // namespace serial
