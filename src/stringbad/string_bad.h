//--------------------------------------------------------------------------------
#ifndef STRINGBAD_STRING_BAD_H_
#define STRINGBAD_STRING_BAD_H_
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*
 	 	 Пример несовершенного класса
 */
class StringBad
{
	private:
	char * str; 				//	Данные, содержащиеся в строке
	int len; 					//	Длина строки
	static int num_strings; 	//	общее количество строк - статический член (как один телефон для всей семьи)
	public:
	StringBad(const char * s) ; //
	StringBad (); 				//
	~StringBad(); 				//
	friend std::ostream & operator << (std::ostream & os, const StringBad & st) ;
};




void callmel(StringBad &) ; 	// передача по ссылке
void callme2(StringBad); 		// передача по значению
void Test_String_Bad(void); 	// проверка

#endif
