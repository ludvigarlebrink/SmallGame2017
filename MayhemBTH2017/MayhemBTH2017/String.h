#ifndef __STRING_H__
#define __STRING_H__

#include <string>

class String
{
public:

	//::.. CONSTRUCTORS ..:://
	String();
	virtual ~String();

	//::.. OPERATOR ..:://
	char& operator[] (size_t position);
	std::string operator= (const std::string &value);

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
	// Returns length of string in terms of bytes
	size_t Length();

	// Returns maximum length the string can reach
	size_t MaxSize();

	// Returns the size of the allocated storage space
	size_t Capacity();

	// Clear the contents of the string
	void Clear();

	// Check if string is empty
	bool Empty();

	// Resizes the string
	void Resize(size_t value);

	//::.. ACCESS FUNCTIONS ..:://
	// Returns a reference to the character at position in the string
	char& At(size_t position);

	// Returns a reference to the first character in the string
	char& Front();

	// Returns a reference to the last character in the string
	char& Back();

	//::.. STRING OPERATIONS ..:://
	// Get C string equivalent
	std::string C_Str();


private:

	std::string m_string;
};

#endif
