#include "Config.hpp"
#include <openssl/sha.h>
#include <cstring>
#include "HashEngine.hpp"
using namespace std;

void    printHelp() {
    cout << "Expected usage: ./a.out [options] [hash]\n\n"
    "Options:\n"
    " -f or --file\tspecify a wordlist file\n"
    " -h or --help\tprint the man\n"
    " -a or --algo\tchoose algo (SHA256 or SHA1)\n"
    " -t or --thread\tchoose the number of thread to use\n"
    "\n";
}

int main(int argc, char **argv) {
    
    try {
        Config  config(argc, argv);

        if (config.getHelp()) {
            printHelp();
            return (0);
        }
        HashEngine  engine;
        engine.run(config);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
}
