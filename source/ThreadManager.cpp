#pragma once

#include <thread>
#include <memory>
#include "Utilities/Utilities.h"


class ThreadManager {
protected:
	class Thread {
	public:
		Thread(){}

		Thread(int _id, void(*func)()) {
			Log("Spawning new thread (id " + std::to_string(id = _id) + ")");
			auto _t = std::thread([func]{ (*func)(); });
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
	void start(){
		Threads = new Thread[max_threads = std::thread::hardware_concurrency()];
		Log("Max usable threads " + std::to_string(max_threads));
	}

	int create(void(*func)()){
		int id = thread_count++;
		Threads[id] = Thread(id, func);
		return id;
	}

	int max_threads;
	int thread_count;
	Thread* Threads;
private:
};
