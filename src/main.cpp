//============================================================================
// Name        : 01.cpp
// Author      : Me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string_bad.h>
#include <string_good.h>
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
	 * 		�������� ����������� vs ������������� ��������
	 */
	String str1 = String ("Hello world!");		// ����������� � �����������
	String str2 = str1;							// ����������� �����������
	String str3;								// Default �����������
	str3 = str2;								// �������� ������������ (������������� ��� ������� ������)

	int exit=1;
	while(exit)	{
		//Test_String_Bad();
		//Test_String_good () ;
		test_new_with_placement();
		cin>>exit;
		exit = 0;
	}
	return 0;
}
//---------------------------------------------------------------------------
