#ifndef __TREE_BASE__H
#define __TREE_BASE__H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class tree_base {

public:
	tree_base* p_head_object; // ��������� �� ������
	vector<tree_base*>subordinate_objects; // ������ ��������
	string s_object_name; // ��� �������
	// �����������
	tree_base(tree_base* p_head_object, string s_object_name = "Base_object"); 
	// ������� �� ���
	bool change_my_name(string new_name); 
	// ��������� �� ���
	string get_my_name(); 
	// ������� ����� ������
	tree_base* get_my_parent();
	// ���������� ������
	void print(); 
	// ������� ����� ��������� �������
	tree_base* get_my_fav_child(string fav_child_name);

};

#endif
