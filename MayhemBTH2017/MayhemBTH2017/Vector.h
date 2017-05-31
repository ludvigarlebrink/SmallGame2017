#ifndef __VECTOR_H__
#define __VECTOR_H__


#include "AAllocator.h"
#include "DefaultAllocator.h"

#include <vector>


template<class T>
class Vector
{
public:

	//::.. CONSTRUCTORS ..:://
	Vector();						// Default constructor.
	Vector(AAllocator* allocator);	// Consturctor with allocator.
	Vector(const T value[]);
	virtual ~Vector();				// Destructor.

	//::.. OPERATOR OVERLOADING ..:://
	T& operator[] (size_t n);		// [] operator overloaded.
	T& operator= (const T &value);	// = operator overloaded.

	//::.. MODIFY FUNCTIONS ..:://
	void PushBack(const T &value);			// Add element at the end.
	void PopBack();							// Delete last element.
	void Assign(size_t n, T const &value);	// Assign new content, replace current content and modify size if needed.
	void Clear();							// Remove all elements.
	void Resize(size_t n);					// Resizes the container to contain n elements

	//::.. GET FUNCTIONS ..:://
	size_t GetSize();	// Return size of vector.
	bool IsEmpty();		// Returns true if the function is empty.

	//::.. ACCESS FUNCTIONS ..:://
	T At(size_t n);	// Access value at element.
	T First();		// Access first element.
	T Last();		// Access last element.

private:
	AAllocator* m_allocator;

	std::vector<T> m_vector;

};


//::.. CONSTRUCTORS ..:://
template<class T>
inline Vector<T>::Vector()
{
	//Do nothing...
}

template<class T>
inline Vector<T>::~Vector()
{
	//Do nothing...
}

template<class T>
inline Vector<T>::Vector(const T value[])
{
	for (int i = 0; i < sizeof(value) / sizeof(*value); i++)
	{
		m_vector.push_back(value[i]);
	}
}


//::.. OPERATOR OVERLOADING ..:://
template<class T>
inline T & Vector<T>::operator[](size_t n)
{
	return m_vector[n];
}

template<class T>
inline T & Vector<T>::operator=(const T & value)
{
	m_vector = value;
}


//::.. MODIFY FUNCTIONS ..:://
template<class T>
inline void Vector<T>::PushBack(const T &value)
{
	m_vector.push_back(value);
}

template<class T>
inline void Vector<T>::PopBack()
{
	m_vector.pop_back();
}

template<class T>
inline void Vector<T>::Assign(size_t n, const T &value)
{
	m_vector.assign(n, value);
}

template<class T>
inline void Vector<T>::Clear()
{
	m_vector.clear();
}

template<class T>
inline void Vector<T>::Resize(size_t n)
{
	m_vector.resize(n);
}


//::.. GET FUNCTIONS ..:://
template<class T>
inline size_t Vector<T>::GetSize()
{
	return m_vector.size();
}

template<class T>
inline bool Vector<T>::IsEmpty()
{
	return m_vector.empty();
}


//::.. ACCESS FUNCTIONS ..:://
template<class T>
inline T Vector<T>::At(size_t n)
{
	return m_vector.at(n);
}

template<class T>
inline T Vector<T>::First()
{
	return m_vector.front();
}

template<class T>
inline T Vector<T>::Last()
{
	return m_vector.back();
}


#endif __VECTOR_H__