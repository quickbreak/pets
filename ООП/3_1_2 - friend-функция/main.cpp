#include <iostream>
#include <vector>

using namespace std;

// если не объявить,
class B;

class A {
	// то как же компилятор поймёт, какой тип у второго аргумента?
	friend int function(const A&, const B&);
	// не важно, где объявлять друга: в private- или public- зоне
public:
	A(int first) : first(first) {};
private:
	int first = -int(1e9);

};

class B {
	friend int function(const A&, const B&);
public:
	B() = default;
	void set_numbers(int first, int second) {
		this->first = first;
		this->second = second;
	}
private:
	int first = -int(1e9);
	int second = -int(1e9);

};

int function(const A& a, const B& b) {
	int result = max(b.first, b.second);
	result = max(result, a.first);
	return result;
}


int main() {

	int first; 
	cin >> first;
	A a(first);
	int second;
	cin >> first >> second;
	B b;
	b.set_numbers(first, second);
	cout << "max = " << function(a, b);

	return 0;
}