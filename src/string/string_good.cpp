/*
 * string_good.cpp
 *
 *  Created on: 21 авг. 2016 г.
 *      Author: 1
 */

#include <cstring> // в некоторых случаях - string.h
#include "string_good.h" // включение <iostream>
using std::cin;
using std::cout;
using std::endl;

// Инициализация статического члена класса
int String::num_strings = 0;

// Статический метод, возвращающий количество созданных строк
int String::HowMany (){
	return num_strings;
}

//--------------------------------------------------------------------------------------
// Методы класса
// конструктор без параметров (по умолчанию)
String::String (){
	len = 4;
	str = new char [1];
	str[0] = '\0';
	num_strings++;
}
/*
 *  Каким не должен быть конструктор. Он не будет совместим с деструктором,
 *  поскольку в нем вызывается delete [] str;
 *  Поскольку деструктор - один, то он сделан под оптимальный вариант класса
 *  и конструтор(ы) необходимо строить таким образомЮ чтобы они все согласовывались
 *  с деструктором.
 */
#ifdef bad_constructor
String::String(){
	str = "default string"; // неверно: не хватает new []
	len = std::strlen(str);
}

#endif
// Конструктор от массива символов
String::String(const char * s){
	len = std::strlen (s);
	str = new char[len +1];
	std::strcpy (str, s);
	num_strings++;
}
// конструктор копирования (Т.е. по сигнатуре компилятор определяет, что это именно конструктор копирования? - Да)
String::String(const String & st){
	num_strings++;				// обработка обновления статического члена
	len = st.len;				// длина та же
	str = new char [len + 1] ;	// выделение памяти
	std::strcpy(str, st.str);	// копирование строки в новое место
}

// Деструктор
String::~String() {
	--num_strings;
	delete [] str;
}

//--------------------------------------------------------------------------------------
/*
 * Методы перегруженных операций
 */

/*
 * 		Явно определенный оператор присваивания Присваивание объекта String объекту String

 */

/*
 * Вопрос: когда вызывается оператор присваивания, а когда конструктор копирования

	Ответ:
		StringBad knot;		//	Объект создан и проинициалирован default конструктором.
		knot = headlinel; 	// 	вызывается операция присваивания
	В то же время:
		StringBad metoo = knot; // используется конструктор копирования,
								// но возможно и присваивание
*/

String & String::operator = (const String & st){
	if (this == &st)
		return *this;

	delete [] str;			// необходимо освободить ранее выделенную память (так как она выделена при вызовек конструктора)
	len = st. len;
	str = new char [len+1] ;
	std::strcpy(str, st.str);

	return *this;
}

// Присваивание С-строки объекту String
String & String::operator = (const char * s){

	if(str!= nullptr)			// на всякий случай
		delete [] str;
	else
		cout << "Memory access error. Something went wrong" << endl;
	len = std::strlen(s);
	str = new char [len + 1];
	std::strcpy(str, s);

	return *this;
}

// Доступ для чтения и записи отдельных символов в неконстантном объекте String
char & String::operator[] (int i){
	return str[i];
}

// Доступ только для чтения отдельных символов в константном объекте String
const char & String:: operator [] (int i) const{
	return str [i] ;
}

// Дружественные функции перегруженных операций
bool operator < (const String &stl, const String &st2){
	return (std::strcmp(stl.str, st2.str) < 0) ;
}

bool operator > (const String &stl, const String &st2){
	return st2.str < stl.str;
}

bool operator==(const String &stl, const String &st2){
	return (std::strcmp(stl.str, st2.str) == 0);
}

// Простой вывод String
ostream & operator << (ostream & os, const String & st){
	os << st.str;
	return os;
}

// Простой ввод String
istream & operator >> (istream & is, String & st){
	char temp[String::CINLIM];			// автомастический объект длиной CINLIM
	is.get(temp, String::CINLIM);
	if (is)
	st = temp;
	while (is && is.get() != '\n')
	continue;
	return is;
}
//------------------------------------------------------------------------------
/*
 * Test String good
 */
const int ArSize = 10;
const int MaxLen =81;

int Test_String_good (void) {

	using std::cout;
	using std::cin;
	using std::endl;

	String name;

	cout <<"Hi, what's your name?\n"; 				// ввод имени
	cin >> name;
	cout << name << ", please enter up to " << ArSize <<" short sayings <empty line to quit>:\n"; 		// ввод поговорки

	String sayings[ArSize]; 							// массив объектов
	char temp[MaxLen]; 									// временное хранилище для строки
	int i;

	for (i = 0; i < ArSize; i++){
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')  				// пустая строка?
			break;									// i не инкрементируется
		else
			sayings [i] = temp;						// перегруженное присваивание
	}
	//--------------------------- Part 2
	int total = i; // общее количество прочитанных строк
	if ( total > 0)
	{
	cout << "Here are your sayings:\n"; // вывод поговорок
	for (i = 0; i < total; i++)
		cout << sayings [i] [0] << ": "<< sayings [i] << endl;
	int shortest = 0;
	int first = 0;
	for (i = 1; i < total; i++){
		if (sayings[i].length () < sayings[shortest].length ())
			shortest = i;
		if (sayings[i] < sayings[first])
			first = i;
	}
	cout << "Shortest saying:\n" << sayings[shortest] << endl;
	// Самая короткая поговорка
	cout << "First alphabetically:\n" << sayings[first] << endl;
	// Первая по алфавиту
	cout << "This program used "<< String::HowMany ()
	<< " String objects. Bye.\n";
	// Количество используемых объектов String
	}
	else
		cout << "No input! Bye.\n"; // ничего не было введено
	return 0;

}


