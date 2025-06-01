#include <iostream>
using namespace std;

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;

	}
	Point(int x)
	{
		this -> x = x;
		this -> y = 0;
		cout << "Constructor:\t\t" << this << endl;
	}*/
	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}


	//methods

	void print()const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}

	//без координат второй точки должен показывать расстояние до начала координат
	//sqrt - кв. корень
	// sqrt((x2-x1)^2 + (y2-y1)^2);

	double distance(const Point& target_point = {0,0}) // перегрузка, если есть аргумент? Point& ? 
	{
		double x_length = this->x - target_point.x;
		double y_length = this->y - target_point.y;
		double distance = sqrt(x_length * x_length + y_length * y_length);
		return distance;
	}
	
};
double distance(const Point& first, const Point& second = {0,0});




//#define STRUCT_POINT
#define HOMEWORK
int main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT



	int a; // Объявление переменной а типа инт
	Point A; //ОБъявление переменной А типа Поинт
			//Создание объекта А структуры Point 
			//Создание экземпляра А структуры Point 
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A; 
	cout << pA->x << "\t" << pA->y;
#endif // STRUCT_POINT
/*
	Point A; // здесь неявно вызывается конструктор ПоУмолчанию
			//поскольку мы создаем объект "по умолчанию"
	//A.set_x(2);
	//A.set_y(3);
	//cout << A.get_x() << "\t" << A.get_y() << endl;
	//A.print();
	Point B = 5;
	//cout << B.get_x() << "\t" << B.get_y() << endl;
	//B.print();
	Point C = {7,8};
	//C.print();
	for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
*/
#ifdef HOMEWORK /*_____________________________________________*/
	Point C = {7,8};
	Point D = {7,9};
	cout <<"distance from 0 to point C: "<< C.distance()<< endl;
	cout <<"distance from C to point D: "<< C.distance(D)<< endl;
	cout << "function_result:distance from C to point D: " << distance(C,D)<< endl;
#endif
	return 0;
}


double distance(const Point& first_point, const Point& second_point)
{
	double x_length = first_point.get_x() - second_point.get_x();
	double y_length = first_point.get_y() - second_point.get_y();
	double distance = sqrt(x_length * x_length + y_length * y_length);
	return distance;
}