#include "SafeQueue.hpp"

SafeQueue::SafeQueue(): _finished(false) {
}
SafeQueue::~SafeQueue() {}

void    SafeQueue::push(std::string str) {
    {
        // lock_guard safer than manual lock/unlock
        std::lock_guard<std::mutex> lock(_mtx);
        _queue.push(str);
    }
    // Automatic unlock with the end of local scope
    _cv.notify_one(); // Waking up 1 thread
}

bool    SafeQueue::pull(std::string &str) {
    std::unique_lock<std::mutex>    lock(_mtx);

    // Waits for a notification
    _cv.wait(lock, [this] {
        // Once woken up, check if there's a reason to continue
        // If queue is empty and finished false -> go back to wait
        return !_queue.empty() || _finished;
    });

    // Woke up and queue empty = finished
    if (_queue.empty()) {
        return false;
    }

    str = _queue.front();
    _queue.pop();
    return true;
}

void    SafeQueue::setFinished() {
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _finished = true;
    }
    _cv.notify_all();
}