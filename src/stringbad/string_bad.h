//--------------------------------------------------------------------------------
#ifndef STRINGBAD_STRING_BAD_H_
#define STRINGBAD_STRING_BAD_H_
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*
 	 	 ������ �������������� ������
 */
class StringBad
{
	private:
	char * str; 				//	������, ������������ � ������
	int len; 					//	����� ������
	static int num_strings; 	//	����� ���������� ����� - ����������� ���� (��� ���� ������� ��� ���� �����)
	public:
	StringBad(const char * s) ; //
	StringBad (); 				//
	~StringBad(); 				//
	friend std::ostream & operator << (std::ostream & os, const StringBad & st) ;
};




void callmel(StringBad &) ; 	// �������� �� ������
void callme2(StringBad); 		// �������� �� ��������
void Test_String_Bad(void); 	// ��������

#endif
