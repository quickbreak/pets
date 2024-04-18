#include "application.h"
#include <iostream>


int main() {
	application app(NULL);
	app.build_tree_objects();
	return app.exec_app();

}


/*
input:
app_root
app_root object_01 3
app_root object_02 2
object_02 object_04 3
object_02 object_05 5
object_01 object_07 2
endtree
app_root 1
object_07 3
object_01 1
object_02 -2
object_04 1

Ctrl+Z
Enter


output:
Object tree
app_root
	object_01
		object_07
	object_02
		object_04
		object_05
The tree of objects and their readiness
app_root is ready
	object_01 is ready
		object_07 is not ready
	object_02 is ready
		object_04 is ready
		object_05 is not ready
*/