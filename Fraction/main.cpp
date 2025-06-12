#include <iostream>
#include<string>
using namespace std;


class Fraction;
Fraction operator+(const Fraction& left, const Fraction& right); //binary '+': 'Fraction' does not define this operator or a conversion to a type acceptable to the predefined operator
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right); // ����� ��� �������� ��������. 
class Fraction
{
	int integer; // ������ ����� �����
	int numerator; // ������ ���������
	int basis; //������  �����������
public:
	int get_integer() const
	{
		return integer;
	}
	int get_numerator() const
	{
		return numerator;
	}
	int get_basis() const
	{
		return basis;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_basis(int basis)
	{
		this->basis = basis;
	}

	/*----------Constructors---------------*/
	Fraction()
	{
		set_integer(0);
		set_numerator(0);
		set_basis(1); // �������� ����� ������ ��� ������� �� ����. ->1.
		cout << "Creating Complete: " << this<<endl;
	}
	Fraction(int integer, int numerator, int basis)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_basis(basis);
		cout << "Creating Complete: " << this << endl;
	}
	Fraction(int numerator, int basis)
	{
		set_integer(0);
		set_numerator(numerator);
		set_basis(basis);
		cout << "Creating Complete: " << this << endl;
	}
	~Fraction()
	{
		cout << "Destroing Complete: " << this<< endl;
	}
	/*----------Operators-----------------------*/

	Fraction& operator=(const Fraction& other)
	{
		this->set_basis(other.basis);
		this->set_integer(other.integer);
		this->set_numerator(other.numerator);
		return *this;
	}
	
	Fraction& operator+= (const Fraction& other)
	{
		return *this=*this+other;
	}

	Fraction& operator-= (const Fraction& other)
	{
		return *this=*this-other;
	}
	Fraction& operator*= (const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/= (const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction& operator++() // ���� ��������� �� +1 �����
	{
		this->integer++; 
		return *this;
	}
	Fraction& operator++(int) // extra parameter of postfix 'operator++' must be of type 'int'	

	{
		Fraction buffer = *this;
		this->integer++;
		return buffer;
	}
	Fraction& operator--() 
	{
		this->integer--;
		return *this;
	}
	Fraction& operator--(int) // extra parameter of postfix 'operator++' must be of type 'int'	

	{
		Fraction buffer = *this;
		this->integer--;
		return buffer;
	}
	/*---------------Methods------------*/
	Fraction& destroy_integer() // ������� �����, ���������� � ���������.
	{
		numerator += integer * basis;
		integer = 0;
		return *this;
	}
	Fraction& allocate_integer() // �������� ��������, �������� �����
	{
		integer = numerator / basis;
		numerator = numerator % basis;
		return *this;
	}
	double to_decimal() // ���������� � ����������
	{
		double result = integer + (double)numerator / basis;
		return result;
	}
	void console() const
	{
		
		cout
			<< (integer ? to_string(integer) : "")
			<< (numerator ? "(" + to_string(numerator) + "/" + to_string(basis)+")" : "")
			<<
		endl;
	}
	
};


Fraction operator+(const Fraction& left, const Fraction& right) //binary '+': 'Fraction' does not define this operator or a conversion to a type acceptable to the predefined operator
{
	Fraction result;
	result.set_basis(left.get_basis() + right.get_basis());
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator() + right.get_numerator());
	return result;
}
Fraction operator-(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_basis(left.get_basis() - right.get_basis());
	result.set_integer(left.get_integer() - right.get_integer());
	result.set_numerator(left.get_numerator() - right.get_numerator());
	return result;
}
Fraction operator*(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_basis(left.get_basis() * right.get_basis());
	result.set_integer(left.get_integer() * right.get_integer());
	result.set_numerator(left.get_numerator() * right.get_numerator());
	return result;
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_basis(left.get_basis() / right.get_basis());
	result.set_integer(left.get_integer() / right.get_integer());
	result.set_numerator(left.get_numerator() / right.get_numerator());
	return result;
}

bool operator==(const Fraction& left, const Fraction& right)
{
	int left_buffer = left.get_integer() * left.get_basis()+left.get_numerator();
	int right_buffer = right.get_integer()*right.get_basis()+right.get_numerator();
	//if((left_buffer== right_buffer)&&(left.get_basis()==right.get_basis()))  6/3 == 4/2 wrong
	//if((left_buffer/left.get_basis()==right.buffer/right.get_basis()) ? ���� ����� wrong
	// 6*2==4*3  1/2 � 3/6  1*6==2*3 8/2� 20/5 8*5 40  2*20 - 40 
	
	return left_buffer*right.get_basis()==right_buffer*left.get_basis();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(const Fraction& left, const Fraction& right)
{
	int left_buffer = left.get_integer() * left.get_basis() + left.get_numerator(); // ����� �����
	int right_buffer = right.get_integer() * right.get_basis() + right.get_numerator();
	return left_buffer * right.get_basis() > right_buffer * left.get_basis();
}
bool operator<(const Fraction& left, const Fraction& right)
{
	//return !(left > right);   ����� ���� == 
	int left_buffer = left.get_integer() * left.get_basis() + left.get_numerator();
	int right_buffer = right.get_integer() * right.get_basis() + right.get_numerator();
	return left_buffer * right.get_basis() < right_buffer * left.get_basis();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}

int main()
{
	Fraction test(2, 4,4);
	Fraction test2(1, 2, 3);
	Fraction test3(3,1 , 2);
	test += test2;
	++test3;
	test = test3;
	cout << test.get_integer()<<" "<< test.get_numerator() <<"/"<<test.get_basis()<< endl; // ����� ����� �� �����. 
	test.console();
	cout<<test.to_decimal()<<endl;
	return 0;
}