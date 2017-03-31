#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__
#include "Vector.h"

//::.. CONSTRUCTORS ..:://

template<class T>
Vector<T>::Vector()
{
	//Do nothing...
}

template<class T>
Vector<T>::~Vector()
{
	//Do nothing...
}

template<class T>
Vector<T>::Vector(const T value[])
{
	for (int i = 0; i < sizeof(value) / sizeof(*value); i++)
	{
		m_vector.push_back(value[i]);
	}
}

template<class T>
T & Vector<T>::operator[](size_t n)
{
	return m_vector[n];
}

template<class T>
T & Vector<T>::operator=(const T & value)
{
	m_vector = value;
}

// Add element at the end
template<class T>
void Vector<T>::Push_Back(const T &value)
{
	m_vector.push_back(value);
}

// Delete last element
template<class T>
void Vector<T>::Pop_Back()
{
	m_vector.pop_back();
}

// Assign new content, replace current content and modify size if needed
template<class T>
void Vector<T>::Assign(size_t n, const T &value)
{
	m_vector.assign(n, value);
}

// Remove all elements
template<class T>
void Vector<T>::Clear()
{
	m_vector.clear();
}

// Return size of vector
template<class T>
size_t Vector<T>::Size()
{
	return m_vector.size();
}

// Check if vector is empty
template<class T>
bool Vector<T>::Empty()
{
	return m_vector.empty();
}

template<class T>
void Vector<T>::Resize(size_t n)
{
	m_vector.resize(n);
}

// Access value at element
template<class T>
T Vector<T>::At(size_t n)
{
	return m_vector.at(n);
}

// Access first element
template<class T>
T Vector<T>::First()
{
	return m_vector.front();
}

// Access last element
template<class T>
T Vector<T>::Last()
{
	return m_vector.back();
}

#endif