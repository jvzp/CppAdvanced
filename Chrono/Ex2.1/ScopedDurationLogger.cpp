/***************************************************************
 *
 * Scoped duration logger class
 *
 ***************************************************************/
#include "ScopedDurationLogger.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

/*
 * Constructor of ScopedDurationLogger
 */
ScopedDurationLogger::ScopedDurationLogger(string s) : log(s) {
	start = high_resolution_clock::now();
	std::time_t ttp = std::chrono::high_resolution_clock::to_time_t(start);
	cout << std::ctime(&ttp) << ": " << log << endl;
}

/*
 * Destructor of ScopedDurationLogger
 */
ScopedDurationLogger::~ScopedDurationLogger() {
	end = high_resolution_clock::now();
	std::time_t ttp = std::chrono::high_resolution_clock::to_time_t(end);
	cout << std::ctime(&ttp) << ": destruction of " << log << endl;
	auto dur = end-start;
	chrono::duration<double> durs(duration_cast<duration<double>>(dur));
	cout << "Life time of " << log << ": " << durs.count() << endl;
}
