#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class TextFileReader {

private:
	string path;
  
public:
	
	/*
	 * Constructor
	 */
	TextFileReader(const string& path) : path(path) {}

	struct textfile_iterator {

		//Fields
		ifstream infile;
		string line;

		/*
 		 * Private basic constructor
		 */
		textfile_iterator() : infile(), line() {}

		textfile_iterator(textfile_iterator&& t) : infile(std::move(t.infile)), line(std::move(t.line)) {}

		/*
 		 * Private constructor 
		 */
		textfile_iterator(const string& path) : infile(path), line() {
			operator++();
		}

		/*
 		 * Operator++ overload
		 */
		textfile_iterator& operator++() {
			if(!getline(infile,line)) {
				infile.close();
				line.erase();
			}
			return *this;
		}

		/*
 		 * Operator== overload
		 */
		bool operator==(const textfile_iterator& it) {
			return ( ( infile.is_open() == it.infile.is_open() ) && (line == it.line) );
		}

		/*
 		 * Operator!= overload
		 */
		bool operator!=(const textfile_iterator& it) {
			return !operator==(it);
		}

		/*
 		 * Operator* overload
		 */
		string& operator*() {
			return this->line;
		}

	};

	/*
	 * Begin function for the iterator
	 */
	auto begin() {
		return textfile_iterator(path);
	}

	/*
	 * end function for the iterator;
	 */
	auto end() {
		return textfile_iterator();
	}

};

auto readlines(const string& path) {
	return TextFileReader(path);
}

/*
 * Main function
 */
int main() {

	for(auto x : readlines("jonas.txt")) {
		cout << x << endl;
	}

	return 0;

}

