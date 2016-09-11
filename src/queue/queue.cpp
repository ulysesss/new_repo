/*
 * queue.cpp
 *
 *  Created on: 28 авг. 2016 г.
 *      Author: 1
 */
//#define test_Q
#ifdef test_Q
class Queue{
	enum {Q_SIZE = 10};
	private:
		// Закрытое представление будет разработано позже
	public:
		Queue(int qs = Q_SIZE) ; 			// создание очереди с предельным размером qs
		~Queue();
		bool isempty() const;
		bool isfull() const;
		int queuecount () const;
		bool enqueue(const Item &item); 	// добавление элемента в конец
		bool dequeue(Item &item);		 	// удаление элемента из начала
};

	Queue linel; 		// очередь с предельным размером 10 элементов
	Queue line2 (20); 	// очередь с предельным размером 20 элементов
#endif
