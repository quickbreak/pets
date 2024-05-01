#include <iostream>
#include <cassert>
#include <clocale>

using namespace std;


const int malo = -int(1e9);


struct node {
public:
	int value = malo;
	node* next = NULL;
	node(int value) :value(value), next(NULL) {};
	node() :value(malo), next(NULL) {};
};


struct linkedlist {
public:
	node* head;
	node* tail;
	linkedlist() : head(NULL), tail(NULL) {};

	// список пуст?
	bool empty() const {
		return head == NULL;
	};

	// добавить в конец элемент x
	void push_back(int value) {
		node* x = new node(value);
		// если это будет первый элемент (список пуст)
		if (this->empty()) {
			head = x;
			tail = x;
			return;
		}
		// если есть хотя бы один элемент
		tail->next = x;
		tail = x;
	};

	// добавить в начало элемент x
	void push_front(int value) {
		node* x = new node(value);
		// если это будет первый элемент (список пуст)
		if (this->empty()) {
			head = x;
			tail = x;
			return;
		}
		// если есть хотя бы один элемент
		x->next = head;
		head = x;
	};

	// вывести элементы списка
	void print() const {
		if (this->empty())
			return;
		node* current = head;
		while (current != NULL) {
			cout << current->value << ' ';
			current = current->next;
		}
		cout << '\n';
	};

	// поиск элемента по значению, первого по порядку
	node* find(int value) const {
		if (this->empty())
			return NULL;
		node* current = head;
		while (current != NULL) {
			if (current->value == value) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	};

	// удаление элемента по значению, если такой есть, первого по порядку
	void erase(int value) {
		if (this->empty())
			return;
		// если первый подошёл
		node* pointer;
		if (head->value == value) {
			pointer = head;
			head = head->next;
			// если элемент был всего один
			if (head == NULL) {
				tail = head;
			}
			delete pointer;
			return;
		}
		node* previous = head;
		node* current = previous->next;
		// иначе
		while (current != NULL) {
			// если нашли значение
			if (current->value == value) {
				previous->next = current->next;
				// если это был крайний элемент
				if (previous->next == NULL) {
					tail = previous;
				}
				delete current;
				return;
			}
			previous = current;
			current = current->next;
		}
	};

	// чтение списка от пользователя
	void fill() {
		if (!this->empty()) {
			cout << "Список не пуст. Очистите его, или добавляйте элементы в конец\n";
			return;
		}
		assert(this->empty());
		cout << "Введите размер списка\n";
		int n; cin >> n;
		cout << "Введите список: " << n << " целых чисел\n";
		int val;
		while (--n >= 0) {
			cin >> val;
			this->push_back(val);
		}
	};

	// автоматически собранный список
	void fill_auto() {
		if (!this->empty()) {
			cout << "Список не пуст. Очистите его, или добавляйте элементы в конец\n";
			return;
		}
		assert(this->empty());
		int n = 10;
		cout << "Автособранный список (" << n << " элементов):\n";
		for (int i = 1; i <= n; ++i) {
			this->push_back(i);
			// cout << i << ' ';
		}
		// cout << '\n';
		this->print();
	};

};


// удалить список
void clear(linkedlist& a) {
	if (a.empty())
		return;
	node* current = a.head;
	node* pointer;
	while (current != NULL) {
		pointer = current;
		current = current->next;
		delete pointer;
	}
	a.head = NULL;
	a.tail = NULL;
}

// создать массив списков на основе списка
linkedlist* create_a(linkedlist& b) {
	linkedlist* a = new linkedlist[10];
	if (b.empty())
		return a;
	node* current = b.head;
	while (current != NULL) {
		a[current->value / 10].push_back(current->value);
		current = current->next;
	}
	return a;
}

// создать список на основе массива списков
linkedlist create_list(linkedlist*& a) {
	linkedlist b;
	for (int i = 0; i < 10; ++i) {
		node* current = a[i].head;
		while (current != NULL) {
			b.push_back(current->value);
			current = current->next;
		}
	}

	return b;
}


int main() {
	setlocale(LC_ALL, "Russian");
	//int a = 10, b = 20, c = 30;
	//int* x = &a;
	//int* y = &b;
	//int* z = &c;
	//y = z;
	//cout << b;
	//// y и z указывают на с
	//// но b никуда не девается, чел


	// ТЕСТ PUSH_BACK
	/*//node x = { 1 };
	//cout << x.value << ' ' << x.next << '\n';
	linkedlist a;
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	a.push_back(1);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//node y = { 2 };
	a.push_back(2);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//node z = { 3 };
	a.push_back(3);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//cout << a.head->next->value << '\n';
	a.print();*/


	// ТЕСТ PUSH_FRONT
	/*//node x = {1};
	//cout << x.value << ' ' << x.next << '\n';
	linkedlist a;
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	a.push_front(1);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//node y = { 2 };
	a.push_front(2);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//node z = { 3 };
	a.push_front(3);
	//cout << a.tail->value << ' ' << a.tail->next << '\n';
	//cout << a.head->next->value << '\n';
	a.print();*/


	// ТЕСТ ERASE и FIND
	/*linkedlist a;
	a.push_front(1);
	cout << a.find(3)->value;
	a.push_front(2);
	a.push_front(3);
	a.print();
	node* p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
	a.erase(2);
	a.print();
	p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
	a.push_back(2);
	a.print();
	p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
	a.erase(2);
	a.print();
	p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
	a.push_front(2);
	a.print();
	p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
	a.erase(2);
	a.print();
	p = a.find(2);
	if (p != NULL)
		cout << p->value << '\n';
		*/

		// ТЕСТ fill и fill_auto
		/*cout << "Миха\n";
		linkedlist a, b;
		a.fill();
		cout << "Список а:\n";
		a.print();
		cout << "Список b:\n";
		b.fill_auto();*/

		// ТЕСТ clear
		/*linkedlist a;
		a.fill_auto();
		clear(a);
		cout << "OK\n";*/


		// ТЕСТ ИНДИВИДУАЛЬНОГО ЗАДАНИЯ
	/*
	7
	15
	20
	30
	49
	86
	97
	4
	*/
	/*linkedlist b;
	b.fill_auto();
	clear(b);
	b.fill();

	linkedlist* created_list = create_a(b);
	cout << "Массив, собранный по списку:\n";
	for (int i = 0; i < 10; ++i) {
		if (created_list[i].empty())
			continue;
		cout << i << "-элементы:\n";
		created_list[i].print();
	}

	cout << "Список, собранный по массиву:\n";
	b = create_list(created_list);
	b.print();*/

}