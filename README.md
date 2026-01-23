**Simple C++ Hash Cracker**

This project is designed for educational purposes to demonstrate how password hashing works and why weak passwords are easy to crack.
For the moment, it can handle SHA256 and SHA1 hashed words. 

**Usage:**

    make
    ./passwd_hash_cracker <target_hash>
Example:

    ./passwd_hash_cracker 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8 [-f filePath] [-h] [-a algo] [-t threadNum]

**How it works:**
1. The program takes a target hash.
2. It reads the wordlist line by line.
3. For each word, it computes the SHA-256 hash.
4. It compares the generated hash with the target hash provided by the user.
5. If they match, the password is recovered.

**Options**
- --file (-f): specify a file path. "rockyou.txt" is used if none specified
- --help (-h): prints the man
- --algo (-a): choose algorithm. SHA256 is the default algorithm
- --thread (-t): choose the number of thread to use

**Future improvements:**
- Other algorithm
- Multithreading to handle larger wordlist files quickly
- Add chrono + options to print it
