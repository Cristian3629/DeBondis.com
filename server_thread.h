#ifndef THREAD_H_
#define THREAD_H_

#include <thread>



class Thread{
protected:
	std::thread thread;
private:
	Thread(const Thread&) = delete;
	Thread& operator=(const Thread&) = delete;
public:
	Thread();
	Thread(Thread&& other);
	Thread& operator=(Thread&& other);
	void start();
	void join();
	virtual ~Thread();
	virtual void run() = 0;
};

#endif /*THREAD_H_*/
