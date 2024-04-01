#ifndef __APPLICATION__H
#define __APPLICATION__H

#include "tree_base.h"

class application : public tree_base {

public:
	application(tree_base* p_head_object, string s_object_name = "Base_object");
	void build_tree_objects(string filename_in);
	void build_tree_objects();
	void exec_app(string filename_out);
	void exec_app();
};

#endif