
#include "Streams.h"

using namespace std;


class A
{
	int x;
public:
	A()
	{
		
	}
	A(int a)
	{
		x = a;
	}
	A(A& a)
	{
		x = a.x;
		x++;
	}
	virtual void f1()
	{
		printf("A :: f1()\n");
	}
	void show()
	{
		printf("%d", x);
	}
	~A() {}

	template <typename T, int count >
	void foo(T x)
	{
		T val[count];
		for(int i = 0; i < count ; i++)
		{
			val[i] = x++;
			cout << val[i] << " ";
		}
	}
};

class B : public A
{
public:
	void f1()
	{
		printf("B :: f1()\n");
	}

	void f2()
	{
		printf("B :: f2()\n");
	}
};

int sum(int a, int b)
{
	return a + b;
}


void main_cplusplus()
{
	// It's Main for Cplusplus Programming.
	
	/***********     Stream Class Usage    ************/

	StreamClass FileObj("ABC.txt"); // Using Double Slash to give Full Path, Example : C:\\Amit_Shah\\ABC.txt
	FileObj.Open_File("write");
	FileObj.outfile << "Hello Buddy" << endl;
	FileObj.outfile << "This is Amit" << endl;

	FileObj.outfile << "Outcome : ";
	FileObj.outfile << setw(10); // Width of Character Set, starts writing from Right and rest spaces in the left.
	FileObj.outfile << 1000000000 << endl;
	FileObj.outfile << "RNG :";
	FileObj.outfile << setw(13);
	FileObj.outfile << 10000000 << endl;

	FileObj.Close_File();
	FileObj.Open_File("read");


	// get length of file:
	FileObj.infile.seekg(0, FileObj.infile.end); // Set position in input sequence to eof
	streamoff fileSize = FileObj.infile.tellg(); //Returns the position of the current character in the input stream.
	FileObj.infile.seekg(0, FileObj.infile.beg); // Again set to beginning.

	char* buffer = new char[static_cast<unsigned int>(fileSize) + 1];
	buffer[fileSize] = '\0'; // Basically Created a null terminated string.

	FileObj.infile.read(buffer, fileSize);			// Another Way : FileObj.infile >> buffer;
	cout << buffer << endl;
	FileObj.infile.close();

	Student_Serialization s1;

	StreamClass FileStream_Obj("Student.txt");
	FileStream_Obj.Open_File("write", ios::trunc);
	FileStream_Obj.outfile << s1 << endl; // To make it work, Overload Operator << in Student Class
	FileStream_Obj.Close_File();

	Student_Serialization s2;
	FileStream_Obj.Open_File("read");
	FileStream_Obj.infile >> s2; // Overloaded. Basically Left Side Object i.e. ifstream object will be returned.

	cout << s2.name << endl << s2.roll << endl << s2.branch << endl;
	FileStream_Obj.Close_File();


	//A *a = new B();
	//a->f1();

	A y(10);
	//A z = y;
	//z.show();

	//a->f2();
	float w = 2.1;
	y.foo<float, 3>(w);

	int c = sum(7, 8);
	printf("\n\n%d\n", c);
}
