/*
 * new.cpp
 *
 *  Created on: 28 авг. 2016 г.
 *      Author: 1
 */
#include <iostream>
#include <string>
#include <new>
using namespace std;
const int BUF = 512;

class JustTesting{

	private:
		string words;
		int number;
	public:
		JustTesting	(const string & s = "Just Testing", int n = 0){
			words = s; number = n; cout << words << " constructed\n";
		}
		~JustTesting() {
			cout << words << " destroyed\n";
		}
		void Show() const {
			cout << words << ", " << number << endl;
		}
};

void test_new_with_placement (void){

	char * buffer = new char[BUF];			// выделение блока памяти (в куче)
	JustTesting *pc1, *pc2;

	pc1 = new (buffer) JustTesting;			// new с размещением
	pc2 = new JustTesting("Heapl", 20);		// new без размещения

	cout << "Memory block addresses:\n" << "buffer: "
	<< (void *) buffer << " heap: " << pc2 << endl;
	cout << "Memory contents:\n";
	cout << pc1 << ": " ;
	pc1->Show();
	cout << pc2 << " : " ;
	pc2->Show();

	JustTesting *pc3, *pc4;

	pc3 = new (buffer) JustTesting ("Bad Idea", 6) ; // new с размещением
	pc4 = new JustTesting("Heap2", 10);

	cout << "Memory contents:\n";
	cout << pc3 << ": ";
	pc3->Show();
	cout << pc4 << " : " ;
	pc4->Show();
	delete pc2;
	delete pc4;
	delete [] buffer;
	cout << "Done\n";
	return;
}

void test_new_with_placement2 (void){
	char * buffer = new char[BUF]; // получение блока памяти
	JustTesting *pc1, *pc2;

	pc1 = new (buffer) JustTesting; // размещение объекта в buffer
	pc2 = new JustTesting("Heapl", 20); // размещение объекта в куче

	cout << "Memory block addresses:\n" << "buffer: "
	<< (void *) buffer << " heap: " << pc2 << endl; // вывод адресов памяти
	cout << "Memory contents:\n"; // вывод содержимого памяти
	cout << pc1 << " : " ;
	pc1->Show();
	cout << pc2 << ": " ;
	pc2->Show();

	JustTesting *pc3, *pc4;
	// Фиксация ячейки, с которой работает new с размещением
	pc3 = new (buffer + sizeof (JustTesting) )
	JustTesting("Better Idea", 6) ;
	pc4 = new JustTesting("Heap2", 10);

	//вывод содержимого памяти
	cout << "Memory contents:\n";
	cout << pc3 << ": ";
	pc3->Show();
	cout << pc4 << ": ";
	pc4->Show();

	//освобождение Heapl
	//освобождение Неар2
	delete pc2;
	delete pc4;

	// Явное уничтожение объектов,
	pc3->~JustTesting();
	pc1->~JustTesting();
	delete [] buffer;
	cout << "Done\n";
	return;
}
