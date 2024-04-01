#include "application.h"
#include <iostream>
#include <string>
#include "tree_base.h"

int successfull_tests_cnt;

void play(string filename_in, string filename_out)
{
	application app(NULL);
	app.build_tree_objects(filename_in);
	app.exec_app(filename_out);
}

int main() {
	application app(NULL);
	app.build_tree_objects();
	app.exec_app();
	return 0;
	/*std::string filestart = "test", fileend_in = "_in.txt", fileend_out = "_out.txt";
	int tests_cnt = 7;
	successfull_tests_cnt = 0;
	for (int i = 1; i <= tests_cnt; ++i) {
		std::string filename_in = filestart + std::to_string(i) + fileend_in;
		std::string filename_out = filestart + std::to_string(i) + fileend_out;
		play(filename_in, filename_out);

	}
	if (successfull_tests_cnt == tests_cnt)
		std::cout << "SUCCEEDED IN ALL THE TESTS!!!";
	else
		std::cout << "Succeeded in " << successfull_tests_cnt << " outta " << tests_cnt << " Tests...";
	return 0;*/
}