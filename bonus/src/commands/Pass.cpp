#include "../../inc/Server.hpp"

Pass::Pass(Server *server): Command(server) {
    
}

Pass::~Pass() {

}

void Pass::run(Client* client, std::list<std::string> args) {
    if (client->getState() == REGISTERED) {
        client->reply(Replies::ERR_ALREADYREGISTERED());
        return ;
    }

    if (args.size() < 1)
    {
        client->reply(Replies::ERR_NEEDMOREPARAMS("PASS"));
        return ;
    }

    std::string uncheckedPassword = args.front();
    std::string password;

    if (uncheckedPassword[uncheckedPassword.length() - 1] == '\r') {
        password = args.front().substr(0, args.front().length() - 1);
    } else {
        password = args.front().substr(0, args.front().length());
    }

    if (this->server->getPass() != password) {
        client->reply(Replies::ERR_PASSWDMISMATCH(client->getNickname()));
        return;
    }

    client->setState(NONICK);
}
