#ifndef __class_info__H
#define __class_info__H


#include "class_base.h"


class class_info final : public class_base
{

public:

	using class_base::class_base;

	// выводит сообщение
	void print_message(const std::string);

};

#endif