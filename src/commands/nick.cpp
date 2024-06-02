/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:45:37 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/28 19:17:24 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::nick(Request request, int fd) {
    std::string response;

    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
        return "";
    if (request.args.size() < 1)
        return "\t\x03" "04No nickname provided\x03\n";
    std::cout << request.args[0] << std::endl;
    if (request.args[0].size() > 9)
        return "\t\x03" "04Nickname is too long\x03\n";
    if (request.args[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") != std::string::npos)
        return "\t\x03" "04Invalid nickname\x03\n";
    if (clientList[fd]->getNickName() == request.args[0]) {
        return "\t\x03" "04Your nickname is already set to:\x03 " + request.args[0] + "\n";
    }
    for (size_t i = 0; i < this->nicknames.size(); i++) {
        if (this->nicknames[i] == request.args[0])
            return "\t\x03" "04Nickname is already in use\x03\n";
    }
    this->nicknames.erase(std::remove(this->nicknames.begin(), this->nicknames.end(), clientList[fd]->getNickName()), this->nicknames.end());
    clientList[fd]->setNickName(request.args[0]);
    this->nicknames.push_back(request.args[0]);
    this->clientList[fd]->setRegistrationStep(2);
    response = "\t\x03" "06Your nickname has been set to:\x03 " + request.args[0] + "\n";
    send(fd, response.c_str(), response.length(), 0);
    return "\t\x03" "03Step 2 complete ✅\x03\n";
}