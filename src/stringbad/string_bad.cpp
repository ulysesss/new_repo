/*
 * stringbad.cpp
 *
 *  Created on: 20 ���. 2016 �.
 *      Author: 1
 */
#include <string_bad.h>
using namespace std;

//=================================================================================================
/*
	����������� ���� ������ �������� ������ ���������:
	��������� ������� ������ ���� ����� �����������
	���������� ������ ���������� �� ���������� ����������� ��������.
	������� �������, ����������� ���� ��������� ������������ �����
	��������� ������� ������ � ��� ������ ����� �������� ��� ���� ������ �����.
*/
/*
 * ������� �������������� ��� ���������� ��������
 */
int StringBad::num_strings = 0;

// 	 	 ���� �������� ������������ � .h, �� �� ���������� => WTF??? �.�. � Embarcadero ����������
/*
 	 ����������� �� ���������
 */
StringBad::StringBad (){
	len = 4;
	str = new char [4] ;
	std::strcpy(str, "C++"); // ������ �� ���������
	num_strings++;
	cout << num_strings << ": \"" << str<< "\" default object created\n"; // ��� ����� �������
}
/*
 * ����������� � �����������
 */
StringBad::StringBad(const char * s){
	len = std::strlen (s);			// �������� ������ ����������� ��������� (��� ����� ����???)
	str = new char[len +1];			// �������� ������������ ������ (+1 �����)
	std::strcpy (str, s);
		/*
		C����� �� �������� � �������. ������� ��������� ��������,
		� ����, � ��� ������ ������ ���������, ��� �� �����.
		������, ��� ��� ������ ������:
		str = s;  ���� ��� ������ ��������� �����, �� �� ������� ����� ������.
		*/
	num_strings++;					// ���������������� ����� ������� ������
	/*
	 * ������� ��������� �������� ����� ������ � �������
	 */
	cout << num_strings <<": \"" << str << "\" object created\n";
}

/*
 * 	����������
 */
StringBad::~StringBad() // ����������� ����������
{
	cout <<"\""<< str << "\" object deleted, ";
	--num_strings;
	cout << num_strings << " left \n";
	delete []str;
}

/*
*	������������� �������� ������ ��� ������ ������
*/

std::ostream & operator << (std::ostream & os, const StringBad & st){
	os << st.str; return os;
}
//====================================================================================================
/*
 *
 * �������� ����������� ������
 */
void callmel(StringBad & rsb){
	cout << "String passed by reference:\n"; 	// ������, ���������� �� ������
	cout << " \"" << rsb << "\"\n";
}

void callme2(StringBad sb){
	cout << "String passed by value:\n"; 			// ������, ���������� �� ��������
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
			 * ����� ������������ ����������� ����������� (�������)
			 * ������� �� �������������� �������� ����������
			 * num_strings => ������� �������
	 */
	StringBad sailor = sports;
	cout << "sailor: " << sailor << endl;
	cout << "Assign one object to another:\n";
	StringBad knot;
	knot = headlinel;
	cout << "knot: " << knot << endl;
	cout << "Exiting the block.\n";
	/*
		 * ����� �������������� ���������� ����������� ����
		 * �������������. ����������� ��� �������������� ����������
		 * ���������� � �������, �������� �� ��������:
		 * knots => sailor => sport
	 */
}
//--------------------------------------------------------------------------------------------
/*
 *  ������� ����������� ����������� ������������ ����������� �� ��������.
 *  ����������, � ������� � ���������� ��� ������ ����������� ��������� ��������:
    sailor.str = sport.str;
    ���� �������� �������� �� ������, � ��������� �� ������. �� ���� ����� ���� ���
	������� sailor ��������� �������������� �������� sports, ��������� ��� �������
	�� �� ���� � �� �� ������. ��� �� ��������, ����� ������� operator<< () ����������
	��������� ��� ������ ������. �� ��� ���������� ���������, ����� ���������� �������
	���. ���� ���������� StringBad ����������� ������, �� ������� ��������� ���������
	str. ��������� ����������� sailor:
 *
 */

