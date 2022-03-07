#pragma once
/*
Streams are flow of data/character. Streams are used for accessing the data outside the program i.e. to and from external sources "File/Keyboard/Monitor/Network".

*** There are iostreams. These are build in classes for accessing I/O Streams.
ios (keyboard/Monitor): istream Class for Input Stream, ostream class for Output Stream.
cin - object of istream class with extraction operator overloaded i.e. "<<"  Associated with the Keyboard.
cout - object of ostream class with insertion operator overloaded i.e. ">>" , Associated with the Monitor.

***
***
ifstream/ofstream classes for File i.e for (Input File Stream / Output File Stream)
we can also use same extraction and insertion operator with files as well.
***

// Lets Code a Program for writting in to the File MyFile.txt
*/

#include <cassert>
#include <fstream> // Header for writting in to File
#include <iomanip> // Will be used for setw function.
#include <iostream>
using namespace std;

class Student_Serialization // Reading/Writing to and from the object to File (i.e. retrieving state of the object from the file)
{
public:
	char name[20] {"Amit"};
	int roll {22};
	char branch[10] {"CSE"};

private:
	// Insertion and Extraction Operator Overloading.
	friend ofstream & operator << (ofstream & ofs, const Student_Serialization &s);
	friend ifstream & operator >> (ifstream & ifs, Student_Serialization &s);
};

inline ofstream & operator<< (ofstream & ofs, const Student_Serialization &s)
{
	ofs << s.name << endl;
	ofs << s.roll << endl;
	ofs << s.branch << endl;
	return ofs;
	
}

inline ifstream & operator>> (ifstream & ifs, Student_Serialization &s)
{
	ifs >> s.name;
	ifs >> s.roll;
	ifs >> s.branch;
	return ifs;

}

class StreamClass
{
public:
	StreamClass()
	{
		cout << "stream class Constructor" << endl;
	}

	StreamClass(string filename)
	{
		m_filename = filename;
	}

	void Open_File(string mode, ios_base::openmode ios_mode = ios::app)
	{
		if(mode == "read")
		{
			infile.open(m_filename);
			if(!infile)
			{
				cerr << "Error: file could not be opened" << endl;																	
				exit(1);
			}

		}
		else if(mode == "write")
		{
			outfile.open(m_filename, ios_mode); // Create a File if not existing otherwise append with mode ios:app existing content
											  // ios:truncate : by default truncate is taken means remove the old content.
			if (!outfile) {			// file couldn't be opened
				cerr << "Error: file could not be opened" << endl;  // cout is an object of the stdout stream, while cerr is an object of the stderr stream.
																	// stdout and stderr are different streams, even though they both refer to console output by default.Redirecting(piping) one of them(e.g.program.exe >out.txt) would not affect the other.
				exit(1);
			}
		}
		else
		{
			assert(false);
		}
	}

	void Close_File()
	{
		if (outfile.is_open())
			outfile.close();

		if (infile.is_open())
			infile.close();
	}

	~StreamClass()
	{
		if (outfile.is_open())
			outfile.close();

		if (infile.is_open())
			infile.close();
	}

	ofstream outfile;		// Since we would only be writing in to file
	ifstream infile;		// Reading from the File, istream object.
	string m_filename;      // Filename to be read/wrtie
};