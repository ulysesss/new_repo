#include "queue.h"
#include <iostream>
#include <cstdlib> // ��� rand() � srand()
#include <ctime> // ��� time()
// ������ ������ Queue
/*
 *  ������������� ������� (�� ������ ��������)
 *  ���������: qsize = qs
 */
Queue::Queue (int qs) : qsize(qs){
	front = rear = nullptr;
	items = 0;
}

Queue::~Queue (){
	Node * temp;
	while (front != nullptr){ 	// ���� ������� �� �����
	temp = front;				// ���������� ������ ���������� ��������
	front = front->next;		// ������������� ��������� �� ��������� �������
	delete temp;				// �������� ����������� ���������� �������� (��� ����� � ����� temp)
	}
}

bool Queue::isempty () const{
	return items == 0;
}

bool Queue::isfull () const{
	return items == qsize;
}

int Queue::queuecount () const{
	return items;
}

// ���������� �������� � �������
bool Queue::enqueue (const Item & item){
	if (isfull ())
		return false;
	Node * add = new Node; 		// �������� ����
	add->item = item; 		// ��������� ���������� �� ����
	add->next = nullptr; 		// ��� nullptr
	items++;				// ��������� ������� ���-�� ��-��� �� 1
	if (front == nullptr) 		// ���� ������� �����,
		front = add; 		// ������� ���������� � ������
	else
		rear->next = add; 	// ����� �� ���������� � �����
	rear = add; 			// ��������� ����� ��������� �� ����� ����
	return true;
}

// �������� �������� �� �������
//��������������, ��� ������ �� ������ �� �������  ��������� � ������� ����� ���� ������ ��� LIFO.

bool Queue::dequeue(Item & item){
	if (front == nullptr)
		return false;		// ������� �����
	/*
	 * 	������������ ���������� ������� ������ ������� �������. ��� ����� �����
		������ �������� ���� front ���������� � ��������� ����������, ����������
		� �����. ����� �������, ��������������, ��� ��� ������ � ������� ����������
		����������, � ������� ��������� ���������� � ������ ��� ����������� �������
	 */
	item = front->item;
	items--;				// ���������� ����� ���������
	Node * temp = front; 	// ���������� �������������� ������� ��������
	front = front->next; 	// ����� ��������� ������ �� ��������� �������
	delete temp; 			// �������� ����������� ������� ��������
	if (items == 0)
		rear = nullptr;
	return true;
}

// ����� ������ Customer
// ��� ��������� ������� ����������� ������ ��� ��������, � �����
// ������������ ���������� ��������� ������� �� ��������� 1-3
void Customer::set(long when){
	processtime = std::rand() % 3 + 1;
	arrive = when;
}

/*
 * 	���������� ��������� �������� �����������, �������� �� ����� ������.
	�����������, ��� � ������� �� ��� ���������� 10 ��������, �.�. ���� ������ ���
	��� ����� �����. ��������� ��������� � ��������� ��� �������� � ����������
	min_per_cust. ������ � ���������� ������� �� ����� ���������� ����� ����� 6 ��
	���, � ����� ����� ��������� �������, ������� ���������� ��������� ������ �����
	�� � ������� �� ����� �����. ��� �����������, �������� �� ������ �� ����� ���������
	�����, � ��������� ������������ �������:
 */
bool newcustomer(double x){
return (std::rand() * x / RAND_MAX < 1) ;
}
/*
 * 	��� ��� �������� ������ ���. �������� RAND MAX ���������� � ����� cstd lib
	(����� std lib .h ) � ������������ ����� ���������� ��������, ������� ����� ������
	���� ������� rand () (���������� ����� 0). �����������, ��� ������� ����� � ��
	��� ����������� �������� ����� 6. ����� �������� rand () * � / RAND_MAX ��������
	����-�� � �������� �� 0 �� 6. � ���������, ��� ����� ������ 1 � ������� ���� ������
	����� �������. ������ ������� ����� ������ ���� �������� � ����������� � ����
	������, � ����� � � ���������� 20 �����. ����� ������������ ��������� ��� ��� �
	�������� �������� �������� �� �������������� ������ ����������� �������� ��
	������ ������ 6 �����.
 */
//============================================================================
const int MIN_PER_HR = 60;
// ������������ �������
void Test_Queue (void){

	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;

	std::srand(std::time(0)); // ��������� ������������� rand()
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: "; // ���� ������������� ������� �������
	int qs;
	cin >> qs;
	Queue line(qs); // ������� ����� ��������� �� qs �����
	cout << "Enter the number of simulation hours: "; // ���� ���������� ����������� �����
	int hours; // ���� ��������
	cin >> hours;

	// �������� ����� ��������� ���� ���� � ������
	long cyclelimit = MIN_PER_HR * hours; // ���������� ������
	cout << "Enter the average number of customers per hour: ";
	// ���� ���������� �������� � ���
	double perhour; // ������� ���������� ��������� �� ���
	cin >> perhour;
	double min_per_cust; // ������� ����� ����� �����������
	min_per_cust = MIN_PER_HR / perhour;
	Item temp; // ������ ������ �������
	long turnaways = 0; // �� �������� � ������ �������

	long customers = 0;
	long served = 0;
	long sum_line = 0;
	int wait_time = 0;
	long line_wait = 0;

//��������� ����, ������ ���������� �������� ������������� ����� ������ ������������� �������.
	for (int cycle = 0; cycle < cyclelimit; cycle++){
		if (newcustomer(min_per_cust)){ // ���� ���������� ������
			if (line.isfull ())			// ������� ���������
				turnaways++;
			else{
				customers++;
				temp.set(cycle); 	// cycle = ����� �������� � ����� ���������� ������� ������������
				line.enqueue(temp); // ���������� ������� � �������
				}
		}
		/*
		 * 	���� ����� �� �������������, ������� �� ������� ������� ��������. ����������
			����� �������� ��� ������������ � ������� � ������� wait time �����������
			��� ����� ������������
		*/
		if (wait_time <= 0 && !line.isempty()){
			line.dequeue (temp);
			wait_time = temp.ptime();
			line_wait += cycle - temp.when();
			served++;     // ���������, ��� ���� ������ �������, �� �� ��� served
		}
		//���� � ������ ������ ������������� ������
		if (wait_time > 0)
			wait_time--;
		sum_line += line.queuecount ();
	}
	// ����� �����������
	if (customers > 0){
	cout << "customers accepted: " << customers << endl;
	cout << " customers served: " << served << endl;
	cout << " turnaways: " << turnaways << endl;
	cout << "average queue size: ";
	cout.precision (2);

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << (double) sum_line / cyclelimit << endl;
	cout << " average wait time: " // ������� ����� �������� (�����)
	<< (double) line_wait / served << " minutes\n";
	}
	else
	cout << "No customers!\n"; // �������� ���
}
