#include <stdlib.h>
#include <stdio.h>
#include "tree_base.h"
#include "application.h"

#include <iostream>

int main()
{
	// program here
	/*freopen("test1_out.txt", "rt", stdin);
	string had_to_get;
	string s = "";
	getline(cin, s, '\n');
	while (s != "eof") {
		had_to_get += s + "\n";
		getline(cin, s, '\n');
	}
	cout << had_to_get;*/
	application app(NULL);
	app.build_tree_objects();
	return app.exec_app();
}
