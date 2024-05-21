/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:24:59 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 11:17:30 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Request.hpp"
#include "../../include/IrcServ.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Utils.hpp"

void    IrcServ::broadcast(std::string channel, int fd) {

    time_t date = this->channels[channel]->getCreationTime();
    std::string message = "";

    message += this->clientList[fd]->getNickName() + " has joined " + channel + "\r\n";
    message += "Welcome to the channel " + channel + " " + clientList[fd]->getNickName() + "\r\n";
    message += "Topic: " + this->channels[channel]->getTopic() + "\r\n";
    message += "Channel created at: " + std::string(ctime(&date)) + "\r\n";
    message += "Channel creator: " + this->channels[channel]->getOwner()->getNickName() + "\r\n";
    message += "Channel has : " + toStr(this->channels[channel]->getConnectedClients()) + " members\r\n";
    this->channels[channel]->sendToAll(message);
}

std::string IrcServ::join(Request request, int fd) {

    if (!clientList[fd])
        return "You have to be connected to join a channel\r\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == false)
        return "You have to be authenticated to join a channel\r\n";
    if (request.args.size() < 1)
        return "Not enough arguments\r\n";
    
    std::string channel = request.args[0];
    std::string key = request.args[1];

    if (!isValidChannelName(channel))
        return "Invalid channel name: must start with '#'\r\n";
    if (clientList[fd]->getChannel() == channel)
        return "You are already in a channel\r\n";

    if (!findChannel(channel, this->channels))
    {
        createChannel(channel, fd);
    }
    else
    {
        if (this->channels[channel]->isClosed() == "+i")
        {
            if (!this->channels[channel]->isClient(clientList[fd]))
                return "You are not invited to this channel\r\n";
        }
        else
        {
            if ((this->channels[channel]->getConnectedClients() >= this->channels[channel]->getLimit()) 
                & (this->channels[channel]->getLimit() != 0))
                return "Channel is full\r\n";
            if (this->channels[channel]->isPrivate() == "+k")
            {
                if (this->channels[channel]->getPassword() != key)
                    return "Invalid password\r\n";
                if (this->channels[channel]->getPassword() == key)
                {
                    clientList[fd]->setChannel(channel);
                    this->channels[channel]->addClient(clientList[fd]);
                    this->channels[channel]->setConeectedClients();
                    broadcast(channel, fd);
                    return "";
                }
            }
            else
            {
                clientList[fd]->setChannel(channel);
                this->channels[channel]->addClient(clientList[fd]);
                this->channels[channel]->setConeectedClients();
                broadcast(channel, fd);
                return "";
            }
        }
        
    }    
    return "";
}