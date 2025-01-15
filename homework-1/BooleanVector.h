#pragma once
#include <iostream>

namespace Constants 
{
constexpr unsigned GROWTH_FACTOR = 2;		
const unsigned ELEMENTS_IN_BUCKET = sizeof(uint8_t) * 8;
}

class BooleanVector
{
private:
	size_t size = 0;
	size_t capacity = 0;

	uint8_t* buckets = nullptr;

	void free();
	void copyFrom(const BooleanVector& other);
	void moveFrom(BooleanVector&& other);

	unsigned getBucketIndex(unsigned num) const;
	unsigned getBitIndex(unsigned num) const;

	size_t calculateCapacity() const;

	//needed for non-const operator[]
	class BitWrapper 
	{
		friend class BooleanVector;
	private:
		uint8_t& byte;
		unsigned bitIndex;
		BitWrapper(uint8_t& byte, unsigned bitIndex) : byte(byte), bitIndex(bitIndex) {}

	public:
		operator bool() const 
		{
			return (byte & (1 << bitIndex));
		}

		BitWrapper& operator=(bool value) 
		{
			if (value)
				byte |= (1 << bitIndex);
			else
				byte &= ~(1 << bitIndex);
			return *this;
		}
	};
public:
	BooleanVector() = default;
	explicit BooleanVector(size_t count);
	BooleanVector(size_t count, bool initialValue);

	BooleanVector(const BooleanVector& other);
	BooleanVector(BooleanVector&& other) noexcept;

	BooleanVector& operator=(const BooleanVector& other);
	BooleanVector& operator=(BooleanVector&& other) noexcept;

	~BooleanVector();

	class vector_iterator;

	void resize(size_t n);

	void push_back(bool value);
	void pop_back();
	void insert(vector_iterator iter, bool value);
	void remove(vector_iterator iter);
	void pop_front();

	BitWrapper operator[](size_t index);

	const bool& operator[](size_t index) const;

class vector_iterator 
{
	friend class BooleanVector;
private:
	BooleanVector* vector;
	//this bitPosition is not the index in the bucket, but in the whole buckets array
	size_t bitPosition;

public:
	//passing only vector and not position, for simpler user interface
	vector_iterator(BooleanVector* vector) : vector(vector), bitPosition(0) {}

	vector_iterator& operator++()
	{
		bitPosition++;
		return *this;
	}

	vector_iterator operator++(int) 
	{
		vector_iterator it = *this;
		++(*this);
		return it;
	}

	vector_iterator& operator--() 
	{
		bitPosition--;
		return *this;
	}

	vector_iterator operator--(int) 
	{
		vector_iterator it = *this;
		--(*this);
		return it;
	}

	bool operator* () const 
	{
		unsigned bucketIndex = bitPosition / Constants::ELEMENTS_IN_BUCKET;
		unsigned bitIndex = bitPosition % Constants::ELEMENTS_IN_BUCKET;

		return (*vector).buckets[bucketIndex] & (1 << bitIndex);
	}

	bool operator==(const vector_iterator& other) const 
	{
		return (bitPosition == other.bitPosition) && (vector == other.vector);
	}

	bool operator!=(const vector_iterator& other) const 
	{
		return !(*this == other);
	}
};

class const_vector_iterator 
{
	friend class BooleanVector;
private:
	const BooleanVector* vector;
	//this bitPosition is not the index in the bucket, but in the whole buckets array
	size_t bitPosition;

public:
	const_vector_iterator(BooleanVector* vector, size_t bitIndex) : vector(vector), bitPosition(bitIndex) {}

	const bool operator*() const 
	{
		unsigned bucketIndex = bitPosition / Constants::ELEMENTS_IN_BUCKET;
		unsigned bitIndex = bitPosition % Constants::ELEMENTS_IN_BUCKET;

		return (*vector).buckets[bucketIndex] & (1 << bitIndex);
	}

	bool operator==(const const_vector_iterator& other) const 
	{
		return (bitPosition == other.bitPosition) && (vector == other.vector);
	}

	bool operator!=(const const_vector_iterator& other) const 
	{
		return !(*this == other);
	}

};

class reverse_vector_iterator 
{
	friend class BooleanVector;
private:
	BooleanVector* vector;
	//this bitPosition is not the index in the bucket, but in the whole buckets array
	size_t bitPosition;

public:
	reverse_vector_iterator(BooleanVector* vector) : vector(vector), bitPosition(0){};

	reverse_vector_iterator& operator++()
	{
		bitPosition--;
		return *this;
	}

	reverse_vector_iterator operator++(int)
	{
		reverse_vector_iterator it = *this;
		++(*this);
		return it;
	}

	reverse_vector_iterator& operator--()
	{
		bitPosition++;
		return *this;
	}

	reverse_vector_iterator& operator--(int)
	{
		reverse_vector_iterator it = *this;
		--(*this);
		return it;
	}

	bool operator*()
	{
		unsigned bucketIndex = bitPosition / Constants::ELEMENTS_IN_BUCKET;
		unsigned bitIndex = bitPosition % Constants::ELEMENTS_IN_BUCKET;

		return (*vector).buckets[bucketIndex] & (1 << bitIndex);
	}

	bool operator==(const reverse_vector_iterator& other) const
	{
		return ((bitPosition == other.bitPosition) && (vector == other.vector));
	}

	bool operator!=(const reverse_vector_iterator& other) const
	{
		return !(*this == other);
	}
};
};
