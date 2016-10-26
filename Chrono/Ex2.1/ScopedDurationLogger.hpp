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
class ScopedDurationLogger {

public:
	/*
	 * Constructor
	 */
	ScopedDurationLogger(std::string s);

	/*
	 * Destructor
	 */
	~ScopedDurationLogger();

private:
	std::string log;
	time_point<high_resolution_clock> start;
	time_point<high_resolution_clock> end;
};
