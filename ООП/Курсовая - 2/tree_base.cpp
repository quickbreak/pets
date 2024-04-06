#include "tree_base.h"
#include <iostream>
#include <fstream>
#include <queue>


tree_base::tree_base(tree_base* p_head_object, const string s_object_name) {
	this->p_head_object = p_head_object; // указатель на предка
	this->s_object_name = s_object_name; // имя потомка
	if (this->p_head_object != NULL) {
		this->p_head_object->subordinate_objects.push_back(this); // добавление предку нового потомка		
	}
}

void tree_base::print() const {
	cout << this->s_object_name; // назовём праотца
	const tree_base* parent = this;
	int n;
	while (parent->subordinate_objects.size() > 0) { // перечисляем непосредственных потомков текущего предка
		cout << '\n';
		cout << parent->s_object_name; // называем предка
		n = parent->subordinate_objects.size();
		for (int i = 0; i < n; ++i) {
			cout << "  " << parent->
				subordinate_objects[i]->
				s_object_name; // и его непосредственных потомков
		}
		// переходим к следующему колену
		parent = parent->subordinate_objects[n - 1];

	}
}

//string tree_base::print(string filename_out) const{
//
//	string answer = "";
//	//cout << this->s_object_name; // назовём праотца
//	answer += this->s_object_name;
//	const tree_base* parent = this;
//	int n;
//	while (parent->subordinate_objects.size() > 0) { // перечисляем непосредственных потомков текущего предка
//		//cout << '\n';
//		answer += "\n";
//		//cout << parent->s_object_name; // называем предка
//		answer += parent->s_object_name;
//		n = parent->subordinate_objects.size();
//		for (int i = 0; i < n; ++i) {
//			//cout << "  " << parent->subordinate_objects[i]->s_object_name; // и его непосредственных потомков
//			answer += "  " + parent->subordinate_objects[i]->s_object_name;
//		}
//		// переходим к следующему колену
//		parent = parent->subordinate_objects[n - 1];
//
//	}
//
//	ifstream file(filename_out);
//	string had_to_get;
//	string s = "";
//	getline(file, s, '\n');
//	while (s!="eof") {
//		had_to_get += s + "\n";
//		getline(file, s, '\n');
//	}
//	file.close();
//	string happily = "Test_" + to_string(filename_out[4] - 48) + "_Passed!\n";
//	string sadly = "Test_" + to_string(filename_out[4] - 48) + "_Failed.\n";
//	if (answer + "\n" == had_to_get)
//		++successfull_tests_cnt;
//	return (answer + "\n" == had_to_get) ? happily : sadly;
//}

string tree_base::get_my_name() const {
	return this->s_object_name;
}

tree_base* tree_base::get_my_parent() const {
	return this->p_head_object;
}

tree_base* tree_base::get_my_fav_child(const string fav_child_name) const {
	// любимый у меня может быть только непосредственнный потомок
	for (auto child : this->subordinate_objects) {
		if (child->s_object_name == fav_child_name) {
			return child;
		}
	}
	return NULL;
}

bool tree_base::is_new_name(const string new_name) const {
	const tree_base* me = this;
	// есть ли у меня уже потомок с именем new_name?
	for (auto sibling : me->subordinate_objects) {
		if (sibling->s_object_name == new_name) {
			return false;
		}
	}
	return true;

}

bool tree_base::change_name(const string new_name) {
	tree_base* parent = this->p_head_object;
	// хочу сменить имя, но будет не прикольно,
	// если у моих siblings есть такое имя:
	// нас же родители путать будут...
	if (parent == NULL || parent->is_new_name(new_name)) {
		this->s_object_name = new_name;
		return true;
	}
	else return false;
}

void tree_base::dfs(const string otstup) const {
	// вывод имени корня
	cout << '\n' << otstup << this->get_my_name();
	// dfs: вывод имени каждой вершины
	for (auto child : this->subordinate_objects) {
		child->dfs(otstup + "    ");
	}
}

void tree_base::set_readiness(const int num) {
	// если это отключение готовности,
	if (num == 0) {
		// то отключается этот объект
		this->readiness = num;
		// и оключаются все объекты ниже исходного
		for (auto child : this->subordinate_objects) {
			child->set_readiness(num);
		}
	}
	else { // если запрос на включение
		// надо проверить, готовы ли все объекты вверх по иерархии
		bool readiness_flag = true;
		tree_base* p_head = this;
		while (p_head->p_head_object != NULL) {
			p_head = p_head->p_head_object;
			// если хоть один не готов
			if (p_head->readiness == 0) {
				// во включении исходного отказано
				readiness_flag = false;
				break;

			}
		}
		// если все готовы
		if (readiness_flag)
			// то и я с ними
			this->readiness = num;
	}
}

void tree_base::dfs_with_readiness(const string otstup) const {
	// вывод готовности корня
	cout << '\n' << otstup << this->get_my_name();
	if (this->readiness != 0)
		cout << " is ready";
	else cout << " is not ready";

	// dfs: вывод готовности каждой вершины
	for (auto child : this->subordinate_objects) {
		child->dfs_with_readiness(otstup + "    ");
	}
}

tree_base* tree_base::find_by_name_down(const string name) {

	// check myself
	if (this->s_object_name == name)
		return this;

	// check my children
	for (auto child : this->subordinate_objects) {
		tree_base* found = child->find_by_name_down(name);
		// если нашли объект с таким именем
		if (found != NULL)
			return found;
	}

	// моё имя не совпало, и всех моих потомков зовут не так
	return NULL;
}

tree_base* tree_base::find_by_name(const string name) {

	// если метод вызван у корня, и это единственнная вершина дерева
	if (this->p_head_object == NULL && this->subordinate_objects.size() == 0) {
		return ((this->s_object_name == name) ? this : NULL);
	}

	// если метод вызван у корня, и это не единственнная вершина дерева,
	// то пусть работает штатно

	// find root
	tree_base* p_head = this;
	while (p_head->p_head_object != NULL) {
		p_head = p_head->p_head_object;

	}
	tree_base* root = p_head;

	// ищем на всём дереве
	return root->find_by_name_down(name);

	//// ну bfs, а что, а что?
	//queue<tree_base*>q;
	//q.push(this);
	//while (!q.empty()) {
	//	tree_base* parent = q.front();
	//	if (parent->s_object_name == name) {
	//		return parent;
	//	}
	//	q.pop();

	//	for (tree_base* child : parent->subordinate_objects) {
	//		q.push(child);
	//	}
	//}
	//// не нашёлся на всём дереве
	//return NULL;

}
