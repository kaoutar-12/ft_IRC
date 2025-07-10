#include "../inc/Server.hpp"

Client::Client(std::string hostname, int port, int fd): hostname(hostname), port(port), fd(fd), state(UNREGISTERED)
{
}

Client::~Client()
{
    close(fd);
}

void Client::welcomeToServer()
{
    reply(Replies::RPL_WELCOME(this->getNickname(), this->getUsername(), this->getHostname()));
    std::cout << "Welcome to the server " << this->getNickname() << "!" << std::endl;
}

int Client::getState() const
{
    return (this->state);
}

void Client::setState(ClientState state)
{
    this->state = state;
}

void Client::setUsername(std::string username)
{
    this->username = username;
}

void Client::setNickname(std::string nickname)
{
    this->nickname = nickname;
}

void Client::setRealname(std::string realname)
{
    this->realname = realname;
}

std::string Client::getHostname() const
{
    return hostname;
}

std::string Client::getUsername() const
{
    return username;
}

std::string Client::getNickname() const
{
    return nickname;
}

std::string Client::getRealname() const
{
    return realname;
}

int Client::getPort() const
{
    return port;
}

int Client::getFd() const
{
    return fd;
}

void Client::reply(std::string message)
{
    std::string msg = message + "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
}

void Client::addInvitingChannel(channel* Channel)
{
	this->invitingChannels.push_back(Channel);
}

std::vector<channel *> Client::getInvitingChannels()
{
	return (this->invitingChannels);
}

channel* Client::getInvitingChannel(std::string channelName)
{
	if (!this->invitingChannels.empty())
	{
		for (std::vector<channel*>::iterator it = invitingChannels.begin();
		it != invitingChannels.end(); it++)
		{
			if ((*it)->getChannelName() == channelName)
				return (*it);
		}
	}
	return (NULL);
}

void Client::delete_invited_channel(channel *Channel) 
{
	std::vector<channel*>::iterator it = std::find(this->invitingChannels.begin(), this->invitingChannels.end(), Channel);
	if (it != this->invitingChannels.end()) {
		this->invitingChannels.erase(it);
	}
}

std::string& Client::getBuffer() {
    return buffer;
}

void Client::setBuffer(const std::string& newBuffer) {
    buffer = newBuffer;
}
