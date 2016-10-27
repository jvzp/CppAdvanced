#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <future>
#include <deque>
#include <mutex>
#include <vector>

using namespace std;

class WorkQueue {

public:
	/*
	 * Constructor
	 */
	WorkQueue();

	/*
	 * Destructor
	 */
	~WorkQueue();

	/*
	 * Submit work to do;
	 */
	auto submit(packaged_task<string(void)>&& pt) {
		auto future = pt.get_future();
		lock_guard<mutex> lck(m);
		queue.emplace_back(std::move(pt));
		return future;
	}

private:
	void run();

	atomic<bool> started;
	thread thr;
	deque<packaged_task<string(void)>> queue;
	mutex m;

};

/***********************************************************************/
/*
 * Callback function for the thread to run
 */
void WorkQueue::run() {
	//make a copy of the queue to keep the critical section short
	deque<packaged_task<string(void)>> copy_queue;
	while(started) 
	{ 
		{
		lock_guard<mutex> lck(m);
		swap(copy_queue, queue);
		}

		for(auto& task: copy_queue) {
			task();
		}
		copy_queue.clear();
	}
}

/*
 * Constructor
 */
WorkQueue::WorkQueue() :
	started(true),
	thr(&WorkQueue::run, this),
	queue(),
	m() {}

/*
 * Destructor
 */
WorkQueue::~WorkQueue() {
	started = false;
	thr.join(); //wait until the thread stopped
}

int main() {

	WorkQueue wq;
	vector<decltype(wq.submit(packaged_task<string(void)>()))> futures;

	for(int i=0; i<10; ++i)
		futures.push_back(wq.submit(packaged_task<string(void)>([i]{  return "test" + to_string(i);   })));

	for (auto& f : futures)
		cout << f.get() << endl;

	cout << "Main thread id = " << this_thread::get_id() << endl;

	return 0;

}
