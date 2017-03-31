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

//::.. OPERATOR ..:://
char & String::operator[](size_t position)
{
	return m_string[position];
}

std::string String::operator=(const std::string & value)
{
	return m_string = value;
}

//::.. MODIFY FUNCTIONS ..:://
// Append to string
std::string & String::Append(const std::string & value)
{
	return m_string.append(value);
}

// Append character to end of string
void String::Push_Back(char value)
{
	m_string.push_back(value);
}

// Delete character at end of string
void String::Pop_Back()
{
	m_string.pop_back();
}

// Assign new value to string, replace current content
std::string & String::Assign(const std::string & value)
{
	return m_string.assign(value);
}

// Insert additional characters into string right before the character indicated by position
std::string & String::Insert(size_t position, const std::string & value)
{
	return m_string.insert(position, value);
}

//::.. CAPACITY FUNCTIONS ..:://
// Returns length of string in terms of bytes
size_t String::Length()
{
	return m_string.length();
}

// Returns maximum length the string can reach
size_t String::MaxSize()
{
	return m_string.max_size();
}

// Returns the size of the allocated storage space
size_t String::Capacity()
{
	return m_string.capacity();
}

// Clear the contents of the string
void String::Clear()
{
	m_string.clear();
}

// Check if string is empty
bool String::Empty()
{
	return m_string.empty();
}

// Resizes the string
void String::Resize(size_t value)
{
	m_string.resize(value);
}

//::.. ACCESS FUNCTIONS ..:://
// Returns a reference to the character at position in the string
char & String::At(size_t position)
{
	return m_string.at(position);
}

// Returns a reference to the first character in the string
char & String::Front()
{
	return m_string.front();
}

// Returns a reference to the last character in the string
char & String::Back()
{
	return m_string.back();
}

//::.. STRING OPERATIONS ..:://
// Get C string equivalent
std::string String::C_Str()
{
	return m_string.c_str();
}
