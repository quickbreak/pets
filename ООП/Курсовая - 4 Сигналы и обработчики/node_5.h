#ifndef __NODE_5__H
#define __NODE_5__H

#include "tree_base.h"

class node_5 final : public tree_base {
public:

	// node_5(tree_base* p_head_object, string s_object_name = "Base_object");

	using tree_base::tree_base;

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