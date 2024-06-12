#include "class_system.h"
#include<iostream>
#include<fstream>


class_system::class_system(class_base* parent, const std::string name):
	class_base(parent, name)
{
	this->reader = new class_reading(this, "reader");
	this->control = new class_remote_control(this, "remote control");
	this->light = new class_light(this->control, "light");
	this->road = new class_road(this, "road");
	this->printer = new class_info(this, "printer");
}


void class_system::build_system() 
{
	// все объекты приводятся в состояние готовности
	this->get_all_ready();


	std::string message;

	// вводится размер дороги
	this->reader->set_connect(SIGNAL_D(class_reading::read), this->road, HANDLER_D(class_road::set_size));
	this->reader->emit_signal(SIGNAL_D(class_reading::read), HANDLER_D(class_road::set_size), message);
	this->reader->remove_connect(SIGNAL_D(class_reading::read), this->road, HANDLER_D(class_road::set_size));

	this->reader->set_connect(SIGNAL_D(class_reading::read), this->road, HANDLER_D(class_road::add_car));
	while (true)
	{
		// вводится информация об очередной машине
		this->reader->emit_signal(SIGNAL_D(class_reading::read), HANDLER_D(class_road::add_car), message);

		if (message == "End of cars")
			break;
	}
	this->reader->remove_connect(SIGNAL_D(class_reading::read), this->road, HANDLER_D(class_road::add_car));

}


int class_system::exec_app() 
{
	this->reader->set_connect(SIGNAL_D(class_reading::read), this, HANDLER_D(class_system::commands_handler));
	this->road->set_connect(SIGNAL_D(class_road::display_status), this->printer, HANDLER_D(class_info::print_message));
	this->control->set_connect(SIGNAL_D(class_remote_control::signal_to_light), this->light, HANDLER_D(class_light::change_color));
	this->control->set_connect(SIGNAL_D(class_remote_control::signal_to_light), this->light, HANDLER_D(class_light::change_duration));
	this->road->set_connect(SIGNAL_D(class_road::show_car), this->printer, HANDLER_D(class_info::print_message));
	
	std::ofstream fout("output.txt");
	fout.close();

	std::string message = "Ready to work"; 
	this->set_connect(SIGNAL_D(class_system::signal_to_printer), this->printer, HANDLER_D(class_info::print_message));
	this->emit_signal(SIGNAL_D(class_system::signal_to_printer), HANDLER_D(class_info::print_message), message);
	message.clear();

	while (true)
	{
		// вводится очередная команда
		this->reader->emit_signal(SIGNAL_D(class_reading::read), HANDLER_D(class_system::commands_handler), message);
		if (message == "Turn off the system" || message == "SHOWTREE")
			break;

		this->make_all_move();
	}

	this->reader->remove_connect(SIGNAL_D(class_reading::read), this, HANDLER_D(class_system::commands_handler));
	this->road->remove_connect(SIGNAL_D(class_road::display_status), this->printer, HANDLER_D(class_info::print_message)); 
	this->road->remove_connect(SIGNAL_D(class_road::show_car), this->printer, HANDLER_D(class_info::print_message));
	this->control->remove_connect(SIGNAL_D(class_remote_control::signal_to_light), this->light, HANDLER_D(class_light::change_color));
	this->control->remove_connect(SIGNAL_D(class_remote_control::signal_to_light), this->light, HANDLER_D(class_light::change_duration));
	this->remove_connect(SIGNAL_D(class_system::signal_to_printer), this->printer, HANDLER_D(class_info::print_message));


	std::ifstream fin("output.txt");
	std::string s;
	while (std::getline(fin, s))
	{
		std::cout << s << '\n';
	}
	fin.close();

	return 0;
}


void class_system::commands_handler(std::string message)
{
	if (message == "Turn off the system") // конец работы системы
	{
		message = "\n" + message;
		this->emit_signal(SIGNAL_D(class_system::signal_to_printer), HANDLER_D(class_info::print_message), message);		
		return;
	}

	else if (message == "SHOWTREE") // вывод системы и конец работы системы
	{
		this->print_system("");
		return;
	}

	else if (message.find("Switching traffic lights") != std::string::npos) // смена длительности цвета
	{
		// меняется цвет светофора и длительность
		this->control->emit_signal(SIGNAL_D(class_remote_control::signal_to_light), HANDLER_D(class_light::change_duration), message);
	}

	else if (message == "Display the system status") // вывод цвета светофора и положения машин
	{
		message = this->light->get_current_color();
		this->road->emit_signal(SIGNAL_D(class_road::display_status), HANDLER_D(class_info::print_message), message);
	}

	else if (message.find("Car") != std::string::npos) // вывод положения машины
	{
		this->road->emit_signal(SIGNAL_D(class_road::show_car), HANDLER_D(class_info::print_message), message);
	}
}


void class_system::make_all_move()
{
	std::string message = "";
	//  меняется цвет светофора
	this->control->emit_signal(SIGNAL_D(class_remote_control::signal_to_light), HANDLER_D(class_light::change_color), message);
	// двигаются все машины
	this->road->make_cars_move(this->light->get_current_color(), this->light->get_previous_color());
}


void class_system::signal_to_printer(const std::string& message)
{}
