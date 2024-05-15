#include "tree_base.h"


tree_base::tree_base(tree_base* p_head_object, const std::string s_object_name) : 
	p_head_object(p_head_object), 
	s_object_name(s_object_name) 
{

	if (this->p_head_object != NULL) {
		// добавить текущий объект в список непосредственных потомков его головного объекта (его родителя)
		this->p_head_object->subordinate_objects.push_back(this); 
	}
}


const std::string tree_base::get_my_name() const {

	return this->s_object_name;
}


tree_base* tree_base::get_my_parent() const {

	return this->p_head_object;
}


tree_base* tree_base::get_my_child(const std::string child_name) {

	for (auto& child : this->subordinate_objects) {
		if (child->s_object_name == child_name) {
			return child;
		}
	}

	return NULL;
}


bool tree_base::change_my_name(const std::string new_name) {
	// если у объекта есть sibling с именем new_name,
	// его нельзя назвать так же
	if (this->get_my_parent() != NULL) { // если у объекта есть родитель
		auto children = this->get_my_parent()->subordinate_objects;
		for (auto child : children) { // то надо проверить всех непосредственных потомков родителя
			if (child->s_object_name == new_name)
				return false;
		}
	}

	this->s_object_name = new_name;
	return true;
}


void tree_base::print_tree() const {
	std::string otstup = "";
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
	std::cout << '\n' << otstup << this->get_my_name();

	// переходим к его потомкам
	for (auto& child : this->subordinate_objects) {
		child->print_tree();
	}
}


void tree_base::print_tree_with_readiness() const {
	std::string otstup = "";
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
	std::cout << '\n' << otstup << this->get_my_name() <<
		((this->readiness == 0) ? " is not ready" : " is ready");

	// переходим к его потомкам
	for (auto& child : this->subordinate_objects) {
		child->print_tree_with_readiness();
	}
}


tree_base* tree_base::find_by_name_down(const std::string name) {

	// проверяем имя текущего объекта                                                  
	if (this->s_object_name == name)
		return this;

	// непосредственные потомки текущего
	tree_base* found = NULL;
	for (auto& child : this->subordinate_objects) {
		found = child->find_by_name_down(name); // вызов метода от каждого из непосредственных потомков
		// если нашли объект с таким именем
		if (found != NULL)
			return found;
	}

	// моё имя не совпало, и всех моих потомков зовут не так
	return NULL;
}


