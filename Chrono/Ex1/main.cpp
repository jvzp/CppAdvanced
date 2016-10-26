#include <iostream>
#include <chrono>

using namespace std;

int main() {

	chrono::system_clock::period p1;
	cout << "System clock: " << p1.num << "/" << p1.den << endl;

	chrono::high_resolution_clock::period p2;
	cout << "High resolution clock" << p2.num << "/" << p2.den << endl;

	return 0;

}
