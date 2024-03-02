#include "tree_base.h"


tree_base::tree_base(tree_base* p_head_object, string s_object_name) {
	this->p_head_object = p_head_object; // ��������� �� ������
	this->s_object_name = s_object_name; // ��� �������
	if (p_head_object != NULL) {
		p_head_object->subordinate_objects.push_back(this); // ���������� ������ ������ �������		
	}
}

void tree_base::print() {
	cout << this->s_object_name; // ������ �������
	tree_base* parent = this;
	int n;
	while (parent->subordinate_objects.size() > 0) { // ����������� ���������������� �������� �������� ������
		cout << '\n';
		cout << parent->s_object_name; // �������� ������
		n = parent->subordinate_objects.size();
		for (int i = 0; i < n; ++i) {
			cout << "  " << parent->
				subordinate_objects[i]->
				s_object_name; // � ��� ���������������� ��������
		}
		// ��������� � ���������� ������
		parent = parent->subordinate_objects[n - 1];

	}
}

string tree_base::get_my_name() {
	return this->s_object_name;
}

tree_base* tree_base::get_my_parent() {
	return this->p_head_object;
}

tree_base* tree_base::get_my_fav_child(string fav_child_name) {
	// ������� � ���� ����� ���� ������ ����������������� �������
	for (auto child : this->subordinate_objects) {
		if (child->s_object_name == fav_child_name) {
			return child;
		}
	}
	return NULL;
}


bool tree_base::change_my_name(string new_name) {
	tree_base* parent = this->p_head_object;
	// ���� ������� ���, �� ����� �� ���������,
	// ���� � ���� siblings ���� ����� ���:
	// ��� �� �������� ������ �����...
	for (auto sibling : parent->subordinate_objects) {
		if (sibling->s_object_name == new_name) {
			return false;
		}
	}
	this->s_object_name = new_name;
	return true;
}