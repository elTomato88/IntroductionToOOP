#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimeter "\n-------------------------------\n"

class Fraction;
Fraction operator *(Fraction left, Fraction right);
Fraction operator /(Fraction left, Fraction right);
class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (!denominator)denominator = 1;
		this->denominator = denominator;
	}
	//Constructors
	Fraction()
	{
		set_integer(0);
		set_numerator(0);
		set_denominator(1); // �������� ����� ������ ��� ������� �� ����. ->1.
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->  integer=integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor" << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		integer = decimal; // ������� �������������� ������
		decimal -= integer;
		denominator = 1e+9; // ����. ��������� �������� � ��������� 9 ������. ��������
		numerator = decimal * denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		set_integer(0);
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;

	}
	Fraction(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;

	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout<<"Destructor\t\t"<<this<< endl;
	}
	//Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	};
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	// increment/Decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	// Type-cast operators
	explicit operator int() const
	{
		return integer + numerator / denominator;
	}
	explicit operator double() const
	{
		return integer + (double)numerator / denominator;
	}
	//Methods
	Fraction& reduce()
	{
		int more, less, rest;
		if (numerator < denominator)
		{
			less = numerator;
			more = denominator;
		}
		else
		{
			more = numerator;
			less = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //Greatest common divisor
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted() const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator); // ������ ������� ��� ����������
		return inverted;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (!integer)cout << 0;
		cout << endl;
	}


};
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());
	*/
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/(const Fraction left, const Fraction right)
{
	return left * right.inverted();
}
// Comparision operator:
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() ==
		left.get_denominator() * right.get_numerator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
std::istream& operator>>(std::istream& is,  Fraction& obj)
{
	//is- input stream
	const int SIZE = 32;
	char sz_input[SIZE] = {};
	//is >> sz_input;
	is.getline(sz_input, SIZE); // ���� ������ � ���������
	const char delimeters[] = { '/', '(', ')', ' ', '.' , ',',  0};
	int numbers[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_input, delimeters); pch; pch = strtok(NULL, delimeters))
		numbers[n++] = atoi(pch);
	for (int i = 0; i < n; i++) cout << numbers[i] << "\t"; cout << endl;
	switch (n)
	{
		case 1:obj = Fraction(numbers[0]); break;
		case 2:obj = Fraction(numbers[0], numbers[1]); break;
		case 3:obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER
int main()
{
#ifdef CONSTRUCTORS_CHECK
	setlocale(LC_ALL, "");
	Fraction A;
	A.print();
	Fraction B = 5;
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
	Fraction E = D;
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Fraction A, B, C;
	cout << delimeter << endl;
	A = B = C = Fraction(2, 3, 4); // ����� ����� ������������, ������� ������� ���������
	//���������� ������. ��������� ���������� ������� ���������� � ��������
	//������ ���������. 
	cout << delimeter << endl;
#endif // ASSIGNMENT_CHECK
	/*
	Fraction A;
	cout << "Enter the Fraction: " << endl;
	cin >> A;
	cout << A<< endl;
	*/
#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;
	cout << A << endl;
	Fraction B;
	B = (Fraction)8;
	cout << B << endl;
	return 0;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER
	Fraction A(2, 3, 4);
	cout << A << endl;
	int a = (int)A;
	cout << a << endl;
	double b = (double)A;
	cout << b << endl;
#endif // CONVERSIONS_FROM_CLASS_TO_OTHER


	Fraction A = 2.76;
	cout << A << endl;
}