#include "../../inc/Server.hpp"

Nick::Nick(Server *server): Command(server) {
    
}

Nick::~Nick() {
    
}

void Nick::run(Client* client, std::list<std::string> args) {
    if (args.size() < 1)
    {
        std::cout << "args size: " << args.size() << std::endl;
        client->reply(Replies::ERR_NEEDMOREPARAMS("NICK"));
        return ;
    }

    if (client->getState() == UNREGISTERED) {
        client->reply(Replies::ERR_NOTREGISTERED());
        return;
    }

    std::string nickname = args.front();
    if (nickname.length() < 1 || nickname.length() > 9) {
        client->reply(Replies::ERR_NOSUCHNICK(nickname));
        return;
    }

    if (this->server->checkNickname(nickname)) {
        client->reply(Replies::ERR_NICKNAMEINUSE(nickname));
        return;
    }

    server->updateNickname(client, nickname);
    client->setNickname(nickname);
    if (client->getState() != REGISTERED) {
        client->setState(NICK);
    }
}