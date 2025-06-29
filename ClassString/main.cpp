#include <iostream>
using namespace std;

class String
{
	int size; // размер строки в байтах
	char* str; // указатель на строку в динамической памяти
public:
	int get_size() const
	{
		return size;
	}
	const char* get_str() const
	{
		return str;
	}
	// constructors

	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i];i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;

	}
	String(const String& other)
	{
		//Конструктор копирования должен выполнять DeepCopy Побитовое копирование
		//т.е. выделять динамическую память под объект и побитово(поэлементно) копировать 
		//содержимое динамической памяти из существующего объекта в создаваемый. 
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstrucor:\t" << this << endl;
	}
	~String()
	{
		
		delete[] str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}
	//operators
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	//methods
	void info()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
char* operator+(const String& left, const String& right)
{
	int size = left.get_size() + right.get_size();
	cout << size << endl;
	char* buffer = new char[size] {};
	for (int i = 0; i < left.get_size(); i++)
	{
		buffer[i] = left.get_str()[i];
	}
	for (int i = 0; i < right.get_size(); i++)
	{
		buffer[i+ left.get_size()-1] = right.get_str()[i];
		
	}
	
	
	return buffer;
}
void main()
{
	setlocale(LC_ALL, "");
	String str1(5); // explicit  конструктор нельзя вызвать оператором присвоить, но всегда можно вызвать с круглыми скобками. 
	str1.info();

	String str2 = "Hello";
	cout << str2 << endl;
	String str3 = str2;
	cout << str3 << endl;

	String str4="World";
	String test = str4 + str2;
	cout <<"Summ:"<< test << endl;

}