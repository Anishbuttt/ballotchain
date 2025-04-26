#include <asio.hpp>
#include <iostream>
#include <limits>

using asio::ip::tcp;

int main() 
{
    try 
    {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        std::cout << "Connected to BallotChain server." << std::endl;

        while (true) 
        {
            std::cout << "\n1. Cast Vote\n2. Exit\nChoice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 1)
            {
                std::string voter, candidate;
                std::cout << "Voter Name: ";
                std::getline(std::cin, voter);
                std::cout << "Candidate Name: ";
                std::getline(std::cin, candidate);

                std::string request = "VOTE|" + voter + "|" + candidate + "\n";
                asio::write(socket, asio::buffer(request));

                asio::streambuf response;
                asio::read_until(socket, response, "\n");
                std::istream input(&response);
                std::string reply;
                std::getline(input, reply);
                std::cout << "Server says: " << reply << std::endl;
            } 
            else if (choice == 2) 
            {
                std::string request = "GET_CHAIN\n";
                asio::write(socket, asio::buffer(request));

                // Read until END_OF_CHAIN marker
                asio::streambuf response;
                std::ostringstream chainData;
                while (true) 
                {
                    asio::read_until(socket, response, "\n");
                    std::istream input(&response);
                    std::string line;
                    std::getline(input, line);
                    if (line == "END_OF_CHAIN") break;
                    chainData << line << "\n";
                }
                std::cout << "--- Blockchain ---\n";
                std::cout << chainData.str();
                std::cout << "------------------\n";

            } 
            else 
            {
                // Send exit command to server and break
                std::string request = "EXIT\n";
                asio::write(socket, asio::buffer(request));
                break;
            }
        }
        
    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }

    return 0;
}