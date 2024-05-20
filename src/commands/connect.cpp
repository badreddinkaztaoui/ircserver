/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:47:56 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 03:42:21 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::connect(Request request, int fd) {
    std::string response;

    if (request.args.size() != 3)
        response = "Not enough parameters\r\n";
    if (request.args[0] != "localhost")
        return "Invalid server\r\n";
    if (request.args[1] != this->port)
        return "Invalid port\r\n";
    if (request.args[2] != this->passWord)
        return "Invalid password\r\n";
    if (this->clientList[fd] && this->clientList[fd]->getAuthenticated() == 1)
        return "Already connected\r\n";
    else {
        this->clientList[fd]->setAuthenticated(1);
        this->clientList[fd]->setNickName("Guest");
        this->nicknames.push_back("Guest");
        this->clientList[fd]->setUserName("Guest");
        this->usernames.push_back("Guest");

        response = "Welcome to the Internet Relay Network " + this->clientList[fd]->getNickName() + "!" + this->clientList[fd]->getUserName() + "@localhost\r\n";
    }
    return response;
}