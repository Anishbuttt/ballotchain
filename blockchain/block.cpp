#include "block.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <ctime>
#include<iomanip>

//#include <openssl/sha.h>

using namespace std;

Block::Block(int idx, const std::string& prevHash, const std::string& data)
    : index(idx), previousHash(prevHash), data(data), timestamp(std::time(0)) {
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << previousHash << data << timestamp;
    std::string toHash = ss.str();

    // Placeholder for real hash logic (or plug in SHA256)
    return std::to_string(std::hash<std::string>{}(toHash));
}

std::string Block::getHash() const {
    return hash;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}

std::string Block::getData() const {
    return data;
}



void Block::printBlock() const {
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Block Index: " << index << std::endl;
    std::cout << "Timestamp: " << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "Data: " << data << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Previous Hash: " << previousHash << std::endl;
    std::cout << "----------------------------------" << std::endl;
}


int main() {
    Block b1(0, "0", "Vote: Alice");
    b1.printBlock();

    Block b2(1, b1.getHash(), "Vote: Bob");
    b2.printBlock();

    return 0;
}