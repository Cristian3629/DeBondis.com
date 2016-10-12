#ifndef THREAD_H_
#define THREAD_H_

#include <thread>



class Thread{
private:
	std::thread thread;
	Thread(const Thread&) = delete;
	Thread& operator=(const Thread&) = delete;
	Thread(Thread&& other);
	Thread& operator=(Thread&& other);
public:
	Thread();
	void start();
	void join();
	virtual ~Thread();
	virtual void run() = 0;
};

#endif /*THREAD_H_*/
