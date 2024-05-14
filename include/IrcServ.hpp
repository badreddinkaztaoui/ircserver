/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:41:53 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/14 02:23:14 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_H
#define IRCSERV_H

#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <map>
#include "Client.hpp"
#include "Request.hpp"

class Client;
class IrcServ {
    private:
        std::string                     port;
        std::string                     passWord;
        std::map<int, Client*>           clientList;
        std::vector<std::string>        usernames;
        std::vector<std::string>        nicknames;
        // std::map<std::string, Channel*> channels;

    public:
        IrcServ();
        IrcServ(char **av);
        void                        acceptSocket(int serverSocket, int epollfd);
        void                        multiClient(int serverSocket, int epollfd);
        void                        createServer();
        ~IrcServ();
};

void    errorFunction(const char *error, int serverSocket);

#endif 