#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class channel {
    private:
        std::string name;
        std::string creator;
        time_t creationTime; 
		std::string topicSetter;
        std::string topic;
        std::string key;
        bool inviteOnly;
        bool topicRestricted; 
        int userLimit;
        std::map<std::string, Client *>	members;
		std::vector<std::string>		invitedMembers;
        std::vector<std::string>		operators;
    public:
        channel();
        channel(Client *client, std::string name, std::string key, std::string topic = "");
        ~channel();

        bool addMember(std::string name, Client *client);

        bool isOperator(std::string name);
        bool isMember(std::string name);
        std::map<std::string, Client *>& getMembers();
        std::vector<std::string>& getOperators();
        std::string &getKey();
        void setKey(std::string key);
        std::string &getTopic();
        void setTopic(std::string topic); 
        time_t getCreationTime();
        void setUsersLimit(int limit);
        int getUsersLimit();
        bool getInviteOnly();
        void setInviteOnly(bool inviteOnly);
        bool getTopicRestricted();
        void setTopicRestricted(bool topicRestricted);
        std::string	getCreator();
		std::string	getChannelName();
		bool getInvitedMember(std::string name);
        void delete_invited_member(std::string name);
		std::vector<std::string>	getInvitedMembers();
		std::string					getSetTopicSetter(std::string topicSetter);
		Client*						getClient(std::string name);
        bool						addOperator(std::string name, Client *client);
		bool						removeOperator(std::string name, Client *client);
		void						addInvite(Client* client, Client *invitedClient);
		bool						isCreator(Client* client);
		void						broadcastReply(std::string Reply);
        void                        updateNick(Client *client, std::string new_nick);
};





#endif