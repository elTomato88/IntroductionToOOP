#include <iostream>
using namespace std;
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
		set_denominator(1); // Возможно будут ошибки при делении на ноль. ->1.
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->  integer=integer;
		this->numerator = 0;
		this->denominator = 1;
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

	//Methods
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
		swap(inverted.numerator, inverted.denominator); // меняет местами две переменных
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
std::istream& operator>>(std::istream& os, Fraction& obj) // 'return': cannot convert from 'std::istream' to 'std::ostream &'
{
	obj.set_integer(os.get);
	return os;
}
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
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
	A = B = C = Fraction(2, 3, 4); // явный вызов конструктора, который создает временный
	//безымянный объект. Временные безымянные объекты существуют в пределах
	//одного выражения. 
	cout << delimeter << endl;
#endif // ASSIGNMENT_CHECK
	Fraction A;
	cout << "Enter the Fraction: " << endl;
	cin >> A;
	return 0;
}