#include "../../inc/Server.hpp"

User::User(Server *server): Command(server) {
    
}

User::~User() {
    
}

void User::run(Client* client, std::list<std::string> args) {
    if (client->getState() == REGISTERED) {
        client->reply(Replies::ERR_ALREADYREGISTERED());
        return;
    }

    if (args.size() < 4) {
        client->reply(Replies::ERR_NEEDMOREPARAMS("USER"));
        return ;
    }

    if (client->getState() == UNREGISTERED) {
        client->reply(Replies::ERR_NOTREGISTERED());
        return;
    }

    if (client->getState() == NONICK) {
        client->reply(Replies::ERR_NONICKNAME());
        return;
    }
    
    std::string username = args.front();
    args.pop_front();
    std::string mode = args.front();
    args.pop_front();
    std::string unused = args.front();
    args.pop_front();
    std::string realname = args.front();
    args.pop_front();
    client->setUsername(username);
    client->setRealname(realname);
    client->setState(REGISTERED);
    client->welcomeToServer();
}