#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"

class channel;

enum ClientState{
    UNREGISTERED,
    REGISTERED,
    NICK,
    NONICK,
    AWAY,
    OPERATOR,
    UNKNOWN
};

class Client{
    private:
        std::string hostname;
        std::string username;
        std::string nickname;
        std::string realname;
        int port;
        int fd;
        ClientState state;
		std::vector<channel*>	invitingChannels;
        std::string buffer;


    public:
        Client(std::string hostname, int port, int fd);
        ~Client();

        std::string getHostname() const;
        std::string getUsername() const;
        std::string getNickname() const;
        std::string getRealname() const;
        int getState() const;
        int getPort() const;
        int getFd() const;

        void setUsername(std::string username);
        void setNickname(std::string nickname);
        void setRealname(std::string realname);
        void setState(ClientState state);

        void reply(std::string message);

        void welcomeToServer();

		std::vector<channel*>	getInvitingChannels();
		channel*				getInvitingChannel(std::string channelName);
		void					addInvitingChannel(channel *Channel);
		void 					delete_invited_channel(channel *Channel);
        std::string& getBuffer();
        void setBuffer(const std::string& newBuffer);
};

#endif