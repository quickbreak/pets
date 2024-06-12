#ifndef __class_reading__H
#define __class_reading__H


#include "class_base.h"


class class_reading final : public class_base
{

public:

	using class_base::class_base;

	// читается строка данных
	void read(std::string&) const;

};

#endif
