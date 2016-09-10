/*
 * string_good.h
 *
 *  Created on: 21 авг. 2016 г.
 *      Author: 1
 */

#ifndef STRING_STRING_GOOD_H_
#define STRING_STRING_GOOD_H_
#include <iostream>
using std::ostream;
using std::istream;
class String{

	private:
	char * str; // указатель на строку
		int len;
		static int num_strings;

	public:
		// Конструкторы и другие методы
		String(const char * s) ;
		String();
		String(const String &) ;
		~String();

		int length () const { return len; }

		// Методы перегруженных операций
		String & operator=(const String &) ;
		String & operator=(const char *);
		char & operator [ ] (int i) ;
		const char & operator[] (int i) const;

		// Дружественные функции перегруженных операций
		friend bool operator<(const String &st, const String &st2);
		friend bool operator>(const String &stl, const String &st2);
		friend bool operator==(const String &st, const String &st2);
		friend ostream & operator << (ostream & os, const String & st) ;
		friend istream & operator << (istream & is, String & st) ;

		// Статическая функция
		static int HowMany();
		static const int CINLIM = 80;
};

int Test_String_good (void) ;
void test_new_with_placement (void);

#endif /* STRING_STRING_GOOD_H_ */
