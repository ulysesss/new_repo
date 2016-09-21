//============================================================================
// Name        : 01.cpp
// Author      : Me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string_bad.h>
#include <string_good.h>
#include "queue.h"
#include "myclass.h"
using namespace std;
//---------------------------------------------------------------------------
/*
 * 	Tail return Type
 */
template <typename T1, typename T2>
auto add(T1 t1, T2 t2) -> decltype(t1 + t2){
   return t1 + t2;
}
//---------------------------------------------------------------------------
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	double a = 0.5, b = 0.5;
	auto c = add(a,b);
	c++;
	/*
	 * 		ѕроверка конструктор vs перегруженный оператор
	 */
	String str1 = String ("Hello world!");		//  онструктор с параметрами
	String str2 = str1;							//  онструктор копировани€
	String str3;								// Default конструктор
	str3 = str2;								// ќпераци€ присваивани€ (перегруженна€ дл€ данного класса)
	String str_0 = "This is ";
	String str_1 = "sum check!";
	std::string native_str = "Ho-ho! ";
	native_str+="I'll fuck you!";
	int len = native_str.length();
	len++;

	//String str_2;
	//str_2 = str_0 + str_1;
	//cout<<str_2<<endl;

	int exit=1;
	while(exit)	{
		//Test_String_Bad();
		//Test_String_good () ;
		//Test_Queue ();
		//test_new_with_placement();
		cin>>exit;
		exit = 0;
	}
	return 0;
}
//---------------------------------------------------------------------------
