#include "block.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

using namespace std;

Block::Block(int idx, const string& prevHash, const string& data)
    : index(idx), previousHash(prevHash), data(data), timestamp(std::time(nullptr)) {
    hash = calculateHash();
}

string Block::calculateHash() const {
    stringstream ss;
    ss << index << previousHash << data << timestamp;
    string input = ss.str();

    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hashResult);

    std::stringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        hexStream << hex << setw(2) << setfill('0') << static_cast<int>(hashResult[i]);

    return hexStream.str();
}

string Block::getHash() const {
    return hash;
}

string Block::getPreviousHash() const {
    return previousHash;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}

std::string Block::getData() const {
    return data;
}

bool Block::isValid() const {
    return hash == calculateHash();
}

void Block::printBlock() const {
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Block Index: " << index << std::endl;
    std::cout << "Timestamp: " << std::put_time(localtime(&timestamp), "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "Data: " << data << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Previous Hash: " << previousHash << std::endl;
    std::cout << "Valid: " << (isValid() ? "Yes" : "No") << std::endl;
    std::cout << "----------------------------------" << std::endl;
}


string Block::toString() const {
    ostringstream ss;
    ss << "Index: " << index
       << " | Timestamp: " << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S")
       << " | Data: " << data
       << " | Hash: " << hash
       << " | PrevHash: " << previousHash;
    return ss.str();
}