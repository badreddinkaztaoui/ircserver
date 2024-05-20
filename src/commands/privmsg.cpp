/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 03:54:43 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 04:06:45 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::privmsg(Request request, int fd) {

    if (!clientList[fd])
        return "You are not connected\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
        return "You must authenticate first\n";
    if (request.args.size() < 2)
        return "Usage: PRIVMSG <nickname> <message>\n";
    for (std::map<int, Client*>::iterator it = clientList.begin(); it != clientList.end(); it++) {
        if (it->second->getNickName() == request.args[0] && it->second->getAuthenticated()) {
            std::string msg = this->clientList[fd]->getNickName() + " ===> ";
            for (size_t i = 1; i < request.args.size(); i++) {
                msg += request.args[i] + " ";
            }
            msg += "\n";
            send(it->first, msg.c_str(), msg.size(), 0);
            return "";
        }
    }
    return "User not found\n";
}