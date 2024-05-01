#include "tree_base.h"
#include <iostream>
#include <queue>


tree_base::tree_base(tree_base* p_head_object, const string s_object_name) : 
	p_head_object(p_head_object), 
	s_object_name(s_object_name) 
{

	if (this->p_head_object != NULL) {
		// добавить текущий объект в список непосредственных потомков его головного объекта (его родителя)
		this->p_head_object->subordinate_objects.push_back(this); 
	}
}


const string tree_base::get_my_name() const {

	return this->s_object_name;
}


tree_base* tree_base::get_my_parent() const {

	return this->p_head_object;
}


tree_base* tree_base::get_my_child(const string child_name) {

	for (auto& child : this->subordinate_objects) {
		if (child->s_object_name == child_name) {
			return child;
		}
	}
	return NULL;
}


bool tree_base::is_new_name(const string new_name) {

	return (this->find_by_name(new_name) == NULL);
}


bool tree_base::change_my_name(const string new_name) {
	// если имя new_name не занято, 
	// могу так назваться
	if (this->is_new_name(new_name)) {
		this->s_object_name = new_name;
		return true;
	}
	else return false;
}


void tree_base::print_tree() const {
	string otstup = "";
	// нужно посчитать количество сдвигов (оно же количество предков)
	int cnt = 0;
	const tree_base* p_head = this;
	// для этого поднимемся вверх по дереву до корня
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
		child->print_tree();
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


void tree_base::print_tree_with_readiness() const {
	string otstup = "";
	// нужно посчитать количество сдвигов (оно же количество предков)
	int cnt = 0;
	const tree_base* p_head = this;
	// для этого поднимемся вверх по дереву до корня
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
		child->print_tree_with_readiness();
	}
}


tree_base* tree_base::find_by_name_down(const string name) {

	// проверяем имя текущего объекта                                                  
	if (this->s_object_name == name)
		return this;

	// непосредственные потомки текущего
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

	// проверяем имя текущего объекта    
	if (this->get_my_name() == name)
		return this;

	// получаем указатель на корень дерева
	tree_base* objptr = this;
	while (objptr->p_head_object != NULL) {
		objptr = objptr->p_head_object;

	}
	tree_base* root = objptr;

	// ищем на всём дереве
	return root->find_by_name_down(name);

}


void tree_base::remove_my_child(const string childname) {

	auto& children = this->subordinate_objects; // список непосредственных потомков
	vector<tree_base*>::iterator it = children.end(); // итератор 
	for (int i = 0; i < children.size();++i) {
		if (children[i]->get_my_name() == childname) { 
			it = children.begin() + i;
			break;
		}
	}
	if (it != children.end()) // если есть непосредственные потомки с именем childname
		children.erase(it); // то удаляем первый по порядку такой объект

}


bool tree_base::change_my_parent(tree_base* newparent) {
	// для корня родителя переопределить нельзя
	if (this->get_my_parent() == NULL)
		return false;
	// второго корня быть не может
	if (newparent == NULL)
		return false;
	// нельзя, чтобы новым родителем был потомок текущего
	if (this->find_by_name_down(newparent->get_my_name()) != NULL)
		return false;
	// нельзя прикрепиться к newparent, если у него есть НЕПОСРЕДСТВЕННЫЙ потомок с таким же именем, как у текущего 
	if (newparent->get_my_child(this->get_my_name()))
		return false;

	// если все условия соблюдены,
	// удаляем себя из списка непосредственных потомков текущего родителя
	this->get_my_parent()->remove_my_child(this->get_my_name());
	// присоединяемся к новому родителю (со всем нашим поддеревом)
	newparent->subordinate_objects.push_back(this);
	this->p_head_object = newparent;
	// выполнено успешно
	return true;
}


tree_base* tree_base::get_object(const string path) {
	// если координата - пустая строка
	if (path.size() == 0)
		return NULL;

	if (path == "/") { // корень дерева
		// find root
		tree_base* objptr = this;
		while (objptr->p_head_object != NULL) {
			objptr = objptr->p_head_object;

		}
		return objptr;
	}
	if (path == ".") // текущий объект
		return this;
	if (path[0] + path[1] == '/' + '/') { // объект по уникальному имени от корневого
		string name = "";
		for (int i = 2; i < path.size(); ++i) {
			name += path[i];
		}

		// поднимаемся до корня дерева
		tree_base* objptr = this;
		while (objptr->p_head_object != NULL) {
			objptr = objptr->p_head_object;

		}

		// проверяем уникальность (bfs)
		vector<tree_base*>children, candidates;
		queue<tree_base*>q; // очередь
		q.push(objptr); // кладём корень 
		while (q.size() > 0) {
			objptr = q.front(); // переходим к очередному объекту
			if (objptr->get_my_name() == name) // проверяем его самого
				candidates.push_back(objptr);
			children = objptr->subordinate_objects;
			for (tree_base* child : children) // кладём в очередь его потомков
				q.push(child);

			q.pop();
		}
		if (candidates.size() == 1) // если имя уникально
			return candidates[0];
		else // если имени нет ни у кого или оно не уникально
			return NULL;
	}
	if (path[0] == '.') { // объект по уникальному имени от текущего
		string name = "";
		for (int i = 1; i < path.size(); ++i) {
			name += path[i];
		}

		// проверяем уникальность (bfs)
		tree_base* objptr;
		vector<tree_base*>children, candidates;
		queue<tree_base*>q; // очередь
		q.push(this); // кладём текущий объект
		while (q.size() > 0) {
			objptr = q.front(); // переходим к очередному объекту
			if (objptr->get_my_name() == name) // проверяем его самого
				candidates.push_back(objptr);
			children = objptr->subordinate_objects;
			for (tree_base* child : children) // кладём в очередь его потомков
				q.push(child);

			q.pop();
		}
		if (candidates.size() == 1) // если имя уникально
			return candidates[0];
		else // если имени нет ни у кого или оно не уникально
			return NULL;
	}
	if (path[0] == '/') { // абсолютная координата от корня
		// поднимаемся до корня
		tree_base* objptr = this;
		while (objptr->p_head_object != NULL) {
			objptr = objptr->p_head_object;

		}
		
		int i = 1;
		string name = "";
		// пошли по path от корня
		while (i < path.size()) {
			name = "";
			while (i < path.size() && path[i] != '/') { // собрали имя очередного объекта на пути
				name += path[i];
				++i;
			}
			++i;
			objptr = objptr->get_my_child(name);
			if (objptr == NULL) // путь path некорректный, не смогли найти очередной объект на пути
				return NULL;
		}
		// если смогли найти, возвращаем
		return objptr;
	}
	else { // если ничего не помогло, это относительная координата от текущего объекта
		tree_base* objptr = this;
		int i = 0;
		string name = "";
		// пошли по path от текущего
		while (i < path.size()) {
			name = "";
			while (i < path.size() && path[i] != '/') { // собрали имя очередного объекта на пути
				name += path[i];
				++i;
			}
			++i;
			objptr = objptr->get_my_child(name);
			if (objptr == NULL) // путь path некорректный, не смогли найти очередной объект на пути
				return NULL;
		}
		// если смогли найти, возвращаем
		return objptr;
	}
}
