#include "application.h"
#include "node_2.h"
#include "node_3.h"
#include "node_4.h"
#include "node_5.h"
#include "node_6.h"


//application::application(tree_base * p_head_object, const std::string s_object_name): tree_base(p_head_object,s_object_name){};


void application::signal(std::string& message) const
{
	message += " (class: 1)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void application::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL application::get_signal_pointer() const
{
	return SIGNAL_D(application::signal);
}


TYPE_HANDLER application::get_handler_pointer() const
{
	return HANDLER_D(application::handler);
}


void application::build_tree_objects() 
{
	std::string path, childname; // путь, имя нового объекта
	// чтение имени корня
	std::cin >> childname;
	this->change_my_name(childname);

	int class_number; // номер класса очередной вершины [2..6]
	tree_base* node; // очередная вершина
	while (true) {
		std::cin >> path;
		if (path == "endtree") // конец дерева
			break;
		std::cin >> childname >> class_number;

		
		tree_base* parent = this->get_object(path); // ищется родитель

		// проверка, нет ли уже у родителя потомка с нашим именем
		tree_base* found = parent->get_my_child(childname); 
		if (!found) { // если имя уникально
			// то создаётся новая вершина указанного класса с таким именем
			if (class_number == 2) {
				node = new node_2(parent, childname);
			}
			else if (class_number == 3) {
				node = new node_3(parent, childname);
			}
			else if (class_number == 4) {
				node = new node_4(parent, childname);
			}
			else if (class_number == 5) {
				node = new node_5(parent, childname);
			}
			else if (class_number == 6) {
				node = new node_6(parent, childname);
			}
		}
		// иначе объект не создаётся
		
	}

	std::cout << "Object tree";
	this->print_tree();


	while (true)
	{
		std::cin >> path;
		if (path == "end_of_connections")
		{
			break;
		}

		auto object_from = this->get_object(path);
		
		std::cin >> path;
		auto object_to = this->get_object(path);

		object_from->set_connect(object_from->get_signal_pointer(), object_to, object_from->get_handler_pointer());
	}
}


int application::exec_app() 
{
	// подъём до корня
	tree_base* objptr = this;

	// все объекты приводятся в состояние готовности 
	std::vector<tree_base*>children; // список детей
	std::queue<tree_base*>q; // очередь
	q.push(objptr); // в очередь кладётся корень 
	while (q.size() > 0) {
		objptr = q.front(); // переход к очередному объекту
		objptr->set_my_readiness(1);
		children = objptr->get_my_subordinate_objects();
		for (tree_base* child : children) // в очередь кладутся его дети
			q.push(child);

		q.pop();
	}


	std::string command, path, message;
	while (true) 
	{
		std::cin >> command;
		if (command == "END") 
		{
			break;
		}
		else if (command == "SET_CONDITION")
		{
			std::cin >> path;
			int code; std::cin >> code;
			tree_base* object = this->get_object(path);
			if (object == NULL)
			{
				std::cout << "\nObject " << path << " not found";
				continue;
			}
			object->set_my_readiness(code);
		}
		else if (command == "EMIT")
		{
			std::cin >> path;
			getline(std::cin, message);
			tree_base* object_from = this->get_object(path);
			if (object_from == NULL)
			{
				std::cout << "\nObject " << path << " not found";
				continue;
			}
			object_from->emit_signal(object_from->get_signal_pointer(), message);
		}
		else if (command == "SET_CONNECT")
		{
			std::cin >> path;
			tree_base* object_from = this->get_object(path);
			if (object_from == NULL)
			{
				std::cout << "\nObject " << path << " not found";
				continue;
			}
			std::cin >> path;
			tree_base* object_to = this->get_object(path);
			if (object_to == NULL)
			{
				std::cout << "\nHandler object " << path << " not found";
				continue;
			}
			object_from->set_connect(object_from->get_signal_pointer(), object_to, object_from->get_handler_pointer());
		}
		else if (command == "DELETE_CONNECT")
		{
			std::cin >> path;
			tree_base* object_from = this->get_object(path);
			if (object_from == NULL)
			{
				std::cout << "\nObject " << path << " not found";
				continue;
			}
			std::cin >> path;
			tree_base* object_to = this->get_object(path);
			if (object_to == NULL)
			{
				std::cout << "\nHandler object " << path << " not found";
				continue;
			}
			object_from->remove_connect(object_from->get_signal_pointer(), object_to, object_from->get_handler_pointer());
		}
		
	}

	return 0;
}
