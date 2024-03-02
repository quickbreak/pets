#include "application.h"
#include "tree_base.h"
#include "node.h"

using namespace std;

application::application(tree_base* p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {};

void application::build_tree_objects() {
	string parent, child;
	tree_base* p_head_object = this;
	cin >> parent; // ����� �������
	this->s_object_name = parent;
	bool is_new_name = false; // ���� sibling � ����� ������?
	while (true) {
		cin >> parent >> child;
		if (parent == child) // ����� ������
			break;

		int n = p_head_object->subordinate_objects.size();
		// ������ ���� �������� - ������� ������� �������� ��������
		// �� �� �� ����� ������ ������
		if (parent != p_head_object->s_object_name) {
			if (n > 0 &&
				parent == p_head_object->subordinate_objects[n - 1]->s_object_name) {
				p_head_object = p_head_object->subordinate_objects[n - 1];
				node* object = new node(p_head_object, child);
			}
		}
		// ����� ������� ��� (child) ������ ������,
		// ���� ��� ������ ����� � ����� ������
		else {
			is_new_name = false;
			for (auto sibling : p_head_object->subordinate_objects) {
				if (sibling->s_object_name == child) {
					is_new_name = true;
					break;
				}
			}
			if (!is_new_name) {
				node* object = new node(p_head_object, child);
			}
		}

	}
}
int application::exec_app() {
	this->print();

	return 0;
}