#include "Config.hpp"
#include <openssl/sha.h>
#include <cstring>
using namespace std;

void    printHelp() {
    cout << "Expected usage: ./a.out [options] [hash]\n\n"
    "Options:\n"
    " -f or --file\tspecify a wordlist file\n"
    " -h or --help\tprint the man\n"
    "\n";
}

int main(int argc, char **argv) {
    
    try {
        Config  config(argc, argv);
        string line;

        if (config.getHelp()) {
            printHelp();
            return (0);
        }

        while (getline(config.getWordList(), line)) {
            
            if (!line.empty() && line.back() == '\r') line.pop_back();
            
            unsigned char computedHash[SHA256_DIGEST_LENGTH];
            // Hash the line
            SHA256(reinterpret_cast<const unsigned char*>(line.c_str()), line.size(), computedHash);
            
            // Comparaison
            if (std::memcmp(computedHash, config.getHash(), SHA256_DIGEST_LENGTH) == 0) {
                cout << "Found! The password is: " << line << endl;
                return (0);
            }
        }
        cout << "Not found :(\n";
        return 0;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
}
