#pragma once

#include "Header.h"

#ifndef _FILE_
#define _FILE_

class File
{
public :
	virtual ~File();
	
	bool Init(const string& address);

	//open file 
	bool OpenFile();

	//close file
	void CloseFile();
	
	//read a line then skip to next one 
	bool ReadLine(string* text);

	//write a string in file 
	void WriteLine(const string& text);

	// create a file 
	void CreateFile();

	// get the address of file
	const string& GetAddress()const;

	//prevent duplication
	File& operator=(const File& File) {
		this->m_address = File.GetAddress();
		return *this;
	}


private :

	//name of file
	string m_address;

	//file stream
	fstream myFile;
};


#endif // !_FILE_
