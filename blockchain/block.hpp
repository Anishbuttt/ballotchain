#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <ctime>

class Block {
private:
    int index;
    std::string previousHash;
    std::string hash;
    std::string data;
    std::time_t timestamp;

public:
    Block(int idx, const std::string& prevHash, const std::string& data);

    std::string calculateHash() const;
    std::string getHash() const;
    std::string getPreviousHash() const;
    std::time_t getTimestamp() const;
    std::string getData() const;

    bool isValid() const;
    void printBlock() const;

    std::string toString() const;

};

#endif
