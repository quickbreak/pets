#include "class_car.h"
#include "class_road.h"
#include<map>


class_car::class_car(class_base* parent, const std::string name, int x, int y) :
	class_base(parent, name),
	coordinate_x(x),
	coordinate_y(y)
{
	if (y == 1)
		this->direction = "left";
	else if (y == -1)
		this->direction = "right";
	else if (x == 1)
		this->direction = "up";
	else if (x == -1)
		this->direction = "down";
}


const std::string class_car::get_direction() const
{
	return this->direction;
}


const std::pair<int, int> class_car::get_location() const
{
	return { this->coordinate_x, this->coordinate_y };
}


void class_car::forget_road()
{
	((class_road*)(this->get_my_parent()))->remove_car(this);
}


int class_car::make_a_move(const std::string& color, const std::string& previous_color)
{
	int x = this->coordinate_x;
	int y = this->coordinate_y;
	std::map<int, class_car*> up = ((class_road*)(this->get_my_parent()))->up;
	std::map<int, class_car*> down = ((class_road*)(this->get_my_parent()))->down;
	std::map<int, class_car*> right = ((class_road*)(this->get_my_parent()))->right;
	std::map<int, class_car*> left = ((class_road*)(this->get_my_parent()))->left; 
	int size = (((class_road*)(this->get_my_parent()))->get_size());

	int new_coordinate, current_coordinate;

	if (this->direction == "left")
	{
		current_coordinate = x;
		new_coordinate = current_coordinate - 1 - (current_coordinate - 1 == 0);
		if (new_coordinate == 1) // сейчас машина у стоп-линии, впереди - перекрёсток
		{
			// if (color == "red" || (color == "yellow" && previous_color == "green"))			-- согласно примеру
			if (color == "red" || color == "yellow")
				return 1; // стоит на месте
		}
		// занято - ничего не попишешь
		if (left.find(new_coordinate) != left.end())
		{
			return 1;
		}
		// свободно или обрыв
		left.erase(current_coordinate); // свой квадрат подкидает
		if (new_coordinate == -size - 1) // обрыв
		{
			this->forget_road();
			return 2;
		}
		// шаг вперёд
		this->coordinate_x = new_coordinate;
		left[new_coordinate] = this; // новый квадрат занимает
		return 1;
	}

	else if (this->direction == "right")
	{
		current_coordinate = x;
		new_coordinate = current_coordinate + 1 + (current_coordinate + 1 == 0);
		if (new_coordinate == -1) // сейчас машина у стоп-линии, впереди - перекрёсток
		{
			// if (color == "red" || (color == "yellow" && previous_color == "green"))			-- согласно примеру
			if (color == "red" || color == "yellow")
				return 1; // стоит на месте
		}

		if (right.find(new_coordinate) != right.end()) // занято - ничего не попишешь
		{
			return 1;
		}
		// свободно или обрыв
		right.erase(current_coordinate); // свой квадрат подкидает
		if ((new_coordinate) == size + 1) // обрыв
		{
			this->forget_road();
			return 2;
		}
		else if (right.find(new_coordinate) == right.end()) // свободно
		{
			this->coordinate_x = new_coordinate;
			right[new_coordinate] = this; // новый квадрат занимает
		}
		return 1;
	}

	else if (this->direction == "up")
	{
		current_coordinate = y;
		new_coordinate = current_coordinate + 1 + (current_coordinate + 1 == 0);
		if (new_coordinate == -1) // сейчас машина у стоп-линии, впереди - перекрёсток
		{
			// if (color == "green" || (color == "yellow" && previous_color == "red"))			-- согласно примеру
			if (color == "green" || color == "yellow")
				return 1; // стоит на месте
		}

		if (up.find(new_coordinate) != up.end()) // занято - ничего не попишешь
		{
			return 1;
		}
		// свободно или обрыв
		up.erase(current_coordinate); // свой квадрат подкидает
		if (new_coordinate == size + 1) // обрыв
		{
			this->forget_road();
			return 2;
		}
		else if (up.find(new_coordinate) == up.end()) // свободно
		{
			this->coordinate_y = new_coordinate;
			up[new_coordinate] = this; // новый квадрат занимает
		}
		return 1;
	}
	else if (this->direction == "down")
	{
		current_coordinate = y;
		new_coordinate = current_coordinate - 1 - (current_coordinate - 1 == 0);
		if (new_coordinate == 1) // сейчас машина у стоп-линии, впереди - перекрёсток
		{
			// if (color == "green" || (color == "yellow" && previous_color == "red"))			-- согласно примеру
			if (color == "green" || color == "yellow")
				return 1; // стоит на месте
		}

		if (down.find(new_coordinate) != down.end()) // занято - ничего не попишешь
		{
			return 1;
		}
		// свободно или обрыв
		down.erase(current_coordinate); // свой квадрат подкидает
		if (new_coordinate == -size - 1) // обрыв
		{
			this->forget_road();
			return 2;
		}
		else if (down.find(new_coordinate) == down.end()) // свободно
		{
			this->coordinate_y = new_coordinate;
			down[new_coordinate] = this; // новый квадрат занимает
		}
		return 1;
	}
}
