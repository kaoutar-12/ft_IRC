#include "../inc/Server.hpp"


channel::channel() {

}
channel::channel(Client *client, std::string name, std::string key, std::string topic) : name(name), topic(topic), key(key), inviteOnly(false), topicRestricted(false), userLimit(-1)
{
    creator = client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    creationTime = std::time(nullptr);
    addMember(client->getNickname(), client);
    addOperator(client->getNickname(), client);
}
channel::~channel() {

}

void channel::setKey(std::string key) {
    this->key = key;
}
std::string &channel::getKey() {
    return (this->key);
}

void channel::setTopic(std::string topic) {
    this->topic = topic;
}

std::string &channel::getTopic() {
    return (this->topic);
}
void channel::setUsersLimit(int limit) {
    this->userLimit = limit;
}

int channel::getUsersLimit() {
    return (this->userLimit);
}

void channel::setInviteOnly(bool inviteOnly) {
    this->inviteOnly = inviteOnly;
}

bool channel::getInviteOnly() {
    return (this->inviteOnly);
}

void channel::setTopicRestricted(bool topicRestricted) {
    this->topicRestricted = topicRestricted;
}

bool channel::getTopicRestricted() {
    return (this->topicRestricted);
}

std::string channel::getCreator() {
    return (this->creator);
}

std::map<std::string, Client *>& channel::getMembers() {
    return (this->members);
}

std::vector<std::string>& channel::getOperators() {
    return (this->operators);
}

std::time_t channel::getCreationTime() {
    return (this->creationTime);
}

bool channel::isMember(std::string name) {
    for (std::map<std::string, Client *>::iterator it = members.begin();it != members.end();it++)
    {
        if (it->second->getNickname() == name)
        {
            return true;
        }
    }
    return false;
}

bool channel::isOperator(std::string name) 
{
	for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end();it++)
	{
		if (*it == name)
			return (true);
	}
	return (false);
}

bool channel::addMember(std::string name, Client *client) {
    if (isMember(name) == true)
	{
        client->reply(Replies::ERR_ALREADYINCHANNEL(client->getNickname()));
		return (false);
	}
    else
        members.insert(std::make_pair(client->getNickname(), client));
	return (true);
}

std::string channel::getChannelName()
{
	return (this->name);
}

bool channel::addOperator(std::string name, Client *client) 
{
	if (!isOperator(name))
	{
		operators.push_back(name);
		return (true);
	}
	else
		client->reply(Replies::ERR_ALREADYOPERATOR(name));
	return (false);
}

bool channel::removeOperator(std::string name, Client *client) 
{
    if (isOperator(name))
	{
        operators.erase(std::remove(operators.begin(), operators.end(), name), operators.end());
		return (true);
	}
    else
        client->reply(Replies::ERR_CHANOPRIVSNEEDED(this->name, name));
	return (false);
}

void channel::addInvite(Client *client, Client *invitedClient)
{
	if (invitedClient->getInvitingChannel(this->name))
	{
		client->reply(Replies::RPL_INVITING(this->name, client, invitedClient, 2));
		return ;
	}
	if (this->isMember(invitedClient->getNickname()))
	{
		client->reply(Replies::ERR_USERONCHANNEL(client, this->name));
		return ;
	}
	if (this->inviteOnly)
	{
		if (this->isOperator(client->getNickname()))
		{
			invitedMembers.push_back(invitedClient->getNickname());
			invitedClient->addInvitingChannel(this);
			client->reply(Replies::RPL_INVITING(this->name, client, invitedClient, 1));
			invitedClient->reply(Replies::RPL_INVITING(this->name, client, invitedClient, 0));
		}
		else
		{
			client->reply(Replies::ERR_CHANOPRIVSNEEDED(this->name, client->getNickname()));
			return ;
		}
	}
	else
	{
		this->invitedMembers.push_back(invitedClient->getNickname());
		invitedClient->addInvitingChannel(this);
		client->reply(Replies::RPL_INVITING(this->name, client, invitedClient, 1));
		invitedClient->reply(Replies::RPL_INVITING(this->name, client, invitedClient, 0));
		for(std::vector<std::string>::iterator it = invitedMembers.begin(); it != invitedMembers.end(); it++)
			std::cout << *it << std::endl;
	}
}

bool channel::isCreator(Client *client)
{
	std::string clientName;

	clientName = client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
	if (clientName == this->getCreator())
		return (true);
	return (false);
}

Client*	channel::getClient(std::string name)
{
	std::map<std::string, Client*>::iterator it;
	for (it = this->members.begin(); it != this->members.end(); it++)
	{
		if (it->second->getNickname() == name)
			return (it->second);
	}
	return (NULL);
}

std::vector<std::string>	channel::getInvitedMembers()
{
	return (this->invitedMembers);
}

void channel::broadcastReply(std::string reply)
{
	for (std::map<std::string, Client *>::iterator it = this->members.begin(); it != this->members.end();
	it++)
	{
		it->second->reply(reply);
	}
}

std::string channel::getSetTopicSetter(std::string topicSetter)
{
	if (topicSetter == "")
		return (this->topicSetter);
	else
	{
		this->topicSetter = topicSetter;
		return (this->topicSetter);
	}
}

void channel::delete_invited_member(std::string name) {
    std::vector<std::string>::iterator it = std::find(this->invitedMembers.begin(), this->invitedMembers.end(), name);
    if (it != this->invitedMembers.end()) {
        this->invitedMembers.erase(it);
    }
}

void channel::updateNick(Client *client, std::string new_nick) {
    std::map<std::string, Client*>::iterator it = members.find(client->getNickname());
    if (it != members.end()) {
        Client* clientPtr = it->second;
        members.erase(it);
        members[new_nick] = clientPtr;
		this->broadcastReply(":" + client->getNickname() + " NICK " + new_nick);
    }

    for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); ++it) {
        if (*it == client->getNickname()) {
            *it = new_nick;
        }
    }

    for (std::vector<std::string>::iterator it = invitedMembers.begin(); it != invitedMembers.end(); ++it) {
        if (*it == client->getNickname()) {
            *it = new_nick;
        }
    }

    if (topicSetter == client->getNickname()) {
        topicSetter = new_nick;
    }
	
    std::string new_creator = client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    if (new_creator == this->getCreator()) {
        this->creator = new_nick + "!" + client->getUsername() + "@" + client->getHostname();
    }
}
