#include "BooleanVector.h"

void BooleanVector::free()
{
	delete[] buckets;
	buckets = nullptr;
	size = capacity = 0;
}

void BooleanVector::copyFrom(const BooleanVector& other)
{
	size = other.size;
	capacity = other.capacity;
	buckets = new uint8_t[capacity];

	for (size_t i = 0; i < capacity; i++)
	{
		buckets[i] = other.buckets[i];
	}
}

void BooleanVector::moveFrom(BooleanVector&& other)
{
	size = other.size;
	capacity = other.capacity;

	buckets = other.buckets;

	other.buckets = nullptr;
	other.size = other.capacity = 0;
}

unsigned BooleanVector::getBucketIndex(unsigned num) const
{
	return num / Constants::ELEMENTS_IN_BUCKET;
}

unsigned BooleanVector::getBitIndex(unsigned num) const
{
	return num % Constants::ELEMENTS_IN_BUCKET;
}


BooleanVector::BooleanVector(size_t count) : size(count)
{
	capacity = count / Constants::ELEMENTS_IN_BUCKET + 1;
	buckets = new uint8_t[capacity]{ 0 };
}

BooleanVector::BooleanVector(size_t count, bool initialValue) : size(count)
{
	capacity = count / Constants::ELEMENTS_IN_BUCKET + 1;
	buckets = new uint8_t[capacity];

	uint8_t mask = initialValue ? 0b11111111 : 0b00000000;

	for (int i = 0; i < capacity; i++) 
	{
		buckets[i] = mask;
	}
}

BooleanVector::BooleanVector(const BooleanVector& other)
{
	copyFrom(other);
}

BooleanVector::BooleanVector(BooleanVector&& other) noexcept
{
	moveFrom(std::move(other));
}

BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return *this;
}

BooleanVector& BooleanVector::operator=(BooleanVector&& other) noexcept
{
	if (this != &other) 
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

BooleanVector::~BooleanVector()
{
	free();
}

size_t BooleanVector::calculateCapacity() const 
{
	if (capacity == 0)
		return 1;
	return capacity * Constants::GROWTH_FACTOR;
};


void BooleanVector::resize(size_t newCapacity)
{
	if (newCapacity <= capacity)
		return;

	//could be done with operator new, but no need since elements are primitive
	uint8_t* newBuckets = new uint8_t[newCapacity]{ 0 };

	for (size_t i = 0; i < capacity; i++)
		newBuckets[i] = buckets[i];

	for (size_t i = capacity; i < newCapacity; i++) 
	{
		newBuckets[i] = 0;
	}

	delete[] buckets;
	buckets = newBuckets;
	capacity = newCapacity;
}

void BooleanVector::push_back(bool value)
{
	if (size == capacity)
	{
		resize(calculateCapacity());
	}

	(*this)[size] = value;

	size++;
}

void BooleanVector::pop_back()
{
	if (size == 0)
		throw std::out_of_range("Cannot pop from empty vector");

	(*this)[size - 1] = false;
	size--;
}

void BooleanVector::insert(vector_iterator iter, bool value)
{
	if (size == capacity || capacity == 0)
		resize(calculateCapacity());

	//move every element after the insertion position to the right to leave space for the new element
	for (int i = size - 1 ; i > iter.bitPosition  ; i--) 
	{
		(*this)[i + 1] = (bool)(*this)[i];
	}

	(*this)[iter.bitPosition] = value;
	size++;
}

void BooleanVector::remove(vector_iterator iter)
{
	if (size == 0)
		throw std::out_of_range("Cannot remove from empty vector");

	//move every element after the removed position to the left
	for (int i = iter.bitPosition; i < size - 1; i++)
	{
		(*this)[i] = (bool)(*this)[i + 1];
	}
	
	(*this)[size - 1] = false;
	size--;
}

void BooleanVector::pop_front()
{
	vector_iterator it(this);
	remove(it);
}

BooleanVector::BitWrapper BooleanVector::operator[](size_t index)
{
	unsigned bucketIndex = getBucketIndex(index);
	unsigned bitIndex = getBitIndex(index);

	return BitWrapper(buckets[bucketIndex], bitIndex);
}


const bool& BooleanVector::operator[](size_t index) const
{
	unsigned bucketIndex = getBucketIndex(index);
	unsigned bitIndex = getBitIndex(index);

	uint8_t mask = (1 << bitIndex);

	return buckets[bucketIndex] & mask;
}
