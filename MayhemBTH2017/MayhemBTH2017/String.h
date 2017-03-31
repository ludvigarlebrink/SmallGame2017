#ifndef __STRING_H__
#define __STRING_H__

#include <string>

class String
{
public:

	//::.. CONSTRUCTORS ..:://
	String();
	virtual ~String();

	//::.. MODIFY FUNCTIONS ..:://
	// Append to string
	std::string &Append(const std::string &value);

	// Append character to end of string
	void Push_Back(char value);

	// Delete character at end of string
	void Pop_Back();

	// Assign new value to string, replace current content
	std::string &Assign(const std::string &value);

	// Insert additional characters into string right before the character indicated by position
	std::string &Insert(size_t position, const std::string &value);

	//::.. CAPACITY FUNCTIONS ..:://
	size_t Size();


private:

	std::string m_string;
};

#endif
