#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "iostream"
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <fstream>

// TODO: adapt if other algo included
# define MAX_HASH_SIZE SHA256_DIGEST_LENGTH

class Config {
    public:
        Config(int argc, char **argv);
        ~Config();
        std::fstream &getWordList();
        unsigned char *getHash();
        bool    getHelp();
    
    private:
        std::fstream _wordList;
        unsigned char _hash[MAX_HASH_SIZE];
        unsigned int    _hashLength;
        bool    _help;
        // TO ADD: algorithm, multithreading
    
};

#endif