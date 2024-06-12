#ifndef __CLASS_SYSTEM__H
#define __CLASS_SYSTEM__H


#include "class_reading.h"
#include "class_info.h"
#include "class_road.h"
#include "class_remote_control.h"
#include "class_light.h"


class class_system final : public class_base
{
	class_reading* reader; // объект для ввода данных
	class_info* printer; // объект для вывода данных
	class_road* road; // объект дорога, которому подчинены объекты машины
	class_remote_control* control; // объект для управления светофором
	class_light* light; // объект светофор


	// обработка поступающих (в exec_app) команд
	void commands_handler(std::string);
	// моделирует поведение объектов один такт согласно сценарию
	void make_all_move();

public:

	class_system(class_base* parent = NULL, const std::string name = "system");

	// построение системы
	void build_system();
	// запуск программы
	int exec_app();

	// бесполезная
	void signal_to_printer(const std::string&);

};

#endif