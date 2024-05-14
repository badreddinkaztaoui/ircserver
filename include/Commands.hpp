/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:27:01 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/14 03:29:08 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Request.hpp"
#include "Client.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <map>

class Commands
{
    private:
        std::map<int, Client*>  clientList;
        std::string             port;
        std::string             passWord;

	public:
        Commands();
        Commands(std::map<int, Client*> clientList, std::string port, std::string passWord);
        // Parsing
        Request                 parseResponse(std::string response);
        std::string             parseRequest(Request request, int fd);
        // Commands
        std::string             serverCap(Request request, int fd);
		std::string             connect(Request request, int fd);
        std::string             nick(Request request, int fd);
        std::string             user(Request request, int fd);
        std::string             join(Request request, int fd);
        std::string             join_message(std::string channel, int fd);
        std::string             mode(Request request, int fd);
        std::string             topic(Request request, int fd);
        std::string             invite(Request request, int fd);
        std::string             privmsg(Request request, int fd);
        std::string             kick(Request request, int fd);
        std::string             quit(Request request, int fd);
        ~Commands();
};


#endif