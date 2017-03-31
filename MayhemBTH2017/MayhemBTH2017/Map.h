#ifndef __MAP_H__
#define __MAP_H__


#include <map>

template <class KEY, class DATA>
class Map
{
public:
	//::.. CONSTRUCTORS ..:://
	Map();
	virtual ~Map();

	void Insert(KEY key, DATA data);

private:
	std::map<KEY, DATA> m_map;

};


template <class KEY, class DATA>
Map<KEY, DATA>::Map()
{
}

template <class KEY, class DATA>
Map<KEY, DATA>::Insert(KEY key, DATA data)
{
	m_map.insert(key, data);
}


#endif // __MAP_H__