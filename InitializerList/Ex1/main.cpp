#include <iostream>
#include <set>
#include <list>

using namespace std;

/*****************************************************************************
 *
 * SearchableStack class
 *
 *****************************************************************************/
template <class T>
class SearchableStack {

public:
	SearchableStack();

	SearchableStack(SearchableStack<T>&& other);

	SearchableStack(std::initializer_list<T> args);

	void push(const T& t);

	void pop();

	bool contains(const T& t) const;

	const T& top() const;

	SearchableStack<T>& operator=(SearchableStack<T>&& other);

private:
	std::multiset<T> set_impl;
	std::list<decltype(set_impl.begin())> list_impl;

};


/*****************************************************************************
 *
 * SearchableStack class implementation
 *
 *****************************************************************************/
/*
 * Standard constructor
 */
template <class T>
SearchableStack<T>::SearchableStack() {}

/*
 * move constructor
 */
template <class T>
SearchableStack<T>::SearchableStack(SearchableStack<T>&& other) {
	//stealing
	set_impl = other.set_impl;
	list_impl = other.list_impl;
}

/*
 * Initializer_list constructor
 */
template <class T>
SearchableStack<T>::SearchableStack(std::initializer_list<T> args) {
	for(auto x : args) {
		this->SearchableStack<T>::push(x);
	}
}

/*
 * Operator= overload
 */
template <class T>
SearchableStack<T>& SearchableStack<T>::operator=(SearchableStack<T>&& other) {
	std::swap(set_impl, other.set_impl);
	std::swap(list_impl, other.list_impl);
        return *this;
}

/*
 * Pushing to the stack: does not guarantee exception safety
 */
template <class T>
void SearchableStack<T>::push(const T& t) {
	auto i = set_impl.insert(t);
	try {
		list_impl.push_back(i);
	} catch (...) {
		set_impl.erase(i);
		throw;
	}
}

/*
 * Pop from the stack: guarantees NoThrow
 */
template <class T>
void SearchableStack<T>::pop() {
	//NoThrow guarantee
	typename std::multiset<T>::iterator it = list_impl.back();
	set_impl.erase(it);
	list_impl.pop_back();
}

/*
 * Contains to search the stack
 */
template <class T>
bool SearchableStack<T>::contains(const T& t) const {
	return set_impl.find(t) != set_impl.end();
}

/*
 * Stack top
 */
template <class T>
const T& SearchableStack<T>::top() const {
	auto it = list_impl.back();
	return *it;
}

/*****************************************************************************
 *
 * Main function for testing
 *
 *****************************************************************************/
int main() {

	int i = 0;

	SearchableStack<int> stack {1,4,5,18};

	if(stack.contains(18)) {
		cout << "SUCCES: 18 is indeed on the stack" << endl;
		i++;
	} else {
		cout << "FAILURE: Foutje" << endl;
	}

	if(stack.contains(6)) {
		cout << "FAILURE: Foutje" << endl;
	} else {
		cout << "SUCCES: 6 is indeed not on the stack" << endl;
		i++;
	}

	stack.pop();
	
	if(stack.contains(18)) {
		cout << "FAILURE: foutje in stack.contains(18)" << endl;
	} else {
		cout << "SUCCES: 18 is indeed not on the stack anymore" << endl;
		i++;
	}

	if(stack.top() == 5) {
		cout << "SUCCES: the new stack top is indeed 5" << endl;
		i++;
	}

	cout << i << " TESTS SUCCEEDED" << endl;
	cout << (4-i) << " TESTS FAILED" << endl;

	return 0;

}
