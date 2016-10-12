#include "server_thread.h"
#include <iostream> //cout

Thread::Thread(){}

Thread::~Thread(){}

void Thread::join(){
	thread.join();
}

void Thread::start(){
	thread = std::thread(&Thread::run, this);
}

//move constructor
Thread::Thread(Thread&& other){
	this->thread = std::move(other.thread);
}


Thread& Thread::operator=(Thread&& other) {
	this->thread = std::move(other.thread);
	return *this;
}
