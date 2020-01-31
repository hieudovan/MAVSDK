#pragma once

#include <queue>
#include <mutex>
#include <memory>

namespace mavsdk {

template<class T> class LockedQueue {
public:
    LockedQueue(){};
    ~LockedQueue(){};

    void emplace_back(T&& item)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.emplace_back(std::forward<T>(item));
    }

    void push_back(T& item)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push_back(item);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size();
    }

    using iterator = typename std::deque<T>::iterator;
    iterator begin() { return _queue.begin(); }

    iterator end() { return _queue.end(); }

    iterator erase(iterator it) { return _queue.erase(it); }

    class Guard {
    public:
        Guard(LockedQueue& locked_queue) : _locked_queue(locked_queue)
        {
            _locked_queue._mutex.lock();
        }

        ~Guard() { _locked_queue._mutex.unlock(); }

        Guard(Guard& other) = delete;
        Guard(const Guard& other) = delete;
        Guard(Guard&& other) = delete;
        Guard(const Guard&& other) = delete;
        Guard& operator=(const Guard& other) = delete;
        Guard& operator=(Guard&& other) = delete;

        T* get_front()
        {
            if (_locked_queue._queue.size() == 0) {
                return nullptr;
            }
            return &_locked_queue._queue.front();
        }

        void pop_front() { _locked_queue._queue.pop_front(); }

    private:
        LockedQueue<T>& _locked_queue;
    };

private:
    std::deque<T> _queue{};
    std::mutex _mutex{};
};

} // namespace mavsdk
