#include <iostream>
#include <set>
#include <list>

using namespace std;

template <class T>
class SearchableStack {

public:
	SearchableStack();

	SearchableStack(SearchableStack<T>&& other);

	void push(const T& t);

	void pop();

	bool contains(const T& t) const;

	const T& top() const;

	SearchableStack<T>& operator=(SearchableStack<T>&& other);

private:
	std::multiset<T> set_impl;
	std::list<decltype(set_impl.begin())> list_impl;

};

template <class T>
SearchableStack<T>::SearchableStack() {}

template <class T>
SearchableStack<T>::SearchableStack(SearchableStack<T>&& other) {
	//stealing
	set_impl = other.set_impl;
	list_impl = other.list_impl;
}

template <class T>
SearchableStack<T>& SearchableStack<T>::operator=(SearchableStack<T>&& other) {
	std::swap(set_impl, other.set_impl);
	std::swap(list_impl, other.list_impl);
        return *this;
}

//Push does not guarantee exception safety
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

//the end() function and the erase() function guarantee NoThrow
template <class T>
void SearchableStack<T>::pop() {
	//NoThrow guarantee
	typename std::multiset<T>::iterator it = list_impl.back();
	set_impl.erase(it);
	list_impl.pop_back();
}

template <class T>
bool SearchableStack<T>::contains(const T& t) const {
	return set_impl.find(t) != set_impl.end();
}

template <class T>
const T& SearchableStack<T>::top() const {
	auto it = list_impl.back();
	return *it;
}

/*int main() {

	int i = 0;

	SearchableStack<int> stack1;
	stack1.push(1);
	stack1.push(4);
	stack1.push(5);
	stack1.push(18);
	SearchableStack<int> stack = std::move(stack1);

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

}*/
