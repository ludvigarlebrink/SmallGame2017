#include "String.h"


//::.. CONSTRUCTORS ..:://
String::String()
{
	//Do nothing...
}

String::~String()
{
	//Do nothing...
}


//::.. OPERATOR OVERLOADING ..:://
char & String::operator[](size_t position)
{
	return m_string[position];
}

void String::operator=(const String &object)
{
	m_string = object.m_string;
}

bool String::operator==(const String &object)
{
	if (m_string == object.m_string)
	{
		return true;
	}

	return false;
}

//::.. MODIFY FUNCTIONS ..:://
void String::Append(const std::string & value)
{
	m_string.append(value);
}

void String::PushBack(char value)
{
	m_string.push_back(value);
}

void String::PopBack()
{
	m_string.pop_back();
}

void String::Clear()
{
	m_string.clear();
}

void String::Reserve(size_t value)
{
	m_string.resize(value);
}


//::.. GET FUNCTIONS ..:://
size_t String::GetLength() const
{
	return m_string.length();
}

size_t String::GetMaxSize() const
{
	return m_string.max_size();
}

size_t String::GetCapacity() const
{
	return m_string.capacity();
}

bool String::IsEmpty() const
{
	return m_string.empty();
}

const char* String::GetAsCStr() const
{
	return m_string.c_str();
}


//::.. ACCESS FUNCTIONS ..:://
char & String::At(size_t position)
{
	return m_string.at(position);
}

char & String::Front()
{
	return m_string.front();
}

char & String::Back()
{
	return m_string.back();
}

void String::Init()
{
}
