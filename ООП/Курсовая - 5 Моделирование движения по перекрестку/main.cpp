﻿#include "class_system.h"


int main() {
	class_system app;
	app.build_system();
	return app.exec_app();

}


/*
Test_1.input:
5
r001xx-77 -1 -3
r003xx-77 1 -4
End of cars
Display the system status
Switching traffic lights red 3
Switching traffic lights green 3
Car r001xx-77
Car r003xx-77


Display the system status


Display the system status
Turn off the system

Test_1.output:
Ready to work
Traffic light color is green
r001xx-77 ( -1,  -3 )
r003xx-77 ( 1,  -4 )
r001xx-77 the car left the road
r003xx-77 ( 1,  -2 )
Traffic light color is red
r003xx-77 ( 1,  1 )
Traffic light color is yellow
r003xx-77 ( 1,  4 )


Test2.input:
5
car_1 -1 -3
car_2 -1 2
car_4 3 1
car_5 4 1
car_3 1 -3
car_8 1 4
car_7 -3 -1
car_6 -2 -1
End of cars
Display the system status
Switching traffic lights red 3
Switching traffic lights green 3



Display the system status


Display the system status
Car car_7
Car car_7
Car car_1
Display the system status
Turn off the system

Test_2.output:
Ready to work
Traffic light color is green
car_1 ( -1,  -3 )
car_2 ( -1,  2 )
car_3 ( 1,  -3 )
car_4 ( 3,  1 )
car_5 ( 4,  1 )
car_6 ( -2,  -1 )
car_7 ( -3,  -1 )
car_8 ( 1,  4 )
Traffic light color is red
car_2 ( -1,  1 )
car_3 ( 1,  -1 )
car_4 ( -4,  1 )
car_5 ( -3,  1 )
car_6 ( 5,  -1 )
car_7 ( 4,  -1 )
Traffic light color is yellow
car_2 ( -1,  -3 )
car_3 ( 1,  3 )
car_7 the car left the road section
car_7 the car left the road section
car_1 the car left the road section
Traffic light color is green
Turn off the system


Test_3.input:
5
r001xx-77 -1 -3
r003xx-77 1 -4
End of cars
SHOWTREE

Test_3.output:
Ready to work
system is ready
    reader is ready
    remote control is ready
        light is ready
    road is ready
        r001xx-77 is ready
        r003xx-77 is ready
    printer is ready
*/