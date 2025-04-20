#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main() {
    try {
        // Create an io_context
        asio::io_context io_context;

        // Create a TCP endpoint (IP and port)
        tcp::endpoint endpoint(tcp::v4(), 12345);

        // Create the acceptor to listen for connections
        tcp::acceptor acceptor(io_context, endpoint);

        std::cout << "🚀 Server is running and waiting for a connection on port 12345..." << std::endl;

        // Wait for a client to connect
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        std::cout << "✅ Client connected!" << std::endl;

        // Read message from the client
        std::string vote;
        asio::read_until(socket, asio::dynamic_buffer(vote), '\n');

        std::cout << "🗳️ Received vote from client: " << vote;

        // Prepare and send response
        std::string response = "✅ Vote received: " + vote;
        asio::write(socket, asio::buffer(response));

        std::cout << "📨 Response sent to client." << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
    }

    return 0;
}
