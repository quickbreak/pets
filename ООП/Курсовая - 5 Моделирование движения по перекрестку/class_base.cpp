#include "class_base.h"
#include "class_info.h"
#include "class_system.h"


class_base::class_base(class_base* parent, const std::string name) : 
	parent(parent), 
	name(name) 
{
	if (this->parent != NULL) {
		// добавить текущий объект в список непосредственных потомков его головного объекта (его родителя)
		this->parent->subordinate_objects.push_back(this); 
	}
}


const std::string class_base::get_my_name() const {

	return this->name;
}


class_base* class_base::get_my_parent() const {

	return this->parent;
}

void class_base::set_connect(TYPE_SIGNAL signal_pointer, 
							class_base* target_object_pointer, 
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


void class_base::remove_connect(TYPE_SIGNAL signal_pointer, class_base* target_object_pointer, TYPE_HANDLER handler_pointer)
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


void class_base::emit_signal(TYPE_SIGNAL signal_pointer, TYPE_HANDLER handler_pointer, std::string& message)
{
	if (this->readiness == 0) // если объект отключен
		return;

	class_base* object_pointer;

	if (signal_pointer != NULL)
		(this->*signal_pointer)(message); // вызов метода сигнала

	// проход по всем связям
	for (int i = 0; i < this->connects.size(); ++i) 
	{
		if (this->connects[i]->signal_pointer == signal_pointer) // если нужный сигнал
		{
			if (this->connects[i]->handler_pointer == handler_pointer) // и нужный обработчик
			{
				object_pointer = this->connects[i]->target_object_pointer;

				if (object_pointer->readiness != 0) // если целевой объект готов
					if (handler_pointer != NULL)
						(object_pointer->*handler_pointer)(message); // вызов метода обработчика
			}
		}
	}

}


int class_base::get_my_readiness() const {
	return this->readiness;
}


void class_base::get_all_ready()
{
	// должен запускаться от корня

	this->readiness = 1;
	for (auto child : this->subordinate_objects)
	{
		child->get_all_ready();
	}
}


void class_base::print_system(std::string space)
{
	// вывод очередного объекта
	std::string message =  "\n" + space + this->name +
		((this->readiness == 0) ? " is not ready" : " is ready");


	// подъём до корня
	class_base* p_obj = this;
	while (p_obj->parent != NULL)
	{
		p_obj = p_obj->parent;
	}
	p_obj->emit_signal(SIGNAL_D(class_system::signal_to_printer), HANDLER_D(class_info::print_message), message);

	// переход к его потомкам
	for (auto child : this->subordinate_objects) {
		child->print_system(space + "    ");
	}
}
