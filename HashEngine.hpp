#ifndef HASH_ENGINE_HPP
#define HASH_ENGINE_HPP

#include "SafeQueue.hpp"
#include <atomic>
#include <thread>
#include "Config.hpp"

struct WorkerParams {
    Algo algorithm;
    size_t digestLength;
    unsigned char targetHash[MAX_HASH_SIZE];
};

class   HashEngine {
    public:
        void    run(Config &);
        HashEngine();
        ~HashEngine();

    private:

        void    worker(SafeQueue &queue, WorkerParams, std::atomic<bool>& found);
        std::atomic<bool>    found;
        std::vector<std::thread>  threads;
};


#endif