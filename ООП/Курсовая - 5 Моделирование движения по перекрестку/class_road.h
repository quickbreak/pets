#ifndef __class_road__H
#define __class_road__H


#include "class_base.h"
#include "class_car.h"
#include<map>


class class_system;

class class_road final : public class_base
{
	friend class class_car;


	std::map<std::string, class_car*>cars; // список машин, упорядоченный по номерам
	int size = 0; // длина дороги в каждом из 4 направлений
	// для up, down int - это y; для left, right - x
	std::map<int, class_car*>up, down, left, right;


	int get_size() const;
	bool car_left(const std::string& car_name) const;
	void remove_car(class_car* car_pointer);
	const std::pair<int, int> get_car_location(const std::string&);

public:

	using class_base::class_base;

	void set_size(std::string size);
	void add_car(const std::string);
	void make_cars_move(const std::string&, const std::string&);
	void display_status(std::string& message);
	void show_car(std::string& message);

};

#endif