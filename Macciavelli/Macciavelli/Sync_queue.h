//
//  Sync_queue.h
//  adapted from an example from Bjarne Stroustrup
//

#ifndef __Sync_queue__
#define __Sync_queue__

#include <mutex>
#include <condition_variable>
#include <list>
#include <future>
#include <thread>

template<typename T>
class Sync_queue {
public:
    void put(const T& val)
    {
        std::lock_guard<std::mutex> lck {mtx};
        q.push_back(val);
        cond.notify_one();
		_queue_size++;
    }

    T get()
    {
        std::unique_lock<std::mutex> lck {mtx};
        cond.wait(lck, [this]{ return !q.empty(); });
        T val {q.front()};
        q.pop_front();
		_queue_size--;
        return val;
    }

	const size_t GetSize() const
	{
		return _queue_size;
	}

private:
    std::mutex mtx;
    std::condition_variable cond;
    std::list<T> q;
	size_t _queue_size = 0;
};

#endif /* defined(__Sync_queue__) */
