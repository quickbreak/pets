#ifndef __CLASS_REMOTE_CONTROL__H
#define __CLASS_REMOTE_CONTROL__H


#include "class_base.h"


class class_remote_control final : public class_base
{

public:

	using class_base::class_base;

	void signal_to_light(std::string&);
};

#endif