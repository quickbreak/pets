#include<iostream>
#include<string>

using namespace std;

class lvl_1 {
private:
	string name;
public:
	lvl_1(string name) : 
		name(name+"_1") 
	{
		// cout << this->name << '\n';
	}
	const string get_name() const {
		return this->name;
	}
};

class lvl_2 : public lvl_1 {
private:
	string name;
public:
	lvl_2(string name) : 
		lvl_1(name + "_2"), 
		name(name + "_2") 
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_3 : public lvl_1 {
private:
	string name;
public:
	lvl_3(string name) :
		lvl_1(name + "_3"), 
		name(name + "_3") 
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_4 : virtual public lvl_1 {
private:
	string name;
public:
	lvl_4(string name) : 
		lvl_1 (name + "_4"), 
		name(name + "_4")
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_5 : virtual public lvl_1 {
private:
	string name;
public:
	lvl_5(string name) : 
		lvl_1(name + "_5"), 
		name(name + "_5") 
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_6 : public lvl_2, public lvl_3 {
private:
	string name;
public:
	lvl_6(string name) : 
		lvl_2(name + "_6"), 
		lvl_3(name + "_6"),
		name(name + "_6") 
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_7 : public lvl_4, public lvl_5 {
private:
	string name;
public:
	lvl_7(string name) : 
		lvl_1(name + "_7"),
		lvl_4(name + "_7"),
		lvl_5(name + "_7"),
		name(name + "_7") 
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

class lvl_8 final: public lvl_6, public lvl_7 {
private:
	string name;
public:
	lvl_8(string name) :
		lvl_1(name + "_8"),
		lvl_6(name + "_8"), 
		lvl_7(name + "_8"), 
		name(name + "_8")
	{
		// cout << this->name << '\n';
	};
	const string get_name() const {
		return this->name;
	}
};

int main() {
	lvl_8* poor_object  = new lvl_8("miha");
	cout << ((lvl_1*)(lvl_2*)(lvl_6*)poor_object)->get_name() << '\n';
	cout << ((lvl_1*)(lvl_3*)(lvl_6*)poor_object)->get_name() << '\n';
	cout << ((lvl_1*)(lvl_7*)poor_object)->get_name() << '\n';
	cout << ((lvl_1*)(lvl_7*)poor_object)->get_name() << '\n';
	cout << ((lvl_2*)(lvl_6*)poor_object)->get_name() << '\n';
	cout << ((lvl_3*)(lvl_6*)poor_object)->get_name() << '\n';
	cout << ((lvl_4*)(lvl_7*)poor_object)->get_name() << '\n';
	cout << ((lvl_5*)(lvl_7*)poor_object)->get_name() << '\n';
	cout << ((lvl_6*)poor_object)->get_name() << '\n';
	cout << ((lvl_7*)poor_object)->get_name() << '\n';
	cout << poor_object->get_name() << '\n';
}