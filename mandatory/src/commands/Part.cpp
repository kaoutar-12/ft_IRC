#include "../../inc/Server.hpp"

Part::Part(Server *server): Command(server) {
    
}

Part::~Part() {
    
}


void Part::run(Client* client, std::list<std::string> args) {
    if (args.size() < 1)
    {
        client->reply(Replies::ERR_NEEDMOREPARAMS("PART"));
        return ;
    }

    std::string channels = args.front();
    args.pop_front();
    std::list<std::string> channelList;

    std::istringstream channelStream(channels);
    std::string item;
    std::string comment;

    while (std::getline(channelStream, item, ',')) {
        channelList.push_back(item);
    }
    for (std::list<std::string>::iterator it = args.begin(); it != args.end();it++) {
        comment += " " + *it;
    }

    for (std::list<std::string>::iterator channelIter = channelList.begin(); channelIter != channelList.end(); ++channelIter) {
        std::string channelName = *channelIter;

        if (channelName.empty() || channelName[0] != '#') {
            client->reply(Replies::ERR_BADCHANMASK("PART"));
            continue;
        }
        server->partUser(channelName, client, this->server, comment, true);
    }
}