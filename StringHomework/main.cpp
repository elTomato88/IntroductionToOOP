#include <iostream>
using namespace std;


class String
{
	char* str;
	int length;

public:
	int get_length() const
	{
		return length;
	}
	char* get_str() const
	{
		return str;
	}
	char get_str(int x) const
	{
		return str[x];
	}
	void set_length() 
	{
		this->length = length;
	}
	void set_str(char* str)
	{
		this->str = str;
	}
/*-------Constructors-----------------*/

	/*String()
	{
		this->length = 1;  // strlen - размер строки
		//this->str = ""; // a value of type "const char *" cannot be assigned to an entity of type "char *"
		this->str = new char[1];
		this->str[0] = " ";
		cout << "Construction complete: " << this << endl;
	}
	*/
	String(const char* str=" ")
	{
		this->length = strlen(str)+1;  // strlen - размер строки
		this->str = new char[length];
		for (int i = 0; i < length; i++)this->str[i] = str[i];
		cout << "Construction complete: " << this << endl;
	
	}
	
	~String()
	{
		delete[] this->str;
		cout << "Destruction complete: " << this << endl;
	};

/*-------Methods-----------------*/

	void print()
	{
		for (int i = 0; i < length; i++)
		{
			cout << str[i];
		}
		cout << endl;
	}
/*-------Operators-----------------*/
	
};

String operator+(const String& left, const String& right)
{
	char* buffer= new char[left.get_length() + right.get_length()-1];
	
	for (int i = 0; i < left.get_length(); i++)
	{
		buffer[i]=left.get_str(i);
		
	}
	for (int i = 0; i < right.get_length(); i++)
	{
		buffer[i+ left.get_length()-1] = right.get_str(i);
	}
	String result(buffer);
	delete[] buffer;
	return result;
}

void main()
{
	String A = {"left"};
	String B = {"right"};
	
	(A + B).print();
	
};
