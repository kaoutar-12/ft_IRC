#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "Server.hpp"

class Server;
class Command;

class CommandHandler{
    private:
        std::map<std::string, Command *> _commands;
    public:
        CommandHandler(Server *server);
        ~CommandHandler();

        Command *getCommand(std::string command);
        void capitalize(std::string &str);

        void handleCommand(std::string command, Client *client);
};

#endif