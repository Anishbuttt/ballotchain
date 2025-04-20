#include <iostream>
#include <asio.hpp>

using namespace std;
using asio::ip::tcp;

int main() {
    try {
        // Set up context
        asio::io_context io_context;

        // Resolve the server's address and port
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");

        // Create a socket and connect
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        cout << "✅ Connected to the server." << endl;

        // Prompt the user for their vote
        string vote;
        cout << "🗳️ Enter your vote: ";
        getline(cin, vote);

        // Send the vote to the server (add newline so server knows where to stop)
        vote += '\n';
        asio::write(socket, asio::buffer(vote));

        cout << "📤 Vote sent. Waiting for response..." << endl;

        // Receive response from the server
        string response;
        asio::read_until(socket, asio::dynamic_buffer(response), '\n');

        cout << "📩 Response from server: " << response << endl;
    }
    catch (exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
    }

    return 0;
}
