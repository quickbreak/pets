#ifndef __NODE__H
#define __NODE__H

#include "tree_base.h"


class node : public tree_base {
public:
	node(tree_base* p_head_object, string s_object_name = "Base_object");

};

#endif
