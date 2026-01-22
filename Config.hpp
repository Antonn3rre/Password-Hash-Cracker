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
        std::fstream &getWordList();
        unsigned char *getHash();
        bool    getHelp();
        Algo    getAlgo();
        size_t  getAlgoDigestLength();
    
    private:
        std::fstream _wordList;
        unsigned char _hash[MAX_HASH_SIZE];
        unsigned int    _hashLength;
        bool    _help;
        Algo _algorithm;
        size_t  _algoDigestLength;
        // TO ADD: multithreading
};

#endif