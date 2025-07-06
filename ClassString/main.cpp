#include <Windows.h>
#include <iostream>
using namespace std;

#define delimeter "\n----------------------------\n"
#define DEBUG
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
	char* get_str()
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
		size = 0;
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
	String(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;// защищаем память от удаления Деструктором
		cout << "MoveConstructor\n" << this << endl;
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
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment: \t\t" << this << endl;
		return *this;
	}
	char operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
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
std::istream& operator>>(std::istream& cin, String& obj)
{
	const int SIZE = 1024; // размер буфера 1 kБ
	char buffer[SIZE] = {};
	cin >> buffer;
	obj = buffer;
	return cin;
}
std::istream& getline(std::istream& cin, String& obj)
{
	cin.getline(obj.get_str(), obj.get_size());
	return cin;
}

String operator+(const String& left, const String& right)
{
	String result (left.get_size() + right.get_size() - 1);
	for (int i = 0; left.get_str()[i]; i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; right.get_str()[i];i++)
		//result.get_str()[left.get_size()-1+i]=right.get_str()[i];
		result[left.get_size() - 1 + i] = right[i];
	return result;
}
//#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS
//#define ISTREAM_OPERATOR
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str1(5); // explicit  конструктор нельзя вызвать оператором присвоить, но всегда можно вызвать с круглыми скобками. 
	str1.info();

	String str2 = "Hello";
	cout << str2 << endl;
	String str3 = str2;
	cout << str3 << endl;

	String str4 = "World";
	String test = str4 + str2;
	cout << "Summ:" << test << endl;
#endif // CONSTRUCTORS_CHECK
#ifdef OPERATOR_PLUS
	String str1 = "HELLO";
	String str2 = "World";
	cout << delimeter << endl;
	String str3 = str1 + str2;
	cout << delimeter << endl;
	cout << str3 << endl;
#endif // OPERATOR_PLUS
#ifdef ISTREAM_OPERATOR
	String str;
	SetConsoleCP(1251);
	cout << "ВВедите строку: ";
	getline(cin, str);
	SetConsoleCP(866);
	cout << str << endl;
#endif // ISTREAM_OPERATOR
	String str1;
	str1.info();
	String str2(8);
	str2.info();
	String str3 = "Hello"; // КОнструктор с одним параметром типа чар*
	str3.info();
	String str4(); // Не вызывается никкакой конструктор и не создается объект.
	//Происходит объявление функции стринг, которая возвращает объект String
	//Пустые скобки не делают явный вызов Default конструктора
	//Если надо явно вызвать DefaCon, это можно сделать фигурными
	String str5(8);
	String str6{ 8 }; //АНалог верхней строке, так же вызывает конструкт.
	String str7{}; // Явный вызов констуркии по умаолчанию
	//{} СЛЕДУЕТ испльозвать с осторднолстьб 
	String str9 = str3;
	

}