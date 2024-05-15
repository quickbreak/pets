#ifndef __NODE_2__H
#define __NODE_2__H

#include "tree_base.h"

class node_2 final : public tree_base {
public:

	// node_2(tree_base* p_head_object, string s_object_name = "Base_object");

	using tree_base::tree_base;

	// ����� ������
	void signal(std::string&) const override;
	// ����� ����������
	void handler(const std::string) const override;
	// ���������� ��������� �� ������-����� ���� ������, ��� � � �������
	TYPE_SIGNAL get_signal_pointer() const override;
	// ���������� ��������� �� �������-����� ���� ������, ��� � � �������
	TYPE_HANDLER get_handler_pointer() const override;

};

#endif
