#include "node_5.h"

// node_5::node_5(tree_base * p_head_object, string s_object_name) : tree_base(p_head_object, s_object_name) {}; 

void node_5::signal(std::string& message) const
{
	message += " (class: 5)";
	std::cout << "\nSignal from " << this->get_my_absolute_path();
}


void node_5::handler(const std::string message) const
{
	std::cout << "\nSignal to " << this->get_my_absolute_path() << " Text: " << message;
}


TYPE_SIGNAL node_5::get_signal_pointer() const
{
	return SIGNAL_D(node_5::signal);
}


TYPE_HANDLER node_5::get_handler_pointer() const
{
	return HANDLER_D(node_5::handler);
}
