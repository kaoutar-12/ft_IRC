#include "../../inc/Server.hpp"

Weather::Weather(Server *server): Command(server) {
}

Weather::~Weather() {
}


void Weather::run(Client* client, std::list<std::string> args) {
    if (args.empty()) {
        client->reply(Replies::ERR_NEEDMOREPARAMS("WEATHER"));
        return;
    }
	if (args.size() > 1) 
	{
		client->reply(Replies::ERR_TOOMANYARGUMENTS("WEATHER"));
		return;
	}

    std::string city = args.front();
    Client *c = server->getClientByNickname("bot");
    if (c) {
        std::cout << "fetching weather for " << city << std::endl;
        c->reply("WEATHER " + client->getNickname() + " " + city);
    }
    else
        client->reply(Replies::RPL_BOTNOTREGISTERED());
    return ;
}
    