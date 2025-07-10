#include "../inc/Server.hpp"

CommandHandler::CommandHandler(Server *server)
{
    _commands["NICK"] = new Nick(server);
    _commands["USER"] = new User(server);
    _commands["PASS"] = new Pass(server);
    _commands["JOIN"] = new Join(server);
    _commands["PRIVMSG"] = new PrivMsg(server);
    _commands["KICK"] = new Kick(server);
    _commands["PART"] = new Part(server);
    _commands["QUIT"] = new Quit(server);
	_commands["MODE"] = new Mode(server);
	_commands["INVITE"] = new Invite(server);
	_commands["TOPIC"] = new Topic(server);
}

CommandHandler::~CommandHandler(){

}

void CommandHandler::capitalize(std::string &str)
{
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        if (*it >= 'a' && *it <= 'z') {
            *it = *it - 'a' + 'A';
        }
    }
}

void CommandHandler::handleCommand(std::string data, Client *client) {
    client->getBuffer() += data;
    std::size_t pos;

    while ((pos = client->getBuffer().find("\n")) != std::string::npos) {
        std::string command = client->getBuffer().substr(0, pos);
        client->setBuffer(client->getBuffer().substr(pos + 1));
        if (!command.empty() && command[0] == ':')
            command = command.substr(1);

        std::stringstream ss(command);
        std::string cmd;
        std::string argsBuffer;

        while(std::getline(ss, cmd)) {
            if (!cmd.empty() && cmd.back() == '\r') {
                cmd.pop_back();
            }
            
            std::string commandName = cmd.substr(0, cmd.find(" "));
            capitalize(commandName);

            try {
                Command *c = _commands.at(commandName);
                if (cmd.find(" ") != std::string::npos) {
                    argsBuffer = cmd.substr(cmd.find(" ") + 1);
                }

                std::istringstream argsStream(argsBuffer);
                std::string arg;
                std::list<std::string> args;

                while (std::getline(argsStream, arg, ' ')) {
                    arg.erase(std::remove_if(arg.begin(), arg.end(), ::isspace), arg.end());
                    args.push_back(arg);
                }

                if (client->getState() != REGISTERED && commandName != "NICK" && commandName != "USER" && commandName != "PASS") {
                    client->reply(Replies::ERR_NOTREGISTERED());
                    return;
                }

                c->run(client, args);
            } catch (const std::out_of_range &e) {
                client->reply(Replies::ERR_UNKNOWNCOMMAND(commandName));
            }
        }
    }
}

Command *CommandHandler::getCommand(std::string command){
    return _commands[command];
}