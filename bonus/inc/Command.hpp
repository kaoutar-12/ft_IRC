#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"

class Server;
class Client;

class Command{
    protected:
        Server *server;

    public:
        Command(Server *server): server(server) {};
        virtual ~Command() {};
        virtual void run(Client* client, std::list<std::string> args) = 0;
};

class Nick : public Command{
    public:
        Nick(Server *server);
        ~Nick();
        void run(Client* client, std::list<std::string> args);
};

class User : public Command{
    public:
        User(Server *server);
        ~User();
        void run(Client* client, std::list<std::string> args);
};

class Pass : public Command{
    public:
        Pass(Server *server);
        ~Pass();
        void run(Client* client, std::list<std::string> args);
};

class Join : public Command{
    public:
        Join(Server *server);
        ~Join();
        void run(Client* client, std::list<std::string> args);
};

class PrivMsg : public Command{
    public:
        PrivMsg(Server *server);
        ~PrivMsg();
        void run(Client* client, std::list<std::string> args);
};

class Kick : public Command{
    public:
        Kick(Server *server);
        ~Kick();
        void run(Client* client, std::list<std::string> args);
};

class Part : public Command{
    public:
        Part(Server *server);
        ~Part();
        void run(Client* client, std::list<std::string> args);
};

class Quit : public Command{
    public:
        Quit(Server *server);
        ~Quit();
        void run(Client* client, std::list<std::string> args);
};

class Mode : public Command{
	private:
		std::map<char, std::string>	modeArgument;
	public:
		Mode(Server *server);
		~Mode();
		void run(Client* client, std::list<std::string> args);
};

class Invite : public Command{
	public:
		Invite(Server *server);
		~Invite();
		void run(Client* client, std::list<std::string> args);
};

class Topic : public Command{
	public:
		Topic(Server *server);
		~Topic();
		void run(Client* client, std::list<std::string> args);
};

class Weather : public Command{
    public:
        Weather(Server *server);
        ~Weather();
        void run(Client* client, std::list<std::string> args);
};

#endif