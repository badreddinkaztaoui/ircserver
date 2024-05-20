/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:45:37 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 03:37:36 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::nick(Request request, int fd) {
    std::string response;

    if (!clientList[fd])
        return "You are not connected\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
        return "You must authenticate first\n";
    if (request.args.size() < 1)
        return "Your nickname is set to: Guest\n";
    std::cout << request.args[0] << std::endl;
    if (request.args[0].size() > 9)
        return "Nickname is too long\n";
    if (request.args[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") != std::string::npos)
        return "Invalid nickname\n";
    if (clientList[fd]->getNickName() == request.args[0]) {
        response = "Your nickname is already set to: " + request.args[0] + "\n";
        return response;
    }
    for (size_t i = 0; i < this->nicknames.size(); i++) {
        if (this->nicknames[i] == request.args[0])
            return "Nickname is already taken\n";
    }
    this->nicknames.erase(std::remove(this->nicknames.begin(), this->nicknames.end(), clientList[fd]->getNickName()), this->nicknames.end());
    clientList[fd]->setNickName(request.args[0]);
    this->nicknames.push_back(request.args[0]);
    response = "Your nickname is set to: " + request.args[0] + "\n";
    return response;
}