#ifndef __APPLICATION__H
#define __APPLICATION__H

#include "tree_base.h"

class application final : public tree_base {

public:

	// application(tree_base* p_head_object, string s_object_name = "Base_object");

	using tree_base::tree_base;

	// построение дерева иерархии объектов
	void build_tree_objects();
	// запуск программы
	int exec_app();

	// метод сигнал
	void signal(std::string&) const override;
	// метод обработчик
	void handler(const std::string) const override;
	// возвращает указатель на сигнал-метод того класса, что и у объекта
	TYPE_SIGNAL get_signal_pointer() const override;
	// возвращает указатель на хэндлер-метод того класса, что и у объекта
	TYPE_HANDLER get_handler_pointer() const override;

};

#endif