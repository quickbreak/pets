#ifndef __CLASS_CAR__H
#define __CLASS_CAR__H


#include "class_base.h"


class class_car final : public class_base
{
	int coordinate_x, coordinate_y;
	std::string direction;


	void forget_road();

public:

	class_car(class_base* parent = NULL, const std::string = "automobile", int x = 0, int y = 0);
	const std::pair<int, int> get_location() const;
	const std::string get_direction() const;
	int make_a_move(const std::string&, const std::string&);

};

#endif