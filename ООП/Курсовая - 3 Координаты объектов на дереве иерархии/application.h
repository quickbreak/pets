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

};

#endif