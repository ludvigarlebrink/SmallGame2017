#ifndef __MAP_H__
#define __MAP_H__


#include <vector>


template <class T>
class Map
{
public:
	//::.. CONSTRUCTORS ..:://
	Map();
	virtual ~Map();

//	void Insert(T data);

	//::.. GET FUNCTIONS ..:://
	bool Exists(const String& name);

private:
	std::vector<String> str;

};


#endif // __MAP_H__


template <class T>
Map<T>::Map()
{
}

template<class T>
inline Map<T>::~Map()
{
}

template <class T>
Map<T>::Insert(KEY key, T data)
{
	m_map.insert(key, data);
}

