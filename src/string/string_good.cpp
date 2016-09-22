/*
 * string_good.cpp
 *
 *  Created on: 21 ���. 2016 �.
 *      Author: 1
 */

#include <cstring> // � ��������� ������� - string.h
#include "string_good.h" // ��������� <iostream>
using std::cin;
using std::cout;
using std::endl;

// ������������� ������������ ����� ������
int String::num_strings = 0;

// ����������� �����, ������������ ���������� ��������� �����
int String::HowMany (){
	return num_strings;
}

//--------------------------------------------------------------------------------------
// ������ ������
// ����������� ��� ���������� (�� ���������)
String::String (){
	len = 4;
	str = new char [1];
	str[0] = '\0';
	num_strings++;
}
/*
 *  ����� �� ������ ���� �����������. �� �� ����� ��������� � ������������,
 *  ��������� � ��� ���������� delete [] str;
 *  ��������� ���������� - ����, �� �� ������ ��� ����������� ������� ������
 *  � ����������(�) ���������� ������� ����� �������� ����� ��� ��� ���������������
 *  � ������������.
 */
#ifdef bad_constructor
String::String(){
	str = "default string"; // �������: �� ������� new []
	len = std::strlen(str);
}

#endif
// ����������� �� ������� ��������
String::String(const char * s){
	len = std::strlen (s);
	str = new char[len +1];
	std::strcpy (str, s);
	num_strings++;
}
// ����������� ����������� (�.�. �� ��������� ���������� ����������, ��� ��� ������ ����������� �����������? - ��)
String::String(const String & st){
	num_strings++;				// ��������� ���������� ������������ �����
	len = st.len;				// ����� �� ��
	str = new char [len + 1] ;	// ��������� ������
	std::strcpy(str, st.str);	// ����������� ������ � ����� �����
}

// ����������
String::~String() {
	--num_strings;
	delete [] str;
}

//--------------------------------------------------------------------------------------
/*
 * ������ ������������� ��������
 */

/*
 * 		���� ������������ �������� ������������ ������������ ������� String ������� String

 */

/*
 * ������: ����� ���������� �������� ������������, � ����� ����������� �����������

	�����:
		StringBad knot;		//	������ ������ � ���������������� default �������������.
		knot = headlinel; 	// 	���������� �������� ������������
	� �� �� �����:
		StringBad metoo = knot; // ������������ ����������� �����������,
								// �� �������� � ������������
*/

String & String::operator = (const String & st){
	if (this == &st)
		return *this;
	delete [] str;			// ���������� ���������� ����� ���������� ������ (��� ��� ��� �������� ��� ������� ������������)
	len = st.len;
	str = new char [len+1] ;
	std::strcpy(str, st.str);
	return *this;
}

// ������������ �-������ ������� String
String & String::operator = (const char * s){

	if(str!= nullptr)			// �� ������ ������
		delete [] str;
	else
		cout << "Memory access error. Something went wrong" << endl;
	len = std::strlen(s);
	str = new char [len + 1];
	std::strcpy(str, s);

	return *this;
}

// ������ ��� ������ � ������ ��������� �������� � ������������� ������� String
char & String::operator[] (int i){
	return str[i];
}

// ������ ������ ��� ������ ��������� �������� � ����������� ������� String
const char & String::operator [] (int i) const{
	return str [i] ;
}

// + ����������� � �������� ������� (��������� this)
// ��������� this ��������� �� ������ ������ (����� � ���������) � �������� ������������ ��������
String String::operator+ (const String& s){
	// this - ������ � ������� ������������

		char* this_content = new char [this->len];
		memcpy(this_content, this->str, this->len);

		char* new_content = new char [s.len+this->len+1];		//
		/*
		 * Returns the length of the given byte string, that is,
		 * the number of characters in a character array whose
		 * first element is pointed to by str up to and not including the first null character
		 */
		memcpy(new_content, this_content, this->len);
		memcpy(new_content+this->len, s.str,s.len);
		new_content[s.len+this->len] = '\0';
		String tmp = new_content;
		delete [] new_content;
		delete [] this_content;
		return tmp;
}


#ifdef hernya
#ifdef signature_1
String String::operator + (const String &st1){
	if (!st1.len)
		return *this;
	int size = st1.len+this->len;
	char result_string_content [size];

	memcpy(result_string_content,  this->str, this->len);
	memcpy(result_string_content + this->len, st1.str, st1.len);
	String res_str = String(result_string_content);
	return res_str;
}
#else
/*
 *  ����� �������� ����� ��� ���������
 *  �� ��� �������� �� �������� ��������� ��������� ����� st1 => ���������� ����������� ����������
 */
String operator+(String st1, const String &st2){
	int size = st1.len+st2.len;
	char result_string_content [size];

	memcpy(result_string_content,  st1.str, st1.len);
	memcpy(result_string_content+st1.len,  st2.str, st2.len);
	//String res_str = String(result_string_content);
//	return res_str;
}
#endif
#endif

// ������������� ������� ������������� ��������
bool operator < (const String &st1, const String &st2){
	return (std::strcmp(st1.str, st2.str) < 0) ;
}

bool operator > (const String &st1, const String &st2){
	return st2.str < st1.str;
}

bool operator==(const String &st1, const String &st2){
	return (std::strcmp(st1.str, st2.str) == 0);
}

// ������� ����� String
ostream & operator << (ostream & os, const String & st){
	os << st.str;
	return os;
}

// ������� ���� String
istream & operator >> (istream & is, String & st){
	char temp[String::CINLIM];			// ��������������� ������ ������ CINLIM
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
const int MaxLen = 81;

int Test_String_good (void) {

	using std::cout;
	using std::cin;
	using std::endl;

	String name;

	cout <<"Hi, what's your name?\n"; 				// ���� �����
	cin >> name;
	cout << name << ", please enter up to " << ArSize <<" short sayings <empty line to quit>:\n"; 		// ���� ���������

	String sayings[ArSize]; 							// ������ ��������
	char temp[MaxLen]; 									// ��������� ��������� ��� ������
	int i;

	for (i = 0; i < ArSize; i++){
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')  				// ������ ������?
			break;									// i �� ����������������
		else
			sayings [i] = temp;						// ������������� ������������
	}
	//--------------------------- Part 2
	int total = i; // ����� ���������� ����������� �����
	if ( total > 0)
	{
	cout << "Here are your sayings:\n"; // ����� ���������
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
	// ����� �������� ���������
	cout << "First alphabetically:\n" << sayings[first] << endl;
	// ������ �� ��������
	cout << "This program used "<< String::HowMany ()
	<< " String objects. Bye.\n";
	// ���������� ������������ �������� String
	}
	else
		cout << "No input! Bye.\n"; // ������ �� ���� �������
	return 0;

}
//

