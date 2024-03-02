#include <stdlib.h>
#include <stdio.h>
#include "tree_base.h"
#include "application.h"

int main()
{
	// program here
	application app(NULL);
	app.build_tree_objects();
	return app.exec_app();
}
