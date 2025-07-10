#include "../../inc/Server.hpp"

Mode::Mode(Server *server) : Command(server) {
	
}

Mode::~Mode()
{

}


void Mode::run(Client *client, std::list<std::string> args)
{
	std::map<char, bool>		changedModes;
	std::string					channelName;
	std::string					modeString;
	std::string					modeReply;
	channel*					Channel;
	bool						adding;

	if (modeArgument['k'].empty() && modeArgument['l'].empty() && modeArgument['o'].empty())
	{
		modeArgument['k'] = "";
		modeArgument['l'] = "";
		modeArgument['o'] = "";
		changedModes['i'] = false;
		changedModes['k'] = false;
		changedModes['l'] = false;
		changedModes['o'] = false;
		changedModes['t'] = false;
		modeReply = std::string("MODE ");
	}
	if (args.empty() || *args.begin() == "MODE")
	{
		client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
		return;
	}
	if (args.front()[0] == '#')
	{
		channelName = args.front();
		Channel = server->getChannel(args.front());
		if (!Channel)
		{
			client->reply(Replies::ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
			return ;
		}
		if (!Channel->isMember(client->getNickname()))
		{
			client->reply(Replies::ERR_NOTONCHANNEL(client->getNickname(), channelName));
			return ;
		}
		args.pop_front();
		if (args.empty())
		{
			server->replyChannelModIs(channelName, client);
			return ;
		}
	}
	else
	{
		client->reply(Replies::ERR_NOSUCHCHANNEL(client->getNickname(), args.front()));
		return ;
	}
	{
		adding = args.front()[0] != '-';
		modeReply += (adding ? "+" : "-");
		modeString = args.front();
		if (modeString.length() <= 1)
		{
			client->reply(Replies::ERR_NEEDMOREPARAMS(modeString));
			return;
		}
		args.pop_front();
	}
	for (int i = 1; modeString[i]; i++)
	{
		char mode = modeString[i];
		switch (mode)
		{
			case 'i':
			{
				if (server->setInviteOnlyChannel(channelName, client, adding))
				{
					changedModes['i'] = true;
				}
				else
					return ;
				break ;
			}
			case 't':
			{
				if (server->setTopicRestrictedChannel(channelName, adding, client))
					changedModes['t'] = true;
				else
					return ;
				break ;
			}
			case 'k':
			{
				if (args.empty() && adding)
				{
					client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
					return ;
				}
				else if (server->setPasswordChannel(channelName, adding ? args.front() : "", client))
				{
					if (adding)
					{
						modeArgument['k'] = args.front();
						args.pop_front();
					}
					changedModes['k'] = true;
				}
				else
					return ;
				break ;
			}
			case 'l':
			{
				if (args.empty() && adding)
				{
					client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
					return ;
				}
				else if (server->setUserLimitChannel(channelName, adding, (adding ? args.front() : "-1"), client))
				{
					modeArgument['l'] = adding ? args.front() : "-1";
					adding ? args.pop_front() : void();
					changedModes['l'] = true;
				}
				else
					return ;
				break ;
			}
			case 'o':
			{
				if (changedModes['o'] == true)
				{
					std::cout << "I allow one user at a time!\n";
					break ;
				}
				if (args.empty())
				{
					client->reply(Replies::ERR_NEEDMOREPARAMS("MODE"));
					return ;
				}
				else if (server->setOperatorChannel(channelName, args.front(), adding, client))
				{
					modeArgument['o'] = args.front();
					changedModes['o'] = true;
					args.pop_front();
				}
				else
					return ;
				break ;
			}
			default :
			{
				client->reply(Replies::ERR_UNKNOWNMODE(client, mode));
				return ;
			}
		}
		if (!adding)
			break ;
	}
	for (std::map<char, bool>::iterator change = changedModes.begin(); change != changedModes.end(); change++)
	{
		if (change->second)
		{
			modeReply += change->first;
		}
	}
	int space_cord = 0;
	while (modeReply[space_cord] && modeReply[space_cord] != ' ')
		space_cord++;
	for (int i = 0; i < (int)modeReply.size() && i < space_cord; i++)
	{
		if ((modeReply[i] == 'k' || modeReply[i] == 'l') && adding)
			modeReply += " " + modeArgument[modeReply[i]];
		if (modeReply[i] == 'o')
		{
			modeReply += " " + modeArgument[modeReply[i]];
			break ;
		}
	}
	server->broadcastArgsReply(channelName, modeReply);
}
