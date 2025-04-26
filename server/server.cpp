#include <asio.hpp>
#include <iostream>
#include <sstream>
#include "../blockchain/blockchain.hpp"
using namespace std;
using asio::ip::tcp;

int main() 
{
    try 
    {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        Blockchain chain;
        std::cout << "Server is running on port 12345...\n";

        while (true) 
        {
                tcp::socket socket(io_context);
                acceptor.accept(socket);
                cout << "New client connected!\n";


            try
            {
                while(true)
                {
                    asio::streambuf buffer;
                    asio::read_until(socket, buffer, "\n");

                    std::istream input(&buffer);
                    std::string message;
                    std::getline(input, message);

                    if(message== "EXIT")
                    {
                        cout<< "client disconnected" << endl;
                        break;
                    }

                    std::cout << "Received: " << message << std::endl;

                    std::string response;
                    if (message.rfind("VOTE|", 0) == 0) 
                    {
                        std::istringstream iss(message);
                        std::string cmd, voter, candidate;
                        std::getline(iss, cmd, '|');
                        std::getline(iss, voter, '|');
                        std::getline(iss, candidate);

                        std::string voteData = "Voter: " + voter + ", Candidate: " + candidate;
                        chain.addBlock(voteData);
                        chain.printChain();  // optional: log the full chain

                        std::string response = "SUCCESS: Vote by " + voter + " recorded\n";
                        asio::write(socket, asio::buffer(response));
                        std::cout << "Sent response to client." << std::endl;

                    }  
                    else if (message.rfind("GET_CHAIN", 0) == 0) 
                    {
                        // Serialize and send full blockchain
                        std::ostringstream oss;
                        for (const auto& block : chain.getChain()) 
                        {
                            oss << block.toString() << "\n";
                        }
                        oss << "END_OF_CHAIN\n"; // delimiter
                        asio::write(socket, asio::buffer(oss.str()));

                    } 
                    else if (message.rfind("EXIT", 0) == 0) 
                    {
                        std::cout << "Client requested to exit.\n";
                        break;

                    } 
                    else 
                    {
                        std::string response = "ERROR: Unknown command\n";
                        asio::write(socket, asio::buffer(response));
                    }
                    //std::cout << "Client disconnected.\n";
                }
            } catch (std::exception& e)
            {
                std::cerr << "Client disconnected or error: " << e.what() << std::endl;
            }
        }
    } catch (std::exception& e) 
    {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}



/*cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="D:/SEM4/algorithm/ballotchain/vcpkg/scripts/buildsystems/vcpkg.cmake"
 cmake --build build  */