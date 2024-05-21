/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:21:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 11:09:34 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"
#include "../../include/Client.hpp"


Request IrcServ::parseResponse(std::string response) {
    Request request;
    request.status = 0;
    
    if (response[0] == ' ' || response[0] == '\0' || response[0] == '\n')
        request.status = 1;

    std::istringstream iss(response);
    std::vector<std::string> args;

    std::string cmd;
    iss >> cmd;

    for (std::string arg; iss >> arg;)
        args.push_back(arg);

    if (args.empty())
        request.status = 1;

    request.cmd = cmd;
    request.args = args;
    return request;
}

std::string IrcServ::parseRequest(Request request, int fd) {
    std::string response;
    std::cout << "CMD: " << request.cmd << std::endl;

    if (request.status == 1)
        response = "Parssing Error\r\n";
    else if (request.cmd == "CAP")
        response = serverCap(request, fd);
    else if (request.cmd == "connect")
        response = connect(request, fd);
    else if (request.cmd == "NICK")
        response = nick(request, fd);
    else if (request.cmd == "USER")
        response = user(request, fd);
    else if (request.cmd == "PRIVMSG")
        response = privmsg(request, fd);
    else if (request.cmd == "JOIN")
        response = join(request, fd);
    else if (request.cmd == "INVITE")
        response = invite(request, fd);
    else if (request.cmd == "TOPIC")
        response = topic(request, fd);
    else if (request.cmd == "KICK")
        response = kick(request, fd);
    else if (request.cmd == "QUIT")
        response = quit(request, fd);
    else
        response = "Unknown command\r\n";
    return response;
}
