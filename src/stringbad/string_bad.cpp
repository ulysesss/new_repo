/*
 * stringbad.cpp
 *
 *  Created on: 20 авг. 2016 г.
 *      Author: 1
 */
#include <string_bad.h>
using namespace std;

//=================================================================================================
/*
	Статический член класса обладает особым свойством:
	программа создает только одну копию статической
	переменной класса независимо от количества создаваемых объектов.
	Другими словами, статический член совместно используется всеми
	объектами данного класса — как единый номер телефона для всех членов семьи.
*/
/*
 * Поэтому инициалировать его необходимо отдельно
 */
int StringBad::num_strings = 0;

// 	 	 Если написать конструкторы в .h, то не собирается => WTF??? Т.к. в Embarcadero собирается
/*
 	 Конструктор по умолчанию
 */
StringBad::StringBad (){
	len = 4;
	str = new char [4] ;
	std::strcpy(str, "C++"); // строка по умолчанию
	num_strings++;
	cout << num_strings << ": \"" << str<< "\" default object created\n"; // для целей отладки
}
/*
 * Конструктор с параметрами
 */
StringBad::StringBad(const char * s){
	len = std::strlen (s);			// получить размер переданного указателя (так можно было???)
	str = new char[len +1];			// выделить динамиически память (+1 зачем)
	std::strcpy (str, s);
		/*
		Cтрока НЕ хранится в объекте. Символы находятся отдельно,
		в куче, а сам объект просто указывает, где их найти.
		Учтите, что так делать нельзя:
		str = s;  Этот код просто сохраняет адрес, но не создает копию строки.
		*/
	num_strings++;					// инкрементировать общий счетчик данных
	/*
	 * Вывести результат создания новой строки в консоль
	 */
	cout << num_strings <<": \"" << str << "\" object created\n";
}

/*
 * 	Деструктор
 */
StringBad::~StringBad() // необходимый деструктор
{
	cout <<"\""<< str << "\" object deleted, ";
	--num_strings;
	cout << num_strings << " left \n";
	delete []str;
}

/*
*	Перегруженный оператор вывода для класса строки
*/

std::ostream & operator << (std::ostream & os, const StringBad & st){
	os << st.str; return os;
}
//====================================================================================================
/*
 *
 * Проверка написанного класса
 */
void callmel(StringBad & rsb){
	cout << "String passed by reference:\n"; 	// строка, переданная по ссылке
	cout << " \"" << rsb << "\"\n";
}

void callme2(StringBad sb){
	cout << "String passed by value:\n"; 			// строка, переданная по значению
	cout << " \"" << sb << "\"\n";
}


void Test_String_Bad(void){
	cout <<"Starting an inner block.\n";
	StringBad headlinel ("Celery Stalks at Midnight");
	StringBad headline2 ("Lettuce Prey");
	StringBad sports("Spinach Leaves Bowl for Dollars");
	cout << "headlinel: " << headlinel << endl;
	cout << "headline2: " << headline2 << endl;
	cout << "sports: " << sports << endl;
	callmel(headlinel);
	cout << "headlinel: " << headlinel << endl;
	callme2(headline2);
	cout << "headline2: " << headline2 << endl;
	cout << "Initialize one object to another:\n";
	/*
			 * здесь используется конструктор копирования (неявный)
			 * который не инкрементирует значение переменной
			 * num_strings => Рушится подсчет
	 */
	StringBad sailor = sports;
	cout << "sailor: " << sailor << endl;
	cout << "Assign one object to another:\n";
	StringBad knot;
	knot = headlinel;
	cout << "knot: " << knot << endl;
	cout << "Exiting the block.\n";
	/*
		 * Здесь автоматические переменные заканчивают свое
		 * существование. Деструкторы для автоматических переменных
		 * Вызываются в порядке, обратном их созданию:
		 * knots => sailor => sport
	 */
}
//--------------------------------------------------------------------------------------------
/*
 *  неявный конструктор копирования осуществляет копирование по значению.
 *  Рассмотрим, к примеру В результате его работы выполняется следующий оператор:
    sailor.str = sport.str;
    Этот оператор копирует не строку, а указатель на строку. То есть после того как
	объекту sailor присвоено первоначальное значение sports, появилось два указате­
	ля на одну и ту же строку. Это не проблема, когда функция operator<< () использует
	указатель для вывода строки. Но это становится проблемой, когда вызывается деструк­
	тор. Ведь деструктор StringBad освобождает память, на которую указывает указатель
	str. Результат уничтожения sailor:
 *
 */

