**Simple C++ SHA-256 Hash Cracker**

This project is designed for educational purposes to demonstrate how password hashing works and why weak passwords are easy to crack.

**Usage:**

    ./a.out <wordlist_path> <target_hash>
Example:

    ./hash_cracker rockyou.txt 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8

**How it works:**
1. The program takes a plain-text wordlist and a target hash.
2. It reads the wordlist line by line.
3. For each word, it computes the SHA-256 hash.
4. It compares the generated hash with the target hash provided by the user.
5. If they match, the password is recovered.

Future improvements:
- Default file if none specified
- Option to use another algorithm
- Multithreading to handle larger wordlist files quickly
- Add chrono + options to print it