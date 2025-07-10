#include "inc/Server.hpp"
#include <cctype>


void printError(const std::string& message) {
    std::cerr << "\033[1;31mError: " << message << "\033[0m" << std::endl;
}

bool isNumeric(const std::string& str) {
    for (unsigned long i = 0; i < str.size(); i++) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void printPortRanges() {
    std::cout << "Port Ranges and Use Cases:\n"
              << "+-------------------------+-------------------------------------------------------------+\n"
              << "| Range                   | Use Cases                                                   |\n"
              << "+-------------------------+-------------------------------------------------------------+\n"
              << "| Well-Known Ports        | Reserved for standard services (HTTP, FTP, SSH)             |\n"
              << "|                         | Range: 0-1023                                               |\n"
              << "+-------------------------+-------------------------------------------------------------+\n"
              << "| Registered Ports        | Used by registered applications and services                |\n"
              << "|                         | Range: 1024-49151                                           |\n"
              << "+-------------------------+-------------------------------------------------------------+\n"
              << "| Dynamic or Private Ports| Ephemeral ports for temporary use                           |\n"
              << "|                         | Range: 49152-65535                                          |\n"
              << "+-------------------------+-------------------------------------------------------------+\n";
}

int main(int ac, char **av)
{
    try{
        if (ac != 3)
            throw std::runtime_error("Usage: /ircserv <port> <password>");
        if (!isNumeric(av[1])) {
            printError("Port number should be numeric.");
            return 1;
        }
        int port = std::atoi(av[1]);
        if (port < 1024 || port > 65535) {
            printError("Port number out of valid range.");
            printPortRanges();
            return 1;
        }
        std::string password = av[2];
        Server _server(av[1], password);
        _server.start();
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
} 	