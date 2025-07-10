#include "../../inc/Server.hpp"

Invite::Invite(Server *server) : Command(server)
{
}

Invite::~Invite()
{
}

void Invite::run(Client* client, std::list<std::string> args)
{
	std::map<int, Client *>::iterator 	severClient;
	std::string							nickname;
	std::string							channelName;
	channel *						 	Channel;

	
	if(args.empty())
	{
		client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
		return ;
	}
	if (*args.begin() == "INVITE")
	{
		client->reply(Replies::RPL_INVITELIST(client->getNickname(), client->getInvitingChannels()));
		return ;
	}
	{
		nickname = args.front();
		if (server->getMember(nickname) == NULL)
		{
			client->reply(Replies::ERR_NOSUCHNICK(nickname));
			return ;
		}
		if (server->getMember(nickname) == client)
		{
			client->reply(Replies::ERR_CANTINVITESELF(nickname));
			return ;
		}
		args.pop_front();
		if(args.empty())
		{
			client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
			return ;
		}
		channelName = args.front();
		if ((Channel = server->getChannel(channelName)) == NULL)
		{
			client->reply(Replies::ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
			return ;
		}
		args.pop_front();
		if (Channel->getMembers().find(client->getNickname()) == Channel->getMembers().end())
		{
			client->reply(Replies::ERR_NOTONCHANNEL(client->getNickname(), channelName));
			return ;
		}
		Channel->addInvite(client, server->getMember(nickname));
	}
}