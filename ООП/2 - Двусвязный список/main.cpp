#include <iostream>
#include <cassert>
#include <clocale>

using namespace std;


const int malo = -int(1e9);
const string smallstring = "";


struct oblastnode {
public:
	string oblastname = smallstring;
	oblastnode* next = NULL;
	oblastnode* previous = NULL;

	oblastnode() = default;
	oblastnode(string oblastname) :
		oblastname(oblastname),
		next(NULL),
		previous(NULL)
	{};
};


struct oblast {
public:
	oblastnode* headoblast;
	oblastnode* tailoblast;

	oblast() : headoblast(NULL), tailoblast(NULL) {};

	// список пуст?
	bool empty() const {
		return headoblast == NULL;
	}

	// добавить в конец узел с информационной часть, переданной парметрами
	void push_back(const string oblastname) {
		oblastnode* x = new oblastnode(oblastname);
		// если это будет первый узел (список пуст)
		if (this->empty()) {
			headoblast = x;
			tailoblast = x;
			return;
		}
		// если есть хотя бы один узел
		tailoblast->next = x;
		tailoblast = x;
	}

	// добавить в начало узел с информационной часть, переданной парметрами
	void push_front(const string oblastname) {
		oblastnode* x = new oblastnode(oblastname);
		// если это будет первый узел (список пуст)
		if (this->empty()) {
			headoblast = x;
			tailoblast = x;
			return;
		}
		// если есть хотя бы один узел
		x->next = headoblast;
		headoblast = x;
	}

	// удалить последний узел
	void pop_back() {
		// если удалять нечего (список пуст)
		if (this->empty()) {
			return;
		}
		// если есть хотя бы один узел
		oblastnode* last = tailoblast;
		tailoblast = tailoblast->previous;
		// узел был единственный
		if (tailoblast == NULL)
			headoblast = NULL;
		delete last;
	}

	// удалить первый узел
	void pop_front() {
		// если удалять нечего (список пуст)
		if (this->empty()) {
			return;
		}
		// если есть хотя бы один узел
		oblastnode* first = headoblast;
		headoblast = headoblast->next;
		// узел был единственный
		if (headoblast == NULL)
			tailoblast = NULL;
		delete first;
	}

	// вывести элементы списка слева направо
	void print_direct() const {
		if (this->empty())
			return;
		oblastnode* current = headoblast;
		while (current != NULL) {
			cout << current->oblastname << ' ';
			current = current->next;
		}
		cout << '\n';
	}

	// вывести элементы списка справа налево
	void print_reverse() const {
		if (this->empty())
			return;
		oblastnode* current = tailoblast;
		while (current != NULL) {
			cout << current->oblastname << ' ';
			current = current->previous;
		}
		cout << '\n';
	};

	// поиск элемента по id, первого по порядку слева направо
	oblastnode* find_first(const string oblastname) const {
		if (this->empty())
			return NULL;
		oblastnode* current = headoblast;
		while (current != NULL) {
			if (current->oblastname == oblastname) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	};

	// удаление узла по значению, если такой есть, первого по порядку
	void erase(const string oblastname) {
		if (this->empty())
			return;

		oblastnode* current = headoblast;
		while (current != NULL) {
			// если нашли нужный узел
			if (current->oblastname == oblastname) {
				// если это первый узел
				if (current == headoblast) {
					// то обновляем голову (и забываем про подлежащий удалению узел)
					headoblast = current->next;
					// если он же - последний
					if (current == tailoblast)
						// то обновляем хвост (и забываем про подлежащий удалению узел)
						tailoblast = NULL;
				}
				else {
					// список забывает про этот узел
					current->previous->next = current->next;
				}
				// освобождаем память
				delete current;
				return;
			}
			// иначе переходим к следующему узлу
			current = current->next;
		}
	};

	// часть списка от узла с номеров startindex до конца перенести в начало списка
	void move(int startindex) {
		if (startindex < 1) {
			cout << "INCORRECT STARTINDEX FOR MOVE\n";
			return;
		}

		if (this->empty())
			return;
		// если это отрезок от головы (до конца) или единственный узел
		// то они уже стоят в начале
		if (startindex == 1) {
			return;
		}
		oblastnode* current = headoblast;
		int index = 0;
		while (current != NULL && ++index < startindex) {
			current = current->next;
		}
		if (current == NULL) {
			cout << "INCORRECT STARTINDEX FOR MOVE\n";
			return;
		}
		// в идеальном мире
		current->previous->next = NULL;
		tailoblast->next = headoblast;
		tailoblast = current->previous;
		headoblast = current;

	}

};


struct node {
public:
	string id = smallstring; // инвентарный номер
	oblast* sphere = NULL; // область знаний
	string author = smallstring; // автор
	string name = smallstring; // название
	int year = -1; // год издания

	node* next = NULL;
	node* previous = NULL;

	node() = default;
	node(string id, oblast* sphere, string author, string name, int year) :
		id(id),
		sphere(sphere),
		author(author),
		name(name),
		year(year)
	{};
};


struct doublylinkedlist{
public:
	node* head;
	node* tail;
	doublylinkedlist() : head(NULL), tail(NULL) {};

	// список пуст?
	bool empty() const {
		return head == NULL;
	}

	// добавить в конец узел с информационной часть, переданной парметрами
	void push_back(const string id, oblast* sphere, const string author, const string name, int year) {
		node* x = new node(id, sphere, author, name, year);
		// если это будет первый узел (список пуст)
		if (this->empty()) {
			head = x;
			tail = x;
			return;
		}
		// если есть хотя бы один узел
		tail->next = x;
		tail = x;
	}

	// добавить в начало узел с информационной часть, переданной парметрами
	void push_front(const string id, oblast* sphere, const string author, const string name, int year) {
		node* x = new node(id, sphere, author, name, year);
		// если это будет первый узел (список пуст)
		if (this->empty()) {
			head = x;
			tail = x;
			return;
		}
		// если есть хотя бы один узел
		x->next = head;
		head = x;
	}

	// удалить последний узел
	void pop_back() {
		// если удалять нечего (список пуст)
		if (this->empty()) {
			return;
		}
		// если есть хотя бы один узел
		node* last = tail;
		tail = tail->previous;
		// узел был единственный
		if (tail == NULL)
			head = NULL;
		delete last;
	}

	// удалить первый узел
	void pop_front() {
		// если удалять нечего (список пуст)
		if (this->empty()) {
			return;
		}
		// если есть хотя бы один узел
		node* first = head;
		head = head->next;
		// узел был единственный
		if (head == NULL)
			tail = NULL;
		delete first;
	}

	// вывести элементы списка слева направо
	void print_direct() const {
		if (this->empty())
			return;
		node* current = head;
		while (current != NULL) {
			cout << current->id << ' ';
			current = current->next;
		}
		cout << '\n';
	}

	// вывести элементы списка справа налево
	void print_reverse() const {
		if (this->empty())
			return;
		node* current = tail;
		while (current != NULL) {
			cout << current->id << ' ';
			current = current->previous;
		}
		cout << '\n';
	};

	// поиск элемента по id, первого по порядку слева направо
	node* find_first(const string id) const {
		if (this->empty())
			return NULL;
		node* current = head;
		while (current != NULL) {
			if (current->id == id) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	};

	// удаление узла по значению, если такой есть, первого по порядку
	void erase(const string id) {
		if (this->empty())
			return;

		node* current = head;
		while (current != NULL) {
			// если нашли нужный узел
			if (current->id == id) {
				// если это первый узел
				if (current == head) {
					// то обновляем голову (и забываем про подлежащий удалению узел)
					head = current->next;
					// если он же - последний
					if (current == tail)
						// то обновляем хвост (и забываем про подлежащий удалению узел)
						tail = NULL;
				}
				else {
					// список забывает про этот узел
					current->previous->next = current->next;
				}
				// освобождаем память
				delete current;
				return;
			}
			// иначе переходим к следующему узлу
			current = current->next;
		}
	};

	// удаление книг с автором author и годом выпуска > year
	void erase_all(const string author, int year) {
		if (this->empty())
			return;

		node* current = head;
		while (current != NULL) {
			// если нашли нужный узел
			if (current->author == author && current->year == year) {
				// если это первый узел
				if (current == head) {
					// то обновляем голову (и забываем про подлежащий удалению узел)
					head = current->next;
					// если он же - последний
					if (current == tail)
						// то обновляем хвост (и забываем про подлежащий удалению узел)
						tail = NULL;
				}
				else {
					// список забывает про этот узел
					current->previous->next = current->next;
				}
				// освобождаем память
				delete current;
			}
			// переходим к следующему узлу
			current = current->next;
		}
	};
	 
	// часть списка от узла с номеров startindex до конца перенести в начало списка
	void move(int startindex) {
		if (startindex < 1) {
			cout << "INCORRECT STARTINDEX FOR MOVE\n";
			return;
		}

		if (this->empty())
			return;
		// если это отрезок от головы (до конца) или единственный узел
		// то они уже стоят в начале
		if (startindex == 1) {
			return;
		}
		node* current = head;
		int index = 0;
		while (current != NULL && ++index < startindex) {
			current = current->next;
		}
		if (current == NULL) {
			cout << "INCORRECT STARTINDEX FOR MOVE\n";
			return;
		}
		// в идеальном мире
		current->previous->next = NULL;
		tail->next = head;
		tail = current->previous;
		head = current;

	}

};


int main() {
	// setlocale(LC_ALL, "Russian");

	oblast spheres_1;
	spheres_1.push_back("chemistry");
	spheres_1.push_back("physics");
	oblast spheres_2;
	spheres_2.push_back("PE");
	spheres_2.push_back("Math");

	doublylinkedlist spisok;
	spisok.push_back("Miha228", &spheres_1, "Doil", "A book", 2025);
	spisok.push_back("Miha322", &spheres_2, "Connon", "The book", 2026);
	cout << spisok.find_first("Miha322")->sphere->find_first("PE")->oblastname;
}