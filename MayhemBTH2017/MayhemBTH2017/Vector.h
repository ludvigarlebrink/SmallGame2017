#ifndef __VECTOR_H__
#define __VECTOR_H__


#include "MemoryManager.h"
#include <vector>

template<class T>
class Vector
{
public:

	//::.. CONSTRUCTORS ..:://
	Vector();
	virtual ~Vector();
	Vector(const T value[]);

	//::.. OPERATOR ..:://
	T& operator[] (size_t n);
	T& operator= (const T &value);

	//::.. MODIFY FUNCTIONS ..:://
	// Add element at the end
	void Push_Back(const T &value);

	// Delete last element
	void Pop_Back();

	// Assign new content, replace current content and modify size if needed
	void Assign(size_t n, T const &value);

	// Remove all elements and set m_size to 0
	void Clear();

	//::.. CAPACITY FUNCTIONS ..:://
	// Return size of vector
	size_t Size();

	// Basicly a get function for m_isEmpty
	bool Empty();

	// Resizes the container to contain n elements
	void Resize(size_t n);

	//::.. ACCESS FUNCTIONS ..:://
	// Access value at element
	T At(size_t n);

	// Access first element
	T First();

	// Access last element
	T Last();

private:
	MemoryManager m_memory;

	std::vector<T> m_vector;

};

#include "Vector.cpp"

#endif __VECTOR_H__