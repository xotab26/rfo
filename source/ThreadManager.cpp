#pragma once

#include <thread>
#include <memory>
#include "Utilities/Utilities.h"


class ThreadManager {
protected:
	class Thread {
	public:
		Thread(){}

		Thread(int _id, void(*func)(int)) {
			Log("Spawning new thread (id " + std::to_string(id = _id) + ")");
			auto _t = std::thread([func, _id]{ (*func)(_id); });
			_thread = std::make_shared<std::thread>(std::move(_t));
		}

		void join(){
			_thread->join();
		}

		int id;
	private:
		std::shared_ptr<std::thread> _thread;
	};

public:
	ThreadManager(){
		max_threads = std::thread::hardware_concurrency() * 2;
	}

	void start(){
		Threads = new Thread[max_threads];
		Log("Max usable threads " + std::to_string(max_threads));
	}

	int create(void(*func)(int)){
		int id = thread_count++;
		Threads[id] = Thread(id, func);
		return id;
	}

	int max_threads;
	int thread_count;
	Thread* Threads;
private:
};