#ifndef __class_base__H
#define __class_base__H


#include<string>
#include<vector>


class class_base;

// для получения указателя на метод сигнала объекта
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(& signal_f)
// для получения указателя на метод обработчика объекта
#define HANDLER_D(handler_f)(TYPE_HANDLER)(& handler_f)

// тип указатель на метод сигнала объекта
typedef void (class_base::* TYPE_SIGNAL)(std::string&);
// тип указатель на метод обработчика объекта
typedef void (class_base::* TYPE_HANDLER)(std::string);




class class_base {

	struct type_connect // Структура, хранящая информацию о связи (одной)
	{
	public:
		TYPE_SIGNAL signal_pointer; // Указатель на метод сигнала
		class_base* target_object_pointer; // Указатель на целевой объект
		TYPE_HANDLER handler_pointer; // Указатель на метод обработчика

	};

	std::vector<type_connect*>connects; // список установленных связей объекта


	class_base* parent; // указатель на предка
	std::vector<class_base*>subordinate_objects; // список потомков

	std::string name; // имя объекта
	int readiness = 1; // готовность объекта. Разработчик решил, что по умолчанию объект будет включен


public:
	// конструктор
	class_base(class_base* parent = NULL, const std::string name = "Base_object");


	// метод установки связи
	void set_connect(TYPE_SIGNAL signal_pointer, class_base* target_object_pointer, TYPE_HANDLER handler_pointer);
	// метод выдачи сигнала и обработки соответствующих обработчиков
	void emit_signal(TYPE_SIGNAL, TYPE_HANDLER, std::string&);
	// возвращает значение поля готовность текущего объекта
	int get_my_readiness() const;
	// метод разрыва связи
	void remove_connect(TYPE_SIGNAL signal_pointer, class_base* target_object_pointer, TYPE_HANDLER handler_pointer);

	// приводит все объекты в состояние готовности
	void get_all_ready();
	// вывод информации о состоянии объектов системы
	void print_system(std::string space);
	// возвращает имя объекта
	const std::string get_my_name() const;
	// возвращает указатель на головной объект (на родителя)
	class_base* get_my_parent() const;

};

#endif
