#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <map>
#include <list>
#include <netdb.h>
#include <arpa/inet.h>
#include <sstream>
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "channel.hpp"
#include "Replies.hpp"
#include "Command.hpp"
#include <algorithm>
#include <cstdlib>
#include "time.h"
#include "ip_address.hpp"

class CommandHandler;

class Server{
    private:
        int sock_fd;
        std::string port;
        std::string pass;
        std::string serverName;
        std::vector<pollfd> _pollfds;
        std::map<int, Client *> _clients;
        CommandHandler *_commandHandler;
        std::map<std::string, channel *> channels;

    public:
        Server(std::string port, std::string pass);
        ~Server();
        void createSocket(std::string port);

        void start();
        void addClient(int fd);
        void removeClient(int fd);
        void handleMessage(int fd);
        std::string readMessage(int fd);
        std::string getPass() const;
        bool checkNickname(std::string const nickname) const;
        void joinChannel(std::string& channelName, Client* client, std::string& key);
        static void broadcast(std::string &targer, Client* client, std::string &message, Server *server);
        static void direct_message(std::string &targer, Client* client, std::string &message, Server *server);
        void broadcast_joining(std::string channelName, Client *client, Server *server);
        static void kickUser(std::string channelName, Client *client, std::string nickname, Server *server, std::string comment);
        static void kickUser(std::string channelName, Client *client, std::list<std::string> &userList, Server *server, std::string comment);
        void broadcast_kick(std::string channelName, Client *client, std::string nickname, Server *server, std::string comment);
        void partUser(std::string channelName, Client *client, Server *server, std::string comment, bool isQuit);
        void quitUser(Client *client, std::string message, Server *server, bool isQuit);

		bool setInviteOnlyChannel(std::string channelName, Client* client, bool adding);
		bool setTopicRestrictedChannel(std::string channelName, bool adding, Client *client);
		bool setPasswordChannel(std::string channelName, std::string key, Client *client);
		bool setUserLimitChannel(std::string channelName, bool adding, std::string limit, Client *client);
		bool setOperatorChannel(std::string channelName, std::string targetClient, bool adding, Client *client);
		void replyChannelModIs(std::string channelName, Client *client);
		void broadcastArgsReply(std::string channelName, std::string modeReply);
		std::map<std::string, channel *>	getChannels();
		channel*							getChannel(std::string channelName);
		Client*								getMember(std::string nickname);
        Client*								getClientByNickname(std::string nickname);
        void                                updateNickname(Client *client, std::string nickname);
};

#endif