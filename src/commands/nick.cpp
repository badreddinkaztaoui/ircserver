/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:45:37 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 14:19:35 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string    isVaildNick(std::string nickname, std::vector<std::string> nicknames) {
    if (nickname.size() > 9)
        return "\t\x03" "04Nickname is too long\x03\n";
    if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") != std::string::npos)
        return "\t\x03" "04Invalid nickname\x03\n";
    for (size_t i = 0; i < nicknames.size(); i++) {
        if (nicknames[i] == nickname)
            return "\t\x03" "04Nickname is already in use\x03\n";
    }
    return "VALID";
}

std::string IrcServ::nick(Request request, int fd) {
    std::string response = "";

    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (request.args.size() < 1)
            return "\t\x03" "04No nickname provided\x03\n";
    if (!clientList[fd]->getIsRegistered()) {
        if (clientList[fd]->getRegistrationStep() < 1)
            return "\t\x03" "07You have to verify the server password first\x03\n";
        if (clientList[fd]->getRegistrationStep() >= 2)
            return "\t\x03" "07You have already set your nickname\x03\n";
        if (isVaildNick(request.args[0], this->nicknames) == "VALID") {
            this->clientList[fd]->setRegistrationStep(2);
            std::string msg = "\t\x03" "03Step 2 complete ✅\x03\n";
            send(fd, msg.c_str(), msg.length(), 0);
        } else {
            return isVaildNick(request.args[0], this->nicknames);
        }
    } else {
        if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
            return "\t\x03" "You have to be authenticated to change your nickname\x03\n";
        if (isVaildNick(request.args[0], this->nicknames) != "VALID")
            return isVaildNick(request.args[0], this->nicknames);
        response = "\t\x03" "03Your nickname has been set to:\x03 " + request.args[0] + "\n";
    }
    if (clientList[fd]->getNickName() != "") {
        if (clientList[fd]->getNickName() == request.args[0])
            return "\t\x03" "06Your nickname is already set to:\x03 " + request.args[0] + "\n";
        this->nicknames.erase(std::remove(this->nicknames.begin(), this->nicknames.end(), clientList[fd]->getNickName()), this->nicknames.end());
    }
    clientList[fd]->setNickName(request.args[0]);
    this->nicknames.push_back(request.args[0]);
    return response;
}