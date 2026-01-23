#include "HashEngine.hpp"
#include <cstring>


void    HashEngine::run(Config &config) {

    WorkerParams params;
    params.algorithm = config.getAlgo();
    params.digestLength = config.getAlgoDigestLength();
    std::memcpy(params.targetHash, config.getHash(), MAX_HASH_SIZE);

    SafeQueue   safeQueue;
    size_t  numThreads = config.getThread();
    std::string line;

    std::vector<std::thread>    workers;
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(&HashEngine::worker, this, std::ref(safeQueue), params, std::ref(found));
    }

    while (std::getline(config.getWordList(), line)) {
        
        if (found.load())
            break;

        if (!line.empty() && line.back() == '\r') line.pop_back();
        safeQueue.push(line);
    }
    safeQueue.setFinished();

    for (auto &t : workers) {
        t.join();
    }
    if (!found.load())
        std::cout << "Not found :(\n";
}

void    HashEngine::worker(SafeQueue &queue, WorkerParams params, std::atomic<bool>& found) {
    
    std::string str;

    while(queue.pull(str)) {

        if (found.load())
            return;

        unsigned char computedHash[params.digestLength];

        // Hash the line
        if (params.algorithm == Algo::SHA256) {
            SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), computedHash);
        } else if (params.algorithm == Algo::SHA1) {
                SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), computedHash);
        }
        // Comparaison
        if (std::memcmp(computedHash, params.targetHash, params.digestLength) == 0) {
            found.store(true);
            std::cout << "Found! The password is: " << str << std::endl;
            return;
        }
    }
    return;
}

HashEngine::HashEngine(): found(false) {}
HashEngine::~HashEngine() {}