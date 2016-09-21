#include "queue.h"
#include <iostream>
#include <cstdlib> // для rand() и srand()
#include <ctime> // для time()
// Методы класса Queue
/*
 *  Инициализация списком (из одного элемента)
 *  синтаксис: qsize = qs
 */
Queue::Queue (int qs) : qsize(qs){
	front = rear = nullptr;
	items = 0;
}

Queue::~Queue (){
	Node * temp;
	while (front != nullptr){ 	// пока очередь не пуста
	temp = front;				// сохранение адреса начального элемента
	front = front->next;		// переустановка указателя на следующий элемент
	delete temp;				// удаление предыдущего начального элемента (для этого и нужен temp)
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

// Добавление элемента в очередь
bool Queue::enqueue (const Item & item){
	if (isfull ())
		return false;
	Node * add = new Node; 		// создание узла
	add->item = item; 		// занесение указателей на узлы
	add->next = nullptr; 		// или nullptr
	items++;				// увеличить счетчик кол-ва эл-тов на 1
	if (front == nullptr) 		// если очередь пуста,
		front = add; 		// элемент помещается в начало
	else
		rear->next = add; 	// иначе он помещается в конец
	rear = add; 			// указатель конца указывает на новый узел
	return true;
}

// Удаление элемента из очереди
//Предполагается, что клиент не уходит из очереди  спонтанно и очередь ведет себя строго как LIFO.

bool Queue::dequeue(Item & item){
	if (front == nullptr)
		return false;		// очередь пуста
	/*
	 * 	Предоставить вызывающей функции первый элемент очереди. Для этого часть
		данных текущего узла front копируется в ссылочную переменную, переданную
		в метод. Таким образом, предполагается, что при вызове в функцию передается
		переменная, в которую заносится информация о только что обслуженном клиенте
	 */
	item = front->item;
	items--;				// уменьшение числа элементов
	Node * temp = front; 	// сохранение местоположения первого элемента
	front = front->next; 	// сдвиг указателя начала на следующий элемент
	delete temp; 			// удаление предыдущего первого элемента
	if (items == 0)
		rear = nullptr;
	return true;
}

// Метод класса Customer
// При появлении клиента фиксируется момент его прибытия, а время
// обслуживания выбирается случайным образом из диапазона 1-3
void Customer::set(long when){
	processtime = std::rand() % 3 + 1;
	arrive = when;
}

/*
 * 	Интересной проблемой является определение, появился ли новый клиент.
	Предположим, что в среднем за час появляются 10 клиентов, т.е. один клиент каж­
	дые шесть минут. Программа вычисляет и сохраняет эту величину в переменной
	min_per_cust. Однако в реальности клиенты не будут появляться точно через 6 ми­
	нут, и нужен более случайный процесс, который моделирует появление одного клиен­
	та в среднем за шесть минут. Для определения, появился ли клиент во время минутного
	цикла, в программе используется функция:
 */
bool newcustomer(double x){
return (std::rand() * x / RAND_MAX < 1) ;
}
/*
 * 	Вот как работает данный код. Значение RAND MAX определено в файле cstd lib
	(ранее std lib .h ) и представляет собой наибольшее значение, которое может возвра­
	щать функция rand () (наименьшее равно 0). Предположим, что среднее время х ме­
	жду появлениями клиентов равно 6. Тогда значение rand () * х / RAND_MAX попадает
	куда-то в интервал от 0 до 6. В частности, оно будет меньше 1 в среднем одну шестую
	часть времени. Данная функция может выдать двух клиентов с промежутком в одну
	минуту, а может и с интервалом 20 минут. Такое нерегулярное поведение как раз и
	отличает реальные процессы от хронологически точных поступлений клиентов по
	одному каждые 6 минут.
 */
//============================================================================
const int MIN_PER_HR = 60;
// тестирование очереди
void Test_Queue (void){

	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;

	std::srand(std::time(0)); // случайная инициализация rand()
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: "; // ввод максимального размера очереди
	int qs;
	cin >> qs;
	Queue line(qs); // очередь может содержать до qs людей
	cout << "Enter the number of simulation hours: "; // ввод количества эмулируемых часов
	int hours; // часы эмуляции
	cin >> hours;

	// Эмуляция будет запускать один цикл в минуту
	long cyclelimit = MIN_PER_HR * hours; // количество циклов
	cout << "Enter the average number of customers per hour: ";
	// Ввод количества клиентов в час
	double perhour; // среднее количество появлений за час
	cin >> perhour;
	double min_per_cust; // среднее время между появлениями
	min_per_cust = MIN_PER_HR / perhour;
	Item temp; // данные нового клиента
	long turnaways = 0; // не допущены в полную очередь

	long customers = 0;
	long served = 0;
	long sum_line = 0;
	int wait_time = 0;
	long line_wait = 0;

//запустить цикл, каждое выполнение которого соответствует одной минуте моделируемого времени.
	for (int cycle = 0; cycle < cyclelimit; cycle++){
		if (newcustomer(min_per_cust)){ // есть подошедший клиент
			if (line.isfull ())			// очередь заполнена
				turnaways++;
			else{
				customers++;
				temp.set(cycle); 	// cycle = время прибытия и выбор случайного времени обслуживания
				line.enqueue(temp); // добавление новичка в очередь
				}
		}
		/*
		 * 	Если никто не обслуживается, выбрать из очереди первого человека. Определить
			время ожидания его обслуживания и занести в счетчик wait time необходимое
			ему время обслуживания
		*/
		if (wait_time <= 0 && !line.isempty()){
			line.dequeue (temp);
			wait_time = temp.ptime();
			line_wait += cycle - temp.when();
			served++;     // считается, что если клиент подошел, то он уже served
		}
		//Если в данный момент обслуживается клиент
		if (wait_time > 0)
			wait_time--;
		sum_line += line.queuecount ();
	}
	// Вывод результатов
	if (customers > 0){
	cout << "customers accepted: " << customers << endl;
	cout << " customers served: " << served << endl;
	cout << " turnaways: " << turnaways << endl;
	cout << "average queue size: ";
	cout.precision (2);

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << (double) sum_line / cyclelimit << endl;
	cout << " average wait time: " // среднее время ожидания (минут)
	<< (double) line_wait / served << " minutes\n";
	}
	else
	cout << "No customers!\n"; // клиентов нет
}
