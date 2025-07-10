#include "../../inc/Server.hpp"

Quit::Quit(Server *server): Command(server) {
    
}

Quit::~Quit() {
    
}

void Quit::run(Client* client, std::list<std::string> args) {
    std::string message;
    for (std::list<std::string>::iterator it = args.begin(); it != args.end();it++) {
        message += *it + " ";
    }
    server->quitUser(client, message, this->server, true);
}