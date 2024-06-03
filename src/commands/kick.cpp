/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:13:03 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 15:02:00 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Utils.hpp"

std::string IrcServ::kick(Request request, int fd) {
    if (request.args.size() < 2)
        return "Usage: /kick <channel> <nickname>\r\n";
    if (!clientList[fd] || !clientList[fd]->getAuthenticated())
        return "You have to be connected to kick a user\r\n";
    if (clientList[fd]->getChannel() == "")
        return "You have to join a channel to kick a user\r\n";
    Channel* channel = findChannel(request.args[0], this->channels);

    if (!channel)
        return "Channel " + request.args[0] + " not found\r\n";
    if (!channel->isOperator(clientList[fd]->getClientFd()))
        return "You don't have the permission to kick a user\r\n";
    
    for (std::map<int, Client*>::iterator it = clientList.begin(); it != clientList.end(); it++)
    {
        if (it->second && it->second->getNickName() == request.args[1])
        {
            if (channel->isClient(it->second))
            {
                std::string res = "You have been kicked from " + channel->getName() + "\r\n";

                it->second->setChannel("");
                channel->setConnectedClients();
                channel->removeClient(it->second);
                send(it->first, res.c_str(), res.length(), 0);
                return "User " + request.args[1] + " has been kicked from " + channel->getName() + "\r\n";
            }
            return "User " + request.args[1] + " is not in the channel\r\n";
        }
    }
    return "User " + request.args[1] + " not found\r\n";
}