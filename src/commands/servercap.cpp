/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servercap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:48:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/19 22:18:17 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"


Client* findClientByFd(int fd, std::map<int, Client*> clientList) {
    for (size_t i = 0; i < clientList.size(); ++i) {
        if (clientList[i] && clientList[i]->getClientFd() == fd) {
            return clientList[i];
        }
    }
    return NULL;
}

std::string IrcServ::serverCap(Request request, int fd) {
    Client* client = findClientByFd(fd, this->clientList);

    for (size_t i = 0; i < request.args.size(); ++i) {
        const std::string& arg = request.args[i];

        if (i + 1 < request.args.size()) { 
            const std::string& nextArg = request.args[i + 1]; 
            
            if (arg.find("PASS") != std::string::npos) {
                std::string password = nextArg.substr(0, nextArg.find('\n'));

                if (!client) {
                    client = new Client(fd);
                    this->clientList[fd] = client;
                }

                if (password == this->passWord) {
                    client->setAuthenticated(1);
                } else {
                    return "Invalid password\n";
                }
            } else if (arg.find("NICK") != std::string::npos) {
                std::string nickname = nextArg.substr(0, nextArg.find('\n'));

                if (std::find(this->nicknames.begin(), this->nicknames.end(), nickname) == this->nicknames.end() && client) {
                    client->setNickName(nickname);
                    this->nicknames.push_back(nickname);
                } else {
                    return (client) ? "Nickname already exist, be creative\n" : "You must authenticate first\n";
                }
            } else if (arg.find("USER") != std::string::npos) {
                std::string username = nextArg.substr(0, nextArg.find('\n'));

                if (std::find(this->usernames.begin(), this->usernames.end(), username) == this->usernames.end() && client) {
                    client->setUserName(username);
                    this->usernames.push_back(username);
                } else {
                    return (client) ? "Username already exist, be creative\n" : "You must authenticate first\n";
                }
            }
        }
    }

    if (client && client->getAuthenticated()) {
        return "Welcome to Leet IRC network " + client->getNickName() + "!001@" + "localhost" + "\n" + "Your username is " + client->getUserName() + "\n";
    } else {
        return "Ooops! You're offline.\n";
    }
}