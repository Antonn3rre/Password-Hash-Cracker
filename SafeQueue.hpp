#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <queue>
#include <condition_variable>
#include <mutex>

class   SafeQueue {
    public:
        SafeQueue();
        ~SafeQueue();
        void    push(std::string);
        bool    pull(std::string &);
        void    setFinished();

    private:


        bool    _finished;
        std::queue<std::string>   _queue;
        std::condition_variable  _cv;
        std::mutex   _mtx;
};

#endif