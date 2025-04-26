#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "block.hpp"
#include <vector>
using namespace std;

class Blockchain {
private:
    std::vector<Block> chain;
    Block createGenesisBlock();

public:
    Blockchain();

    void addBlock(const std::string& data);
    Block getLastBlock() const;
    bool isChainValid() const;
    void printChain() const;
    const vector<Block>& getChain() const;
};

#endif