tree_base* tree_base::find_by_name(const std::string name) {

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


void tree_base::remove_my_child(const std::string childname) {

	auto& children = this->subordinate_objects; // список непосредственных потомков
	std::vector<tree_base*>::iterator it = children.end(); // итератор 
	for (int i = 0; i < children.size();++i) {
		if (children[i]->get_my_name() == childname) { 
			it = children.begin() + i;
			break;
		}
	}
	if (it != children.end()) // если есть непосредственный потомок с именем childname 
		// (гарантирована уникальность имён среди объектов с одинаковым головным объектом (родителем))
		children.erase(it); // то удаляем первый по порядку такой объект

}


bool tree_base::change_my_parent(tree_base* newparent) {
	// для корня родителя переопределить нельзя
	if (this->get_my_parent() == NULL)
		return false;
	// второго корня быть не может
	if (newparent == NULL)
		return false;
	// нельзя, чтобы новым родителем был потомок текущего.
	// Здесь проверяется наличие именно объекта newparent,
	// имя, как у newparent, спокойно может встречаться 
	// среди потомков текущего объекта
	std::vector<tree_base*>children;
	std::queue<tree_base*>q; // очередь
	tree_base* objptr = this;
	q.push(objptr); // кладём текущий объект 
	while (q.size() > 0) {
		objptr = q.front(); // переходим к очередному объекту
		if (objptr == newparent) // проверяем его самого
			return false;
		children = objptr->subordinate_objects;
		for (tree_base* child : children) // кладём в очередь его потомков
			q.push(child);

		q.pop();
	}
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


tree_base* tree_base::get_object(const std::string path) {
	// если координата - пустая строка
	if (path.size() == 0)
		return NULL;

	if (path == "/") { // корень дерева
		// поднимаемся до корня
		tree_base* objptr = this;
		while (objptr->p_head_object != NULL) {
			objptr = objptr->p_head_object;

		}
		return objptr;
	}
	if (path == ".") // текущий объект
		return this;
	if (path[0] + path[1] == '/' + '/') { // объект по уникальному имени от корневого
		std::string name = "";
		for (int i = 2; i < path.size(); ++i) {
			name += path[i];
		}

		// поднимаемся до корня дерева
		tree_base* objptr = this;
		while (objptr->p_head_object != NULL) {
			objptr = objptr->p_head_object;

		}

		// проверяем уникальность имени 
		std::vector<tree_base*>children, candidates;
		std::queue<tree_base*>q; // очередь
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
		std::string name = "";
		for (int i = 1; i < path.size(); ++i) {
			name += path[i];
		}

		// проверяем уникальность имени
		tree_base* objptr;
		std::vector<tree_base*>children, candidates;
		std::queue<tree_base*>q; // очередь
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
		std::string name = "";
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
	else { // если никакой другой сценарий не прошёл, это относительная координата от текущего объекта
		tree_base* objptr = this;
		std::string name = "";
		int i = 0;
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


void tree_base::set_connect(TYPE_SIGNAL signal_pointer, 
							tree_base* target_object_pointer, 
							TYPE_HANDLER handler_pointer) 
{
	// Если такая связь уже есть, второй раз не добавляется
	for (int i = 0; i < this->connects.size(); ++i) {
		if (this->connects[i]->signal_pointer == signal_pointer &&
			this->connects[i]->target_object_pointer == target_object_pointer &&
			this->connects[i]->handler_pointer == handler_pointer)
		{
			return;
		}
	}

	type_connect* new_connect = new type_connect{ signal_pointer, target_object_pointer, handler_pointer };

	this->connects.push_back(new_connect); // добавление новой связи
}


void tree_base::remove_connect(TYPE_SIGNAL signal_pointer, tree_base* target_object_pointer, TYPE_HANDLER handler_pointer)
{
	// создаётся пример связи, которую надо удалить из списка связей
	type_connect* value = new type_connect{ signal_pointer, target_object_pointer, handler_pointer };
	// все связи, совпадающие с value, перемещаются в конец списка.
	// Возвращается указатель на крайний справа не совпадающий с value элемент
	auto it_start = remove_if(this->connects.begin(), this->connects.end(), [value](type_connect* connect) {
		return connect->signal_pointer == value->signal_pointer &&
			connect->handler_pointer == value->handler_pointer &&
			connect->target_object_pointer == value->target_object_pointer;
		});
	// лямбда захватывает значение [value], потому что иначе она не видит локальные переменные
	
	// все связи, совпавшие с value, удаляются из списка
	this->connects.erase(it_start, this->connects.end());

	/*auto index = this->connects.end();   // УДАЛЯЕТ ТОЛЬКО ПЕРВОЕ ВХОЖДЕНИЕ (в этой работе исключено повторное, ну и ладно)
	for (int i = 0; i < this->connects.size(); ++i)
	{
		auto connect = connects[i];
		if (connect->signal_pointer == signal_pointer &&
			connect->handler_pointer == handler_pointer &&
			connect->target_object_pointer == target_object_pointer)
		{
			index = this->connects.begin() + i;
			break;
		}
	}
	if (index != this->connects.end())
		this->connects.erase(index);*/
}


int tree_base::get_my_readiness() const {
	return this->readiness;
}


void tree_base::emit_signal(TYPE_SIGNAL signal_pointer, std::string& message)
{
	if (this->get_my_readiness() == 0) // если объект отключен
		return;

	TYPE_HANDLER handler_pointer;
	tree_base* object_pointer;

	(this->*signal_pointer)(message); // вызов метода сигнала

	// проход по всем обработчикам
	for (int i = 0; i < this->connects.size(); ++i) 
	{
		if (this->connects[i]->signal_pointer == signal_pointer) // определение допустимого обработчика
		{
			handler_pointer = this->connects[i]->handler_pointer;
			object_pointer = this->connects[i]->target_object_pointer;

			if (object_pointer->get_my_readiness() != 0) // если целевой объект готов
				(object_pointer->*handler_pointer)(message); // вызов метода обработчика
		}
	}

}


std::string tree_base::get_my_absolute_path() const
{
	const tree_base* object_pointer = this;
	if (object_pointer->p_head_object == NULL) // если это корень
		return "/";
	std::string absolute_path = "";
	while (object_pointer->p_head_object != NULL)  // подъём до корня, сбор всех встречающихся объектов в absolute_path
	{
		absolute_path = "/" + object_pointer->s_object_name + absolute_path;
		object_pointer = object_pointer->p_head_object;
	}

	return absolute_path;
}


void tree_base::set_my_readiness(const int num) {
	// если это отключение готовности,
	if (num == 0) {
		// то отключается этот объект
		this->readiness = num;
		// и отключаются все объекты ниже исходного
		for (auto& child : this->subordinate_objects) {
			child->set_my_readiness(num);
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
		// наконец, если все готовы,
		if (readiness_flag)
			// устанавливается значение готовности текущего объекта
			this->readiness = num;
	}
}


std::vector<tree_base*> tree_base::get_my_subordinate_objects() const {
	return this->subordinate_objects;
}
