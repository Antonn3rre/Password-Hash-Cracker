#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
    
    // Check input
    if (argc != 3) {
        cout << "Wrong number of arguments\n"
        << "Expected ./a.out [words file] [hashed password]\n";
        return (0) ;
    }

    string line;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    // Open WordsList file
    fstream WordsList(argv[1]);

    // Check if WordsList is open
    if (!WordsList.is_open()) {
        std::cout << "Error while opening words list file\n";
        return (0);
    }

    while (getline(WordsList, line)) {
        
        if (!line.empty() && line.back() == '\r') line.pop_back();
        
        // Hash the line
        SHA256(reinterpret_cast<const unsigned char*>(line.c_str()), line.size(), hash);
        
        // Convert binary to string hexa
        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        string currentHashStr = ss.str();

        // Comparaison
        if (currentHashStr == argv[2]) {
            cout << "Found! The password is: " << line << endl;
            WordsList.close();
            return (0);
        }
    }
    cout << "Not found :(\n";
    WordsList.close();
    return 0;
}
