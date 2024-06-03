/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 03:44:12 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 14:24:41 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"
#include "../../include/Utils.hpp"

std::string     isValidUsername(std::string username) {
    if (username.size() > 9)
        return "\t\x03" "04Username is too long\x03\n";
    for (size_t i = 0; i < username.size(); i++) {
        if (!isalnum(username[i]) && username[i] != '_')
            return "\t\x03" "04Invalid username\x03\n";
    }
    return "VALID";
}

std::string IrcServ::user(Request request, int fd) {
    std::string response = "";

    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (request.args.size() < 4)
        return "\t\x03" "04Not enough parameters\x03\n";
    if (request.args[3][0] != ':')
        return "\t\x03" "04Invalid format\x03\n";
    if (!clientList[fd]->getIsRegistered()) {
        if (clientList[fd]->getRegistrationStep() < 2)
            return "\t\x03" "07You have to set your nickname first\x03\n";
        if (clientList[fd]->getRegistrationStep() >= 3)
            return "\t\x03" "07You have already registred\x03\n";
        if (isValidUsername(request.args[0]) != "VALID")
            return isValidUsername(request.args[0]);
        clientList[fd]->setRegistrationStep(3);
        clientList[fd]->setIsRegistered(true);
        clientList[fd]->setAuthenticated(true);
        std::string msg = "\t\x03" "03Step 3 complete ✅\x03\n";
        send(fd, msg.c_str(), msg.length(), 0);
        registredMsg(fd);
    } else {
        if (!clientList[fd]->getAuthenticated())
            return "\t\x03" "04You have to be authenticated to change your username\x03\n";
        if (isValidUsername(request.args[0]) != "VALID")
            return isValidUsername(request.args[0]);
        response = "\t\x03" "03Your username has been set to:\x03 " + request.args[0] + "\n";
    }
    if (clientList[fd]->getUserName() != "") {
        if (clientList[fd]->getUserName() == request.args[0])
            return "\t\x03" "06Your username is already set to:\x03 " + request.args[0] + "\n";
        this->usernames.erase(std::remove(this->usernames.begin(), this->usernames.end(), clientList[fd]->getUserName()), this->usernames.end());
    }
    clientList[fd]->setUserName(request.args[0]);
    clientList[fd]->setRealName(request.args[3]);
    clientList[fd]->setHostname(request.args[1]);
    clientList[fd]->setServername(request.args[2]);
    this->usernames.push_back(request.args[0]);

    return response;
}