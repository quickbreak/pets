#include "class_light.h"


void class_light::change_color(std::string s)
{
	if (cycles_count > 0)
	{
		--cycles_count;
		return;
	}

	if (current_color == "green" || current_color == "red")
	{
		previous_color = current_color;
		current_color = "yellow";
		cycles_count = 1;
	}
	else // current is yellow
	{
		if (previous_color == "green")
		{
			current_color = "red";
			cycles_count = this->red_duration - 1;
		}
		else
		{
			current_color = "green";
			cycles_count = this->green_duration - 1;
		}
		previous_color = "yellow";
	}
}


void class_light::change_duration(std::string s)
{
	std::string color = "";
	int i = 25;
	while (s[i] != ' ')
	{
		color += s[i];
		++i;
	}
	std::string cycles = "";
	while (i < s.size())
	{
		cycles += s[i];
		++i;
	}
	int duration = stoi(cycles);

	if (duration >= 2)
	{
		if (color == "green")
		{
			if (this->current_color == "green")
			{
				int done = this->green_duration - this->cycles_count;
				this->cycles_count = duration - done;
			}
			this->green_duration = duration;
		}

		else
		{
			if (this->current_color == "red")
			{
				int done = this->red_duration - this->cycles_count;
				this->cycles_count = duration - done;
			}
			this->red_duration = duration;
		}
	}
}


const std::string class_light::get_current_color()
{
	return this->current_color;
}


const std::string class_light::get_previous_color()
{
	return this->previous_color;
}
