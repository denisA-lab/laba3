#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

/////////////////////////////////////////////////ХРАНИЛИЩЕ/////////////////////////////////////////////////////////////

template <typename T>
struct StorItem {
public:
	StorItem *next;
	StorItem *prev;
	T *value;
};

template <typename T>
class MyStorage {
public:
	int size;
	StorItem<T> *head;
	StorItem<T> *tail;

	MyStorage();
	~MyStorage();

	void addToStor(T *item);	//Функция добавления элемента в список

	void delAllStor();																	//функция удаления всех элементов списка
	void delElem(int num);																//Функция удаления одного элемента

	T *getElem(int num);																//Получение объекта из хранилища
	int getSize();																		//Получение размера хранилища
};

template <typename T>
MyStorage<T>::MyStorage() {//конструктор 
	head = NULL;
	tail = NULL;
	size = 0;
	cout << "......CREATING MYSTORAGE......" << endl;
}

template<typename T>
MyStorage<T>::~MyStorage() {//деструктор
	delAllStor();
	cout << "......MYSTORAGE IS DELETED......" << endl;
}

template<typename T>
void MyStorage<T>::addToStor(T *item) {//Функция добавления элемента в список
	StorItem<T> *Temp = new StorItem<T>;
	Temp->value = item;
	Temp->next = NULL;
	size++;

	if (!head) {//проверка на первый эл
		Temp->prev = NULL;
		head = Temp;
		tail = head;
	}
	else {
		Temp->prev = tail; //Указываем, что предыдущим элементом списка относительно добавленного, будет последний элемент существующего списка
		tail->next = Temp; //Следующий за последним существующим это непосредственно сейчас добавляемый элемент списка
		tail = Temp;       //После того как указали что есть настоящий и что предыдущий, объявляем, что последний существующий это только что добавленный элемент
	}
}

template<typename T>
void MyStorage<T>::delAllStor() {//функция удаления всех элементов списка
	while (head != NULL) //пока не указываем на хвост
	{
		StorItem<T> *Temp = head; //создаем временный элемент
		head = head->next; //присваиваем ему указатель на следующий
		delete Temp->value; // и удаляем его
	}
}

template<typename T>
void MyStorage<T>::delElem(int num) {//удаление из хранилища 

	StorItem<T> *Temp = head; //создаем временный элемент

	if ((num>size) || (num<1)) //если указанный элемент не существует, то
		cout << "Takogo elementa net" << endl; //выводим предупреждение на экран
	else
	{
		for (int i = 1; i != num; i++) //иначе, переходим до этого элемента
		{
			Temp = Temp->next;
		}

		if (Temp->prev == NULL) //если удаляем первый элемент
		{
			if (size == 1) //если этот элемент единственный
			{
				head = NULL;
				tail = NULL;
			}
			else //если он первый, но не единственный
			{
				Temp->next->prev = NULL;
				head = Temp->next;
			}

			delete Temp->value;
			size--;
			cout << "Element " << num << " udalen" << endl;
			return;
		}

		if (Temp->next == NULL) //если удаляем последний элемент, то
		{
			Temp->prev->next = NULL; //предыдущий элемент указывает
									 //на NULL
			tail = Temp->prev; //указатель на последний элемент
							   //указывает на предпоследний

			delete Temp->value;
			size--;
			cout << "Element " << num << " udalen" << endl;
			return;
		}

		//если элемент находится в центре списка
		if (Temp->next != NULL && Temp->prev != NULL)
		{
			Temp->prev->next = Temp->next; //предыдущий элемент указывает
										   //на следующий
			Temp->next->prev = Temp->prev; //следующий указывает на
										   //предыдущий
			delete Temp;
			size--;
			cout << "Element " << num << " udalen" << endl;
			return;
		}
	}
}

template <typename T>
T* MyStorage<T>::getElem(int num) { //Получение объекта из хранилища
	if ((num > size) || (num < 0)) {
		cout << "Element doesn't exist" << endl << endl;
		return 0;
	}

	else {
		StorItem<T> *Temp = head;
		int n = 0;
		while (n < num) {
			Temp = Temp->next;
			n++;
		}
		return Temp->value;
	}
}

template<typename T>
int MyStorage<T>::getSize() { //Получение размера хранилища
	cout << "Size: " << size << endl;
	return size;
}

/////////////////////////////////////////////////КЛАССЫ/////////////////////////////////////////////////////////

class Shape {							  //Родительский класс SHAPES
protected:
	double S;
	double P;

public:
	Shape() {							  //Конструктор без параметров
		S = 0;
		P = 0;
		cout << "...Calling CONSTRUCTOR without parameters of parental class SHAPES..." << endl;
	}


	~Shape() {								//Деструктор
		S = 0;
		P = 0;
		cout << "...Calling DESTRUCTOR of parental class SHAPES..." << endl;
	}

	Shape(int S, int P) {				   //Конструктор с параметром
		P = 0;
		S = 0;
		cout << "...Calling CONSTRUCTOR with parameters of parental class SHAPES..." << endl;
	}


	Shape(Shape& copy) {					//Копирующий конструктор
		S = copy.S;
		P = copy.P;
		cout << "...Object of class SHAPES was copied..." << endl;
	}

	virtual void calcS() {}					//Виртуальные функции
	virtual void calcP() {}

	virtual void Info() {
	}

};



class Circle : public Shape {            //Класс CIRCLE
private:
	int R;

public:
	Circle() {							  //Конструктор без параметров
		cout << "...Calling CONSTRUCTOR without parameters of class CIRCLE..." << endl;
	}

	~Circle() {
		R = 0;
		S = 0;
		P = 0;
		cout << "...Calling DESTRUCTOR of class CIRCLE..." << endl;
		cout << endl;
	}

	Circle(int R1) {					  //Конструктор с параметром
		R = R1;
		cout << "...Calling CONSTRUCTOR with parameters of class CIRCLE..." << endl;
	}

	Circle(Circle& copy) {		  //Копирующий конструктор
		R = copy.R;
		cout << "...Object of class CIRCLE was copied..." << endl;
	}

	void calcS() {				  //Реализация методов
		S = 3.14 * R * R;
	}
	void calcP() {
		P = 2 * 3.14 * R;
	}

	void setValue(int R2) {
		R = R2;
	}

	void Info() {
		calcS();
		calcP();
		cout << "CIRCLE Information:" << endl;
		cout << "R = " << R << endl;
		cout << "S = " << S << endl;
		cout << "P = " << P << endl;
		cout << endl;
	}
};


class Square : public Shape {			  //Класс SQUARE
private:
	int a;

public:
	Square() {                            //Неинициализирующий конструктор
		cout << "...Calling CONSTRUCTOR without of class SQUARE..." << endl;
	}

	Square(int a1) {					  //Инициализируюший конструктор
		a = a1;
		cout << "...Calling CONSTRUCTOR with parameters of class SQUARE..." << endl;
	}

	Square(Square& copy) {		  //Копирующий конструктор
		a = copy.a;
		cout << "...Object of class SQUARE was copied..." << endl;
	}


	~Square() {																		//Деструктор
		S = 0;
		P = 0;
		a = 0;
		cout << "...Calling DESTRUCTOR of class SQUARE..." << endl;
		cout << endl;
	}

	void setValue(int a2) {					  //Инициализирующий метод
		a = a2;
	}

	void calcS() {
		S = a * a;
	}

	void calcP() {
		P = 4 * a;
	}

	void Info() {
		calcS();
		calcP();
		cout << "SQUARE Information:" << endl;
		cout << "Side = " << a << endl;
		cout << "S = " << S << endl;
		cout << "P = " << P << endl;
		cout << endl;
	}

};

/////////////////////////////////////////////////ОСНОВНАЯ ПРОГРАММА////////////////////////////////////////////////////
int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	//Создаем хранилище
	MyStorage<Shape> storage;

	// добавляем в него объекты
	for (int i = 0; i < 10; i += 2) {
		int val = rand() % 99 + 1;
		storage.addToStor(new Circle(val));
		cout << "The object CIRCLE is added to the storage, the index is " << i << endl << endl;
		int val1 = rand() % 99 + 1;
		storage.addToStor(new Square(val1));
		cout << "The object SQUARE is added to the storage, the index is " << i + 1 << endl << endl;
	}

	//обращаемся поочередно ко всем
	for (int i = 0; i < storage.size; i++)
	{
		cout << "Element number " << i << endl;
		storage.getElem(i)->Info();
	}

	return 0;
}
