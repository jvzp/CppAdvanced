#include <iostream>
#include "ScopedDurationLogger.hpp"
#include <chrono>

using namespace std;

int main() {

	chrono::high_resolution_clock::period p;
	cout << p.num << "/" << p.den << endl;

	ScopedDurationLogger d1("Start of main");

	int i = 0;
	while( i < 1000000 ) {
		i++;
	}

	ScopedDurationLogger d2("After while loop");

	return 0;

}
