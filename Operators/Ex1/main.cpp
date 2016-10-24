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
	inline bool operator()(const std::string& s) const {
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

int main() {

	vector<string> strings { "boo", "foo", "zoo", "zo", "bar", "fubar" };

	strings.erase(remove_if(begin(strings), end(strings), EndsWith("oo")), 
			end(strings));

	for (auto i = strings.begin(); i != strings.end(); ++i)
    		std::cout << *i << ' ';

	std::cout << endl;

}
