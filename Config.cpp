#include "Config.hpp"
#include <vector>
#include <stdexcept>

std::fstream    openWordsList(std::string path) {
    std::fstream WordsList(path);

    // Check if WordsList is open
    if (!WordsList.is_open()) {
        throw std::runtime_error("Error while opening words list file.");
    }
    return WordsList;
}

Config::Config(int argc, char **argv): _algorithm(Algo::SHA256) {

    _hashLength = 0;
    std::vector<std::string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); i++) {

        // Option to specify wordlist file
        if (args[i] == "-f" || args[i] == "--file") {
            if (i + 1 < args.size()) {
                _wordList = openWordsList(args[++i]);
            } else {
                throw std::runtime_error("Option -f requires a filename.");
            }
        // Option to print a man
        } else if (args[i] == "-h" || args[i] == "--help") {
            _help = true;
            return ;
        // Option to choose an alogrithm
        } else if (args[i] == "-a" || args[i] == "--algo") {
            if (i + 1 < args.size()) {
                if (args[++i] == "SHA256") {
                    _algorithm = Algo::SHA256;
                    _algoDigestLength = SHA256_DIGEST_LENGTH;
                } else if (args[i] == "SHA1") {
                    _algorithm = Algo::SHA1;
                    _algoDigestLength = SHA_DIGEST_LENGTH;
                } else {
                    throw std::runtime_error("Unknown algorithm");
                }
            } else {
                throw std::runtime_error("Option -a requires an argument");
            }
        }
        else {
            // retrieve the hash given
            if (_hashLength) {
                _help = true;
                return ;
            }
            
            // Check input size
            if (args[i].length() % 2 != 0)
                throw std::runtime_error("Hash length must be even");
            if (args[i].length() / 2 > MAX_HASH_SIZE)
                throw std::runtime_error("Hash too long");

            // Convert text hash to hexa and store it in _hash
            for (size_t j = 0; j < args[i].length() / 2; j++) {
                std::string byteString = args[i].substr(j * 2, 2);
                _hash[j] = static_cast<unsigned char>(std::strtol(byteString.c_str(), nullptr, 16));
            }
            // Store _hash length
            _hashLength = args[i].length() / 2;
        }
    }
    // Default wordlist file if none specified
    if (!_wordList.is_open()) {
        _wordList = openWordsList(std::string("rockyou.txt"));
    }
    // If no hash given: send an error
    if (!_hashLength)
        throw std::runtime_error("Missing arguments"); 
    
    // Check if the hash size and the choosed algo correponds
    if (_algorithm == Algo::SHA256 && _hashLength != SHA256_DIGEST_LENGTH) {
            throw std::runtime_error("Hash buffer size mismatch!");
    } else if (_algorithm == Algo::SHA1 && _hashLength != SHA_DIGEST_LENGTH) {
            throw std::runtime_error("Hash buffer size mismatch!");
    }
}

Config::~Config() {
    _wordList.close();
}

std::fstream &Config::getWordList() {
    return _wordList;
}
unsigned char *Config::getHash() {
    return _hash;
}
bool    Config::getHelp() {
    return _help;
}
Algo    Config::getAlgo() {
    return _algorithm;
}
size_t  Config::getAlgoDigestLength() {
    return _algoDigestLength;
}