#include "Utilities.h"
#include <thread>
#include <memory>


class ThreadManager {
public:
	class Thread {
	public:
		Thread(){}

		Thread(int _id, std::thread _t) {
			if (Config::DEBUG) Log("Spawning new thread (id " + std::to_string(id = _id) + ")");
			_thread = std::make_shared<std::thread>(std::move(_t));
		}

		Thread(int _id, void(*func)(int)) {
			if (Config::DEBUG) Log("Spawning new thread (id " + std::to_string(id = _id) + ")");
			auto _t = std::thread([func, _id]{ (*func)(_id); });
			_thread = std::make_shared<std::thread>(std::move(_t));
		}

		void join(){
			_thread->join();
		}

		void detach(){
			_thread->detach();
		}

		int id;
	private:
		std::shared_ptr<std::thread> _thread;
	};

	ThreadManager() {
		max_threads = std::thread::hardware_concurrency() * 2;
	}

	void start(){
		Threads = new Thread[max_threads];
		if (Config::DEBUG)
			Log("Maximum allowed threads = " + std::to_string(max_threads));
	}

	int create(std::thread _t) {
		int id = thread_count++;
		if (id < max_threads){
			Threads[id] = Thread(id, std::move(_t));
			return id;
		}
		else{
			Print::Error(-1, "You've reached the soft limit for concurrent threads!!");
			return -1;
		}
	}

	void join_thread(int thread_id){
		Threads[thread_id].join();
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
