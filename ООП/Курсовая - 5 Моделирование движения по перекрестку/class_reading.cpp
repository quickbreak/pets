#include "class_reading.h"
#include<iostream>


void class_reading::read(std::string& message) const
{
	getline(std::cin, message);
}
