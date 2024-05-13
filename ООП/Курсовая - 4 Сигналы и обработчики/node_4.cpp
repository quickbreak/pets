#include "node_4.h"

// node_4::node_4(tree_base* p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {};

void node_4::signal(std::string& message) const
{
	message += " (class: 4)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void node_4::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL node_4::get_signal_pointer() const
{
	return SIGNAL_D(node_4::signal);
}


TYPE_HANDLER node_4::get_handler_pointer() const
{
	return HANDLER_D(node_4::handler);
}
