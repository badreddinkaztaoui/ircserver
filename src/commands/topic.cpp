/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:53:45 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 11:25:26 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"
#include "../../include/IrcServ.hpp"
#include "../../include/Utils.hpp"

std::string IrcServ::topic(Request request, int fd) {
    if (request.args.size() < 2)
        return "Usage: /TOPIC <channel> <topic>\r\n";
    if (!clientList[fd] || !clientList[fd]->getAuthenticated())
        return "You have to be connected to set a topic\r\n";
    if (clientList[fd]->getChannel() == "")
        return "You have to join a channel to set a topic\r\n";
    
    Channel* channel = findChannel(request.args[0], this->channels);

    if (!channel->isOperator(clientList[fd]->getClientFd()) || !channel->canSetTopic(clientList[fd]->getClientFd()))
        return "You don't have the permission to set the topic\r\n";
    else {
        channel->setTopic(request.args[1]);
        return ":" + clientList[fd]->getNickName() + " TOPIC " + channel->getName() + " :" + channel->getTopic() + "\r\n";
    }
}