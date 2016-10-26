#ifndef SCOPED_DURATION_LOGGER_HPP_
#define SCOPED_DURATION_LOGGER_HPP_

/***************************************************************
 *
 * Scoped duration logger class
 *
 ***************************************************************/
#include <chrono>
#include <string>

using namespace std::chrono;

/*
 * Class
 */
template <typename function_type>
class ScopedDurationLogger {

public:
	/*
	 * Constructor
	 */
	ScopedDurationLogger(std::string s, function_type f);

	/*
	 * Destructor
	 */
	~ScopedDurationLogger();

private:
	std::string log;
	time_point<high_resolution_clock> start;
	function_type f;
};

template <typename function_type>
ScopedDurationLogger<function_type>::ScopedDurationLogger(std::string s, function_type f) :
	log(s),
	start(high_resolution_clock::now()),
	f(f) {}

/*
 * Destructor of ScopedDurationLogger
 */
template <typename function_type>
ScopedDurationLogger<function_type>::~ScopedDurationLogger() {
	auto dur = high_resolution_clock::now() - start;
	std::chrono::duration<double> durs(dur);
	f(log, durs.count());
}

#endif

