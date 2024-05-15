#ifndef __NODE_5__H
#define __NODE_5__H

#include "tree_base.h"

class node_5 final : public tree_base {
public:

	// node_5(tree_base* p_head_object, string s_object_name = "Base_object");

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