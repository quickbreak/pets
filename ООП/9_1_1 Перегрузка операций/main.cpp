#include <iostream>
#include <vector>

using namespace std;

class triangle {
	int a, b, c;
public:


	triangle() :a(0), b(0), c(0) {};
	triangle(int a, int b, int c) :a(a), b(b), c(c) {};

	int get_a() const {
		return this->a;
	}

	int get_b() const {
		return this->b;
	}

	int get_c() const {
		return this->c;
	}

	void set_a(int a) {
		this->a = a;
	}

	void set_b(int b) {
		this->b = b;
	}

	void set_c(int c) {
		this->c = c;
	}
};


triangle& operator + (triangle& first, triangle& second) {
	triangle result;
	int side_1 = first.get_a() + second.get_a();
	int side_2 = first.get_b() + second.get_b();
	int side_3 = first.get_c() + second.get_c();
	if (side_1 >= side_2 && side_1 >= side_3) { // side_1 is max
		if (side_1 < side_2 + side_3) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	else if (side_2 >= side_1 && side_2 >= side_3) { // side_2 is max
		if (side_2 < side_1 + side_3) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	else if (side_3 >= side_1 && side_3 >= side_2) { // side_3 is max
		if (side_3 < side_1 + side_2) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	return result;
}

triangle& operator - (triangle& first, triangle& second) {
	triangle result;
	int side_1 = first.get_a() - second.get_a();
	int side_2 = first.get_b() - second.get_b();
	int side_3 = first.get_c() - second.get_c();
	if (side_1 >= side_2 && side_1 >= side_3) { // side_1 is max
		if (side_1 < side_2 + side_3) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	else if (side_2 >= side_1 && side_2 >= side_3) { // side_2 is max
		if (side_2 < side_1 + side_3) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	else if (side_3 >= side_1 && side_3 >= side_2) { // side_3 is max
		if (side_3 < side_1 + side_2) {
			result.set_a(side_1);
			result.set_b(side_2);
			result.set_c(side_3);
		}
	}
	return result;
}


int main() {

	int n, a, b, c;
	cin >> n;
	vector<triangle>v(n + 1);

	for (int i = 1; i <= n; ++i) {
		cin >> a >> b >> c;
		v[i] = *(new triangle(a, b, c));
	}

	int first, second;
	char oper;
	int cnt = 0;
	while (cin >> first) {

		cin >> oper >> second;
		if (oper == '+')
			v[first] = v[first] + v[second];
		else
			v[first] = v[first] - v[second];
	}
	cout << "a = " << v[first].get_a() << "; " << "b = " <<
		v[first].get_b() << "; " << "c = " << v[first].get_c() << ".";
	return 0;
}

/*
3
3 4 5
6 8 10
5 12 13
1 + 2
1 - 3
*/