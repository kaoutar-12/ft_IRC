#include "../inc/Server.hpp"

std::string Replies::ERR_NONICKNAME() {
    return "431 :No nickname given";
}

std::string Replies::RPL_WELCOME(const std::string& nickname, const std::string& username, const std::string& hostname) {
    return "001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!" + username + "@" + hostname;
}

std::string Replies::ERR_UNKNOWNCOMMAND(const std::string& command) {
    return "421 " + command + " :Unknown command";
}

std::string Replies::ERR_NEEDMOREPARAMS(const std::string& command) {
    return "461 " + command + " :Not enough parameters";
}

std::string Replies::ERR_TOOMANYARGUMENTS(const std::string& command) {
    return "461 " + command + " :Too many arguments";
}


std::string Replies::ERR_PASSWDMISMATCH(const std::string& client) {
	(void)client;
    return "464 " + serverIP + " :Password incorrect";
}

std::string Replies::ERR_ALREADYREGISTERED() {
    return "462 :You may not reregister";
}

std::string Replies::ERR_NOSUCHNICK(const std::string& nickname) {
    return "401 " + nickname + " :No such nick/channel";
}

std::string Replies::ERR_NICKNAMEINUSE(const std::string& nickname) {
    return "433 " + nickname + " :Nickname is already in use";
}

std::string Replies::ERR_ONLYONECHANNEL(const std::string& user) {
    return "477 " + user + " :You can only join one channel at a time : JOIN CHANNEL KEY";
}

std::string Replies::ERR_BADCHANMASK(const std::string& channel) {
    return "476 " + channel + " :Bad Channel Mask";
}


std::string Replies::ERR_ALREADYINCHANNEL(const std::string& nickname) {
    return "443 " + nickname + " :is already on channel";
}

std::string Replies::ERR_ALREADYOPERATOR(const std::string& nickname) {
    return "913 " + nickname + " :is already an operator";
}

std::string Replies::ERR_NORECIPIENT(const std::string& nickname) {
    return "411 " + nickname + " :No recipient given (PRIVMSG)";
}

std::string Replies::ERR_NOTONCHANNEL(const std::string& nickname, const std::string& channel) {
    return "442 " + nickname + " " + channel + " :You're not on that channel";
}

std::string Replies::ERR_USERNOTINCHANNEL(const std::string& operator_nick, const std::string& channel, const std::string& nonexistent_user) {
    return "441 " + operator_nick + " " + channel + " " + nonexistent_user + " :They aren't on that channel";
}

std::string Replies::ERR_BADCHANNELKEY(const std::string& channel, Client *client) {
    return (": " + serverIP + " 475 " + client->getNickname() + " " + channel + " :Cannot join channel (+k) - bad key");
}
std::string Replies::ERR_INVITEONLYCHAN(const std::string& nickname) {
    return (":" + serverIP + " 473 " + nickname + " :Cannot join channel (+i)");
}

std::string Replies::ERR_CHANNELISFULL(const std::string& nickname) {
    return (":" + serverIP + " 471 " + nickname + " :Cannot join channel (+l)");
}

std::string Replies::ERR_CHANOPRIVSNEEDED(const std::string& channel, const std::string& nickname) {
    return ":" + serverIP + " 482 " + nickname + " " + channel + " :You're not channel operator";
}

std::string Replies::ERR_CANNOTKICKOPERATOR(const std::string& channelName) {
    return "482 " + channelName + " :You cannot kick another operator from the channel.";
}

std::string Replies::ERR_NOTREGISTERED() {
    return ("" + serverIP + " 451 : You have not registered");
}

std::string Replies::RPL_CHANNELMODEIS(std::string name, std::string& channelName, std::string& command)
{
	return (":" + serverIP + " 324 " + name + " " + channelName + ((command.empty()) ? "" : " +" + command));
}

std::string Replies::RPL_CHANNELMODEIS_BROADCAST(std::string& channelName, std::string& command)
{
	return (":" + serverIP + " MODE " + channelName + " " + command);
}

std::string Replies::ERR_NOSUCHCHANNEL(std::string name, std::string& channelName)
{
	return (":" + serverIP + " 403 " + name + " " + channelName + " :No such channel");
}

std::string Replies::ERR_UNKNOWNMODE(Client *client, char& modeChar)
{
	return (":" + serverIP + " 472 " + client->getNickname() + " " + std::string(1, modeChar) + " :is unknown mode char to me");
}

std::string Replies::ERR_USERONCHANNEL(Client *client, std::string ChannelName)
{
	return (":" + serverIP + " 443 " + client->getNickname() + " " + ChannelName + " ::is already on channel");
}

std::string Replies::RPL_INVITING(std::string channelName, Client* client, Client* invitedMember, int sendToClient)
{
	if (sendToClient == 1)
		return (":" + serverIP + " 341 " + client->getNickname() + " " + invitedMember->getNickname() + " " + channelName + " :Invitation sent");
	else if (sendToClient == 2)
		return (":" + serverIP + " 341 " + client->getNickname() + " " + invitedMember->getNickname() + " "+ channelName + " :Invitation has already been sent");
	else
		return (":" + client->getNickname() + "!" + client->getUsername() + "@" + serverIP + " INVITE " + invitedMember->getNickname() + " :" + channelName);
}

std::string Replies::ERR_ERRONEUSNICKNAME (std::string& nickname)
{
	return (":" + serverIP + " 432 " + nickname + " :Erroneus nickname");
}

std::string Replies::ERR_USERNOTINCHANNEL (std::string targetClient, std::string channelName)
{
	return (":" + serverIP + " 441 " + targetClient + " "
	+ channelName + ": They aren't on that channel");
}

std::string Replies::ERR_CANTKICKCREATOR (Client *client, std::string channelName)
{
	return (":" + serverIP + " 484 " + client->getNickname() + " " + channelName + " :Cannot remove channel creator's operator status");
}

std::string Replies::ERR_INVALIDLIMIT (Client *client, std::string channelName)
{
	return (":" + serverIP + " 479 " + client->getNickname() + " " + channelName + " :Invalid user limit specified");
}

std::string Replies::ERR_CANTINVITESELF(std::string clientName)
{
	return (":" + serverIP + " 481 " + clientName + " :You cannot invite yourself");
}

std::string Replies::RPL_INVITELIST(const std::string& clientNickname, std::vector<channel *> channels) {
	if (channels.empty())
		return ("346 " + clientNickname + " * :You have no pending invitations.");
    std::string reply = "336 " + clientNickname + " :";
    
    for (size_t i = 0; i < channels.size(); ++i) {
        reply += channels[i]->getChannelName();
        if (i < channels.size() - 1) {
            reply += ",";
        }
    }
    
    return (reply);
}

std::string Replies::RPL_TOPIC(std::string clientName, std::string channelName, std::string topic)
{
	if (topic == "")
	{
		return (":" + serverIP + " 331 " + clientName + " " + channelName + " :No topic is set");
	}
	else
	{
		return (":" + serverIP + " 332 " + clientName + " " + channelName + " :Current topic is: " + topic);
	}
}

std::string Replies::RPL_TOPICWHOTIME(std::string clientName, std::string channelName, std::string topicSetter, time_t setTime)
{
	return (":" + serverIP + " 333 " + clientName + " " + channelName + " " + topicSetter + " " + std::to_string(setTime));
}

std::string Replies::RPL_BOTNOTREGISTERED()
{
	return (":" + serverIP + " 1 bot bot not registered for now !");
}

