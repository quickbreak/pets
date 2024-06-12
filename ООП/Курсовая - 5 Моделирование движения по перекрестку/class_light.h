#pragma once


#include "class_base.h"


class class_light final : public class_base
{
	std::string current_color = "green"; // какой цвет был в прошлом такте
	std::string previous_color = "yellow"; // какой цвет был до прихода этого цвета
	int cycles_count = 5; // сколько осталось тактов
	int green_duration = 5; // сколько тактов сейчас по дефолту отрабатывают зелёный цвет
	int red_duration = 5; // сколько тактов сейчас по дефолту отрабатывают красный цвет
public:

	using class_base::class_base;

	void change_color(std::string s = "");
	const std::string get_current_color();
	const std::string get_previous_color();
	void change_duration(std::string s);
};
