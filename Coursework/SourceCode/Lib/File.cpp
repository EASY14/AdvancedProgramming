#include "File.h"


File::~File()
{
	CloseFile();
}

bool File::Init(const string& address)
{
	m_address = address;
	return true;
}

bool File::OpenFile()
{
	if (m_address.size() == 0)
		ErrorOutput(L"file address is null");

	myFile.open(m_address, ios::in | ios::out);

	try
	{
		if (myFile.fail())
			throw invalid_argument("No file exists in " + m_address);
	}
	catch (const invalid_argument& iae)
	{
		cout << iae.what() << endl;
		return false;
	}

	return true;
}

void File::CloseFile()
{
	myFile.close();
}

bool File::ReadLine(string* text)
{
	if (getline(myFile, *text))
		return true;
	else
		return false;
}

void File::WriteLine(const string& text)
{
	myFile << text << endl;
}

void File::CreateFile()
{
	ofstream text(m_address);
	text.close();
}

const string & File::GetAddress()const
{
	return m_address;
}
