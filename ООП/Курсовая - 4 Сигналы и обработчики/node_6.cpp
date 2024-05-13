#include "node_6.h"

// node_6::node_6(tree_base* p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {};

void node_6::signal(std::string& message) const
{
	message += " (class: 6)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void node_6::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL node_6::get_signal_pointer() const
{
	return SIGNAL_D(node_6::signal);
}


TYPE_HANDLER node_6::get_handler_pointer() const
{
	return HANDLER_D(node_6::handler);
}
