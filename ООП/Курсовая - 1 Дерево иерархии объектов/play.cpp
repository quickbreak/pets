#include "application.h"
#include "play.h"

void play(string filename_in, string filename_out)
{
	application app(NULL);
	app.build_tree_objects(filename_in);
	app.exec_app(filename_out);
}
