#ifndef SCOPED_DURATION_LOGGER_HPP_
#define SCOPED_DURATION_LOGGER_HPP_

/***************************************************************
 *
 * Scoped duration logger class
 *
 ***************************************************************/
#include <chrono>
#include <string>
#include <map>
#include <vector>

struct ScopedDurationLoggerData
{
    static std::map<std::string, std::vector<double>> recordedDurations;

    void operator()(double seconds, const std::string& tag){
        recordedDurations[tag].push_back(seconds);
    }
};

// Hack, better put this in it's own cpp file
std::map<std::string, std::vector<double>> ScopedDurationLoggerData::recordedDurations;

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
	ScopedDurationLogger( std::string log, function_type f=function_type() ) :
		log(log),
		start(high_resolution_clock::now()),
		f(f) {}

	/*
	 * Destructor
	 */
	~ScopedDurationLogger() {
		auto dur = high_resolution_clock::now() - start;
		std::chrono::duration<double> durs(dur);
		f(durs.count(), log);
	}

private:
	std::string log;
	time_point<high_resolution_clock> start;
	function_type f;
};

#endif

