#include <iostream>
#include "ScopedDurationLogger.hpp"
#include <chrono>

using namespace std;

class functorclass {
public:
	functorclass() {}

	void operator()(string log, double time_lapse) {
		cout << log << " took: " << time_lapse << "s" << endl;
	}	

private:

};

int main() {

	ScopedDurationLogger<functorclass> d1("Main function", functorclass());

	int i = 0;
	while( i < 100000000 ) {
		i++;
	}

	//ScopedDurationLogger<functor>::ScopedDurationLogger d2("After while loop", functor());

	return 0;

}
