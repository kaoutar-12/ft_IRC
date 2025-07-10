#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <unordered_map>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define PURPLE  "\033[1;35m"

bool connectToServer(const std::string &server_ip, int port, int &sockfd) {
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str()); 

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(sockfd);
        return false;
    }

    return true;
}

bool sendToServer(int sockfd, const std::string &message) {
    if (send(sockfd, message.c_str(), message.length(), 0) == -1) {
        std::cerr << RED << "Failed to send message ❌" << RESET << std::endl;
        return false;
    }
    return true;
}

std::string fetchWeatherData(const std::string& city, const std::string& apiKey) {
    std::string url = "http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + city;
    std::string command = "curl -s \"" + url + "\" -o weather.json";
    system(command.c_str());
    std::ifstream file("weather.json");
    std::string response((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    remove("weather.json");
    if (response.find("error") != std::string::npos) {
        return "City unknown";
    }
    return response;
}

std::string extractValue(const std::string& json, const std::string& key) {
    std::string searchKey = "\"" + key + "\":";
    std::size_t startPos = json.find(searchKey);
    if (startPos == std::string::npos) {
        return "";
    }

    startPos += searchKey.length();
    while (json[startPos] == ' ' || json[startPos] == '\"' || json[startPos] == '{') {
        startPos++;
    }

    std::size_t endPos = json.find_first_of(",}", startPos);
    std::string value = json.substr(startPos, endPos - startPos);
    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
    return value;
}

std::string formatWeatherResponse(const std::string& weatherJson) {
    std::string location = extractValue(weatherJson, "name");
    std::string country = extractValue(weatherJson, "country");
    std::string condition = extractValue(weatherJson, "text");
    std::string temp_c = extractValue(weatherJson, "temp_c");
    std::string wind_kph = extractValue(weatherJson, "wind_kph");
    std::string humidity = extractValue(weatherJson, "humidity");
    std::string uv_index = extractValue(weatherJson, "uv");

    std::ostringstream oss;
    oss << "------------------------\n";
    oss << "Weather Information:\n";
    oss << "Location: " << location << ", " << country << "\n";
    oss << "Condition: " << condition << "\n";
    oss << "Temperature: " << temp_c << "°C\n";
    oss << "Wind Speed: " << wind_kph << " kph\n";
    oss << "Humidity: " << humidity << "%\n";
    oss << "UV Index: " << uv_index << "\n";
    oss << "------------------------\n";

    return oss.str();
}

void listenForMessages(int sockfd, std::string& apiKey) {
    char buffer[512];
    int numBytes;

    while (true) {
        if ((numBytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[numBytes] = '\0';
            std::string message(buffer);
            std::istringstream iss(message);
            std::string command, user, city;

            iss >> command >> user >> city;

            if (command == "WEATHER") {
                std::string weatherJson = fetchWeatherData(city, apiKey);

                
                if (weatherJson == "City unknown") {
                    std::string response = "PRIVMSG " + user + " :City unknown\r\n";
                    sendToServer(sockfd, response);
                } else {

                    std::string formattedMessage = formatWeatherResponse(weatherJson);
                    std::cout << "User: " << user << std::endl;
                    std::cout << "City: " << city << std::endl;
                    std::cout << "------------------------" << std::endl;

                    
                    std::istringstream iss(formattedMessage);
                    std::string line;
                    while (std::getline(iss, line)) {
                        std::string response = "PRIVMSG " + user + " :" + line + "\r\n";
                        sendToServer(sockfd, response);
                    }
                }
            }
        } else if (numBytes == 0) {
            std::cout << RED << "Server closed the connection" << RESET << std::endl;
            break;
        } else {
            std::cerr << RED << "Failed to receive message ❌" << RESET << std::endl;
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << GREEN << "Usage: " << argv[0] << " <server> <port> <password>" << RESET << std::endl;
        return 1;
    }

    std::string server = argv[1];
    int port = std::stoi(argv[2]);
    std::string password = argv[3];
    int sockfd;
    char *apikey = getenv("WEATHER_API_KEY");
    std::string apiKey;
    if (apikey) {
        apiKey = apikey;
        std::cout << GREEN << "WEATHER_API_KEY environment variable set ✅" << RESET << std::endl;
    } else {
        std::cerr << RED << "WEATHER_API_KEY environment variable not set ❌" << RESET << std::endl;
        exit(1);
    }

    if (connectToServer(server, port, sockfd)) {
        std::cout << GREEN << "Connected to server ✅" << RESET << std::endl;

        
        if (!sendToServer(sockfd, "PASS " + password + "\r\n") ||
            !sendToServer(sockfd, "NICK bot\r\n") ||
            !sendToServer(sockfd, "USER botname 0 * :bot\r\n")) {
            std::cerr << RED << "Failed to register with the server ❌" << RESET << std::endl;
            close(sockfd);
            return 1;
        }
        std::cout << GREEN << "Registered with the server ✅" << RESET << std::endl;
        std::cout << GREEN << "Listening for messages..." << RESET << std::endl;
        listenForMessages(sockfd, apiKey);
        close(sockfd);
    } else {
        std::cerr << RED << "Failed to connect to server ❌" << RESET << std::endl;
    }

    return 0;
}