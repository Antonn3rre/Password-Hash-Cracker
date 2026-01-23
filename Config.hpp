#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "iostream"
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <fstream>

// TODO: adapt if other algo included
# define MAX_HASH_SIZE SHA256_DIGEST_LENGTH

enum class Algo {
    SHA256,
    SHA1
};

class Config {
    public:
        Config(int argc, char **argv);
        ~Config();
        Config &operator=(Config &);
        Config(Config &);
        std::fstream &getWordList();
        const unsigned char *getHash() const;
        const bool    getHelp() const;
        const Algo    getAlgo() const;
        const size_t  getAlgoDigestLength() const;
        const size_t  getThread() const;
    
    private:
        std::fstream _wordList;
        unsigned char _hash[MAX_HASH_SIZE];
        unsigned int    _hashLength;
        bool    _help;
        Algo _algorithm;
        size_t  _algoDigestLength;
        size_t  _thread;
};

#endif