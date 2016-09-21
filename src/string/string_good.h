/*
 * string_good.h
 *
 *  Created on: 21 ���. 2016 �.
 *      Author: 1
 */

#ifndef STRING_STRING_GOOD_H_
#define STRING_STRING_GOOD_H_
#include <iostream>
#define signature_1
using std::ostream;
using std::istream;
class String{

	private:
	char * str; // ��������� �� ������
		int len;
		static int num_strings;

	public:
		// ������������ � ������ ������
		String(const char * s) ;
		String();
		String(const String &) ;
		~String();

		int length () const { return len; }

		// ������ ������������� ��������
		String & operator=(const String &) ;
		String & operator=(const char *);
		/*
		 ��������� ��������� + �.�.
			Type& operator+=( Type const & );
   	   	���
   	   	friend Type operator+( Type lhs, Type const & rhs ) {
		return lhs+=rhs;
		stackoverflow.com/questions/6067535/error-with-c-operator-overloading
		*/
		#ifdef signature_1
			String operator+(const String &st1);
		#else
			friend String operator+(String st1, const String &st2);
		#endif
		char & operator [] (int i) ;
		const char & operator[] (int i) const;


		// ������������� ������� ������������� ��������
		friend bool operator<(const String &st1, const String &st2);
		friend bool operator>(const String &stl, const String &st2);
		friend bool operator==(const String &st1, const String &st2);

		friend ostream & operator << (ostream & os, const String & st) ;
		friend istream & operator << (istream & is, String & st) ;
		// ����������� �������
		static int HowMany();
		static const int CINLIM = 80;
};

int Test_String_good (void) ;
void test_new_with_placement (void);

#endif /* STRING_STRING_GOOD_H_ */
