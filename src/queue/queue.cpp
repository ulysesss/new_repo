/*
 * queue.cpp
 *
 *  Created on: 28 ���. 2016 �.
 *      Author: 1
 */
//#define test_Q

#ifdef test_Q
class Queue{
	enum {Q_SIZE = 10};
	private:
		// �������� ������������� ����� ����������� �����
	public:
		Queue(int qs = Q_SIZE) ; 			// �������� ������� � ���������� �������� qs
		~Queue();
		bool isemptyO const;
		bool isfull() const;
		int queuecount () const;
		bool enqueue(const Item &item); 	// ���������� �������� � �����
		bool dequeue(Item &item);		 	// �������� �������� �� ������
};

	Queue linel; 		// ������� � ���������� �������� 10 ���������
	Queue line2 (20); 	// ������� � ���������� �������� 20 ��������� => WTF???
#endif
