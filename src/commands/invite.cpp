/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:54:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 11:18:21 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Utils.hpp"

std::string IrcServ::invite(Request request, int fd) {
    if (!clientList[fd] || !clientList[fd]->getAuthenticated())
        return "You have to be connected to invite someone\r\n";
    if (request.args.size() < 2)
        return "Usage: /INVITE <nickname> <channel>\r\n";
    if (clientList[fd]->getChannel().empty())
        return "You have to be in a channel to invite someone\r\n";
    
    Channel* channel = findChannel(request.args[1], this->channels);

    if (!channel)
        return "Channel not found\r\n";
    if (!channel->isOperator(clientList[fd]->getClientFd()))
        return "You have to be an operator to invite someone\r\n";
    
    for (std::map<int, Client*>::iterator it = clientList.begin(); it != clientList.end(); it++) {

        std::string res = "You have been invited to join " + channel->getName() + "\r\n";

        if (it->second && it->second->getNickName() == request.args[0] && it->second->getAuthenticated()) {
            if (it->second->getChannel() != "")
                return "User is already in the channel\r\n";
            it->second->setChannel(channel->getName());
            channel->addClient(it->second);
            channel->setConeectedClients();
            send(it->second->getClientFd(), res.c_str(), res.length(), 0);
            broadcast(channel->getName(), fd);
            return clientList[fd]->getNickName() + " invited " + it->second->getNickName() + " to " + channel->getName() + "\r\n";
        }
    }

    return clientList[fd]->getNickName() + " is not connected\r\n";
}