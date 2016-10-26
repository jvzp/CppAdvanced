#include <iostream>
#include <boost/algorithm/string/join.hpp>
#include "ScopedDurationLogger.hpp"
#include <chrono>
#include <sstream>

using namespace std;

void operator_plus() {

	ScopedDurationLogger<ScopedDurationLoggerData> d1("Operator+");

	int i = 0;
	string s("b");	
	while(i < 100000) {
		s = s + "b";
		i++;
	}
}

void operator_plus_is() {

	ScopedDurationLogger<ScopedDurationLoggerData> d1("Operator+=");

	int i = 0;
	string s("b");	
	while(i < 100000) {
		s += "b";
		i++;
	}
}

void boost_join() {

	ScopedDurationLogger<ScopedDurationLoggerData> d1("Boost::algorithm::join");

	int i = 0;
	string s("b");
	vector<string> vs;
	while(i < 100000) {
		vs.push_back(s);
		i++;
	}
	string joined = boost::algorithm::join(vs, "");
	
}

void string_stream() {

	ScopedDurationLogger<ScopedDurationLoggerData> d1("Osstringstream");

	std::stringstream ss;

	int i = 0;
	while(i < 100000) {
		ss << "s";
		i++;
	}
	
}

int main() {
	int j = 0;
	for(j = 0; j < 50; j++) {
		operator_plus();
		operator_plus_is();
		boost_join();
		string_stream();
	}

	cout << "After running every operator 50 times 100000 copies/assignments, the timing results are on average:" << endl;

	for (auto x : ScopedDurationLoggerData::recordedDurations) {
		double sum = 0;
		for(auto y : x.second) {
			sum += y;
		}
		double avg = sum/(x.second.size());
        	cout << x.first << " took " << avg << " seconds" << endl;
	}

	return 0;

}
