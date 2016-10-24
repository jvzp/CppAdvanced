#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class EndsWith {

public:
	/*
	 * Constructor
	 */	
	EndsWith(const std::string& s) : _expected(s) {}
	
	/*
	 * Operator() overload
	 */
	inline bool operator()(const std::string& s) {
		//Ik doe hier nu enkel een contains ipv ends with...
		//het is het principe van functors dat telt he..
		if (s.find(_expected) != std::string::npos) {
			return true;
		} else {
			return false;
		}

	}

private:
	const std::string _expected;

};

class invertor {

public:
	/*
	 * constructor
	 */
	invertor(const EndsWith& s) : endswith_obj(s) {}

	/*
	 * Operator() overload
	 */
	inline bool operator()(const std::string& s) {
		bool value = endswith_obj(s);
		if (value)
			return false;
		else
			return true;
	}

private:
	EndsWith endswith_obj;

};

int main() {
	//functor
	vector<string> strings { "boo", "foo", "zoo", "zo", "bar", "fubar" };

	strings.erase(remove_if(begin(strings), end(strings), EndsWith("oo")), 
			end(strings));

	std::cout << "Remove ends with foo:" << endl;
	for (auto i = strings.begin(); i != strings.end(); ++i)
    		std::cout << *i << ' ';
	std::cout << endl;

	//inverted functionality
	vector<string> strings2 { "boo", "foo", "zoo", "zo", "bar", "fubar" };

	strings2.erase(remove_if(begin(strings2), end(strings2), invertor(EndsWith("oo"))), 
			end(strings2));

	std::cout << "Inverted functionality:" << endl;
	for (auto i = strings2.begin(); i != strings2.end(); ++i)
    		std::cout << *i << ' ';
	std::cout << endl;
}
