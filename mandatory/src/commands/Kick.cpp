#include "../../inc/Server.hpp"

Kick::Kick(Server *server): Command(server) {
    
}

Kick::~Kick() {
    
}

void Kick::run(Client* client, std::list<std::string> args) {
    if (args.size() < 2)
    {
        client->reply(Replies::ERR_NEEDMOREPARAMS("KICK"));
        return ;
    }

    std::string channels = args.front();
    args.pop_front();
    std::string users;
    if (!args.empty()) {
        users = args.front();
        args.pop_front();
    }

    std::list<std::string> channelList;
    std::list<std::string> userList;

    std::istringstream channelStream(channels);
    std::istringstream users_stream(users);
    std::string item;
    std::string comment;
    std::string message;

    while (std::getline(channelStream, item, ',')) {
        channelList.push_back(item);
    }
    while (std::getline(users_stream, item, ',')) {
        userList.push_back(item);
    }
    for (std::list<std::string>::iterator it = args.begin(); it != args.end();it++) {
        comment += " " + *it;
    }
    if (channelList.size() == 1)
    {
        server->kickUser(channelList.front(), client, userList, this->server, comment);
        return ;
    }
    for (std::list<std::string>::iterator channelIter = channelList.begin(); channelIter != channelList.end(); ++channelIter) {
        std::string channelName = *channelIter;

        if (channelName.empty() || channelName[0] != '#') {
            client->reply(Replies::ERR_BADCHANMASK("JOIN"));
            continue;
        }
        if (userList.empty())
        {
            client->reply(Replies::ERR_NEEDMOREPARAMS("KICK"));
            return ;
        }
        std::string user = userList.front();
        userList.pop_front();
        server->kickUser(channelName, client, user, this->server, comment);
    }
}