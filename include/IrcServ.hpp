/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:41:53 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/19 22:20:43 by bkaztaou         ###   ########.fr       */
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
        std::map<int, Client*>          clientList;
        std::vector<std::string>        usernames;
        std::vector<std::string>        nicknames;
        // std::map<std::string, Channel*> channels;

    public:
        IrcServ();
        IrcServ(char **av);

        // --------------------------------- //
        //--------- SERVER FUNCTIONS --------//
        // --------------------------------- //
        void                            acceptSocket(int serverSocket, int epollfd);
        void                            multiClient(int serverSocket, int epollfd);
        void                            createServer();

        // --------------------------------- //
        // ------------- PARSING ------------//
        // --------------------------------- //
        Request                         parseResponse(std::string response);
        std::string                     parseRequest(Request request, int fd);

        // --------------------------------- //
        // ------------ COMMANDS ------------//
        // --------------------------------- //
        std::string                     serverCap(Request request, int fd);
		std::string                     connect(Request request, int fd);
        std::string                     nick(Request request, int fd);
        std::string                     user(Request request, int fd);
        std::string                     join(Request request, int fd);
        std::string                     join_message(std::string channel, int fd);
        std::string                     mode(Request request, int fd);
        std::string                     topic(Request request, int fd);
        std::string                     invite(Request request, int fd);
        std::string                     privmsg(Request request, int fd);
        std::string                     kick(Request request, int fd);
        std::string                     quit(Request request, int fd);

        // --------------------------------- //
        // ------------- CHANNELS -----------//
        // --------------------------------- //

        ~IrcServ();
};

void    errorFunction(const char *error, int serverSocket);

#endif 