	#include "../../inc/Server.hpp"

	PrivMsg::PrivMsg(Server *server): Command(server) {
		
	}

	PrivMsg::~PrivMsg() {
		
	}

	void PrivMsg::run(Client* client, std::list<std::string> args) {
		if (args.size() < 2)
		{
			client->reply(Replies::ERR_NEEDMOREPARAMS("PRIVMSG"));
			return ;
		}

		std::string channels = args.front();
		args.pop_front();
		std::list<std::string> channelList;

		std::istringstream channelStream(channels);
		std::string item;

		while (std::getline(channelStream, item, ',')) {
			channelList.push_back(item);
		}
		std::string message;
		for (std::list<std::string>::iterator it = args.begin(); it != args.end(); ++it)
			message += " " + *it;
		message.erase(0, message.find_first_not_of(' '));
		for (std::list<std::string>::iterator channelIter = channelList.begin(); channelIter != channelList.end(); ++channelIter) {
			std::string channelName = *channelIter;

			if (channelName.empty() || channelName == "#")
			{
				client->reply(Replies::ERR_NORECIPIENT(client->getNickname()));
				return ;
			}
			if (channelName[0] == '#')
				server->broadcast(channelName, client, message, server);
			else
				server->direct_message(channelName, client, message, server);

		}
	}