#include "../../inc/Server.hpp"

Join::Join(Server *server): Command(server) {
    
}

Join::~Join() {
    
}

void Join::run(Client* client, std::list<std::string> args) {
    if (args.empty()) {
        client->reply(Replies::ERR_NEEDMOREPARAMS("JOIN"));
        return;
    }
    if (args.size() > 2)
    {
        client->reply(Replies::ERR_BADCHANMASK("JOIN"));
        return;
    }
    std::string channels = args.front();
    args.pop_front();
    std::string keys;
    if (!args.empty()) {
        keys = args.front();
        args.pop_front();
    }

    std::list<std::string> channelList;
    std::list<std::string> keyList;

    std::istringstream channelStream(channels);
    std::istringstream keyStream(keys);
    std::string item;

    while (std::getline(channelStream, item, ',')) {
        channelList.push_back(item);
    }

    while (std::getline(keyStream, item, ',')) {
        keyList.push_back(item);
    }

    std::list<std::string>::iterator keyIter = keyList.begin();

    for (std::list<std::string>::iterator channelIter = channelList.begin(); channelIter != channelList.end(); ++channelIter) {
        std::string channelName = *channelIter;

        if (channelName.empty() || channelName[0] != '#' || channelName == "#") {
            client->reply(Replies::ERR_BADCHANMASK("JOIN"));
            continue;
        }

        std::string key;
        if (keyIter != keyList.end()) {
            key = *keyIter;
            ++keyIter;
        }

        server->joinChannel(channelName, client, key);
    }
}
