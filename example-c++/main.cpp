#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

struct TransactionData {
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};

class Block {
    private:
        int index;
        size_t blockHash;
        size_t previousHash;
        size_t generateHash();

    public:
        Block(int idx, TransactionData d, size_t prevHash);
        size_t getHash();
        size_t getPreviousHash();
        TransactionData data;
        bool isHashValid();
};

Block::Block(int idx, TransactionData d, size_t prevHash){
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

size_t Block::generateHash(){
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

    return finalHash(hash1(toHash) + hash2(previousHash));
}

size_t Block::getHash(){
    return blockHash;
}

size_t Block::getPreviousHash(){
    return previousHash;
}

bool Block::isHashValid(){
    return generateHash() == blockHash;
}

class Blockchain{
    private: 
        Block createGenesisBlock();
    public:
        vector<Block> chain;
        Blockchain();
        void addBlock(TransactionData data);
        bool isChainValid();

        //demo
        Block *getLastestBlock();
};

Blockchain::Blockchain(){
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock(){
    time_t current;
    TransactionData d;
    d.amount = 0;
    d.receiverKey = "None";
    d.senderKey = "None";
    d.timestamp = current;

    hash<int> hash1;
    Block genesis(0, d, hash1(0));
    return genesis;
}

//bad - only demo
Block *Blockchain::getLastestBlock(){
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d){
    int index = (int)chain.size() - 1;
    Block newBlock(index, d, getLastestBlock()->getHash());
}

bool Blockchain::isChainValid(){
    vector<Block>::iterator it;
    int chainLen = (int)chain.size();

    for(it=chain.begin(); it!= chain.end(); ++it){
        Block currentBlock = *it;
        if(!currentBlock.isHashValid()){
            //invalid
            return false;
        }
        if(chainLen > 1){
            Block previousBlock = *(it-1);
            if(currentBlock.getPreviousHash() != previousBlock.getHash()){
                //invalid
                return false;
            }
        }
    }
    return true;
}

int main(){
    //start 
    Blockchain AwesomeCoin;

    //data for 1th block
    TransactionData data;
    time_t dataTime;
    data.amount = 1.5;
    data.receiverKey = "Joe";
    data.senderKey = "Sally";
    data.timestamp = time(&dataTime);

    AwesomeCoin.addBlock(data);

    cout << "Is chain valid?" << "\n" << AwesomeCoin.isChainValid() << "\n";
    
    //data for 2th block
    TransactionData data2;
    time_t dataTime2;
    data2.amount = 0.004;
    data2.receiverKey = "Marta";
    data2.senderKey = "Fred";
    data2.timestamp = time(&dataTime2);

    AwesomeCoin.addBlock(data2);

    cout << "Now is chain valid?" << "\n" << AwesomeCoin.isChainValid() << "\n";

    Block *hackBlock = AwesomeCoin.getLastestBlock();
    hackBlock->data.amount = 10000;
    hackBlock->data.receiverKey = "Jon";

    cout << "Now is the chain still valid? \n" << AwesomeCoin.isChainValid() << "\n";
    
    return 0;
}
