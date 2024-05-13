#include "node_3.h"

// node_3::node_3(tree_base* p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {};

void node_3::signal(std::string& message) const
{
	message += " (class: 3)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void node_3::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL node_3::get_signal_pointer() const
{
	return SIGNAL_D(node_3::signal);
}


TYPE_HANDLER node_3::get_handler_pointer() const
{
	return HANDLER_D(node_3::handler);
}
