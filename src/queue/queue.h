// queue.h Ч интерфейс дл€ очереди
#ifndef QUEUE_H_
#define QUEUE_H_
extern void Test_Queue (void);
// ќчередь, содержаща€ элементы Customer
class Customer	{
	private:
		long arrive; 		// момент по€влени€ клиента
		int processtime; 	// врем€ обслуживани€ клиента
	public:
		Customer() { arrive = processtime =0; }
		void set(long when);
		long when() const { return arrive; }
		int ptime() const { return processtime; }
};
typedef Customer Item;

class Queue{
	private:
	// ќпределени€ области действи€ класса
	// Node - вложенна€ структура, локальна€ дл€ данного класса
		struct Node { Item item; struct Node* next;};
		enum {Q_SIZE = 10};
	// «акрытые члены класса
		Node* front; 			// указатель на начало Queue
		Node* rear; 			// указатель на конец Queue
		int items; 				// текущее количество элементов в Queue
		const int qsize; 		// максимальное количество элементов в Queue
		/*
		 * 	‘иктивные закрытые методы избавл€ют от написани€ конструктора копировани€ и оператора присваивани€
		 * 	и в то же врем€ переопредел€ют автоматически сгенерированные конструктор и оператор копировани€ (выполн€ющие
		 * 	нежелательное поверхностное копирование)
		 */
		Queue(const Queue & q):qsize (0) { } // ”преждающие объ€влени€ дл€ предотвращени€ открытого копировани€
		Queue & operator=(const Queue & q) { return *this; }
	public:
		Queue(int qs = Q_SIZE);
		~Queue();
		bool isempty() const;
		bool isfull() const;
		int queuecount () const;

		/*
		 * —игнатуа => работаем с константной ссылкой. “.е. исходный объект не копируетс€
		 * (так как это экземпл€р класса, то соотв. не вызываетс€ констркутор копировани€,
		 * что может быть нежелательно). —сылка константна€ => исходный объект не мен€етс€.
		 */
		bool enqueue(const Item &item);
		bool dequeue(Item &item);
};
#endif
