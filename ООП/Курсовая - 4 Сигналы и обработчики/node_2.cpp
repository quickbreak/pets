#include "node_2.h"

// node_2::node_2(tree_base* p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {};


void node_2::signal(std::string& message) const
{
	message += " (class: 2)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void node_2::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL node_2::get_signal_pointer() const
{
	return SIGNAL_D(node_2::signal);
}


TYPE_HANDLER node_2::get_handler_pointer() const
{
	return HANDLER_D(node_2::handler);
}
