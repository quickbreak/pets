#include "tree_base.h"
#include <iostream>


tree_base::tree_base(tree_base* p_head_object, const string s_object_name) : 
	p_head_object(p_head_object), 
	s_object_name(s_object_name) 
{

	if (this->p_head_object != NULL) {
		this->p_head_object->subordinate_objects.push_back(this); // добавление предку нового потомка		
	}
}


const string tree_base::get_my_name() const {
	return this->s_object_name;
}


const tree_base* tree_base::get_my_parent() const {
	return this->p_head_object;
}


tree_base* tree_base::get_my_fav_child(const string fav_child_name) {
	// любимый у меня может быть только непосредственный потомок
	for (auto& child : this->subordinate_objects) {
		if (child->s_object_name == fav_child_name) {
			return child;
		}
	}
	return NULL;
}


bool tree_base::is_new_name(const string new_name) {

	return this->find_by_name(new_name) == NULL;

}


bool tree_base::change_name(const string new_name) {
	// если ещё ни у кого нет имени new_name, 
	// могу так назваться
	if (this->is_new_name(new_name)) {
		this->s_object_name = new_name;
		return true;
	}
	else return false;
}


void tree_base::dfs() const {
	string otstup = "";
	// посчитаем количество сдвигов (оно же количество предков)
	int cnt = 0;
	const tree_base* p_head = this;
	while (p_head->p_head_object != NULL) {
		p_head = p_head->p_head_object;
		++cnt;
	}
	// собираем сдвиг для текущего
	for (int i = 0; i < cnt; ++i)
		otstup += "    ";

	// выводим очередной объект
	cout << '\n' << otstup << this->get_my_name();

	// переходим к его потомкам
	for (auto& child : this->subordinate_objects) {
		child->dfs();
	}
}


void tree_base::set_readiness(const int num) {
	// если это отключение готовности,
	if (num == 0) {
		// то отключается этот объект
		this->readiness = num;
		// и отключаются все объекты ниже исходного
		for (auto& child : this->subordinate_objects) {
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


void tree_base::dfs_with_readiness() const {
	string otstup = "";
	// посчитаем количество сдвигов (оно же количество предков)
	int cnt = 0;
	const tree_base* p_head = this;
	while (p_head->p_head_object != NULL) {
		p_head = p_head->p_head_object;
		++cnt;
	}
	// собираем сдвиг для текущего
	for (int i = 0; i < cnt; ++i)
		otstup += "    ";

	// выводим очередной объект
	cout << '\n' << otstup << this->get_my_name() <<
		((this->readiness == 0) ? " is not ready" : " is ready");

	// переходим к его потомкам
	for (auto& child : this->subordinate_objects) {
		child->dfs_with_readiness();
	}
}


tree_base* tree_base::find_by_name_down(const string name) {

	// check myself
	if (this->s_object_name == name)
		return this;

	// check my children
	tree_base* found = NULL;
	for (auto& child : this->subordinate_objects) {
		found = child->find_by_name_down(name);
		// если нашли объект с таким именем
		if (found != NULL)
			return found;
	}

	// моё имя не совпало, и всех моих потомков зовут не так
	return NULL;
}


tree_base* tree_base::find_by_name(const string name) {

	// если метод вызван у корня, и это единственная вершина дерева
	if (this->p_head_object == NULL && this->subordinate_objects.size() == 0) {
		return ((this->s_object_name == name) ? this : NULL);
	}

	// если метод вызван у корня, и это не единственная вершина дерева,
	// то пусть работает штатно

	// find root
	tree_base* p_head = this;
	while (p_head->p_head_object != NULL) {
		p_head = p_head->p_head_object;

	}
	tree_base* root = p_head;

	// ищем на всём дереве
	return root->find_by_name_down(name);

}
