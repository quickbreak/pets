#include "class_road.h"


void class_road::set_size(std::string message)
{
	int size = stoi(message);
	this->size = size;
}


int class_road::get_size() const
{
	return this->size;
}


void class_road::add_car(const std::string s)
{
	if (s == "End of cars")
		return;


	std::string car_name;
	int i = 0;
	while (s[i] != ' ')
	{
		car_name += s[i];
		++i;
	}
	std::string help;
	++i;
	while (s[i] != ' ')
	{
		help += s[i];
		++i;
	}
	int coordinate_x = stoi(help);

	++i;
	help.clear();
	while (i < s.size())
	{
		help += s[i];
		++i;
	}
	int coordinate_y = stoi(help);

	class_car* new_car = new class_car(this, car_name, coordinate_x, coordinate_y);
	this->cars[car_name] = new_car;
	if (new_car->get_direction() == "up")
		this->up[coordinate_y] = new_car;
	else if (new_car->get_direction() == "down")
		this->down[coordinate_y] = new_car;
	else if (new_car->get_direction() == "left")
		this->left[coordinate_x] = new_car;
	else if (new_car->get_direction() == "right")
		this->right[coordinate_x] = new_car;
}


const std::pair<int, int> class_road::get_car_location(const std::string& car_name)
{
	return cars[car_name]->get_location();
}


void class_road::remove_car(class_car* car_pointer)
{
	this->cars.erase(car_pointer->get_my_name());
	int x = car_pointer->get_location().first;
	int y = car_pointer->get_location().second;
	const std::string direction = car_pointer->get_direction();
	if (direction == "up")
		this->up.erase(y);
	else if (direction == "down")
		this->down.erase(y);
	else if (direction == "right")
		this->right.erase(x);
	else if (direction == "left")
		this->left.erase(x);
}


void class_road::make_cars_move(const std::string& color, const std::string& previous_color)
{
	// те, кто едет влево
	std::map<int, class_car*>mp;
	while (this->left.size() > 0)
	{
		auto [x, car] = *(this->left.begin());
		int code = car->make_a_move(color, previous_color);
		if (code == 2)
			continue;
		else
			mp[car->get_location().first] = car;
		this->left.erase(this->left.begin());
	}
	this->left = mp;
	mp.clear();
	// те, кто едет вниз
	while (this->down.size() > 0)
	{
		auto [y, car] = *(this->down.begin());
		int code = car->make_a_move(color, previous_color);
		if (code == 2) {
			continue;
		}
		else
			mp[car->get_location().second] = car;
		this->down.erase(this->down.begin());
	}
	this->down = mp;
	mp.clear();
	// те, кто едет вправо
	while (this->right.size() > 0)
	{
		auto [x, car] = *(std::prev(this->right.end()));
		int code = car->make_a_move(color, previous_color);
		if (code == 2) {
			continue;
		}
		else
			mp[car->get_location().first] = car;

		this->right.erase(std::prev(this->right.end()));
	}
	this->right = mp;
	mp.clear();
	// те, кто едет вверх
	while (this->up.size() > 0)
	{
		auto [y, car] = *(std::prev(this->up.end()));
		int code = car->make_a_move(color, previous_color);
		if (code == 2) {
			continue;
		}
		else
			mp[car->get_location().second] = car;
		this->up.erase(std::prev(this->up.end()));
	}
	this->up = mp;
	mp.clear();
}


bool class_road::car_left(const std::string& car_name) const
{
	return this->cars.find(car_name) == this->cars.end();
}


void class_road::display_status(std::string& message) 
{
	message = "\nTraffic light color is " + message;

	for (auto [name, pointer] : this->cars)
	{
		auto [x, y] = pointer->get_location();
		message += "\n" + name + " ( " + std::to_string(x) + ",  " + std::to_string(y) + " )";
	}
}


void class_road::show_car(std::string& message)
{
	std::string name = message.substr(message.find(' ') + 1);

	if (this->car_left(name))
		message = "\n" + name + " the car left the road section";
	else
	{
		auto [x, y] = this->get_car_location(name);
		message = "\n" + name + " ( " + std::to_string(x) + ",  " + std::to_string(y) + " )";
	}
}
