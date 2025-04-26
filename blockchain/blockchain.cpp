#include "blockchain.hpp"
#include <iostream>

Blockchain::Blockchain() {
    chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    return Block(0, "0", "Genesis Block");
}

Block Blockchain::getLastBlock() const {
    return chain.back();
}

void Blockchain::addBlock(const std::string& data) {
    int newIndex = chain.size();
    std::string prevHash = getLastBlock().getHash();
    Block newBlock(newIndex, prevHash, data);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i];
        const Block& previous = chain[i - 1];

        // Check if current block is valid
        if (!current.isValid()) return false;

        // Check if current block links to previous
        if (current.getPreviousHash() != previous.getHash()) return false;
    }
    return true;
}

void Blockchain::printChain() const {
    for (const auto& block : chain) {
        block.printBlock();
    }
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}