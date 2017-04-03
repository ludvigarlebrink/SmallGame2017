#ifndef __STRING_H__
#define __STRING_H__


#include <string>


class String
{
public:
	//::.. CONSTRUCTORS ..:://
	String();				// Default constructor.
//	String(char* string);	// Copy constructor.
	String(char* string);	// Default constructor.
	virtual ~String();		// Destructor.

	//::.. OPERATOR OVERLOADING ..:://
	char& operator[] (size_t position);		// [] operator overloaded.
	void operator= (const String &other);	// = operator overloaded.
	bool operator== (const String &other);	// == operator overloaded.

	//::.. MODIFY FUNCTIONS ..:://
	void Append(const std::string &value);	// Append to string.
	void PushBack(char value);				// Append character to end of string.
	void PopBack();							// Delete character at end of string.
	void Clear(); 							// Clear the contents of the string.
	void Reserve(size_t value);				// Resizes the string.

	//::.. GET FUNCTIONS ..:://
	size_t GetLength() const;		// Returns length of string in terms of bytes.
	size_t GetMaxSize() const;		// Returns maximum length the string can reach.
	size_t GetCapacity() const;		// Returns the size of the allocated storage space.
	bool IsEmpty() const;			// Returns true or false if the string is empty.
	const char* GetAsCStr() const;	// Returns a char pointer to the string.

	//::.. ACCESS FUNCTIONS ..:://
	char& At(size_t position);		// Returns a reference to the character at position in the string.
	char& Front();					// Returns a reference to the first character in the string.
	char& Back();					// Returns a reference to the last character in the string.

private:
	//::.. HELPER FUNCTIONS ..:://
	void Init();

private:
	std::string m_string;
};


#endif
