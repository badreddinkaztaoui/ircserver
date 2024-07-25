/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:24:59 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 16:09:27 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Request.hpp"
#include "../../include/IrcServ.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Utils.hpp"

void    IrcServ::broadcast(std::string channel, int fd) {

    time_t date = this->channels[channel]->getCreationTime();
    std::string message = "";

    message += this->clientList[fd]->getNickName() + " has joined " + channel + "\n";
    message += "Welcome to the channel " + channel + " " + clientList[fd]->getNickName() + "\n";
    message += "Topic: " + this->channels[channel]->getTopic() + "\n";
    message += "Channel created at: " + std::string(ctime(&date)) + "\n";
    message += "Channel creator: " + this->channels[channel]->getOwner()->getNickName() + "\n";
    this->channels[channel]->sendToAll(message);
}

std::string IrcServ::join(Request request, int fd) {

    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == false)
        return "\t\x03" "04You have to be authenticated to join a channel\x03\n";
    if (request.args.size() < 1)
        return "\t\x03" "04Usage: /join <channel>\x03\n";
    
    std::string channel = request.args[0];
    // A channel key is optional and can be empty
    std::string key = request.args.size() > 1 ? request.args[1] : "";

    if (!isValidChannelName(channel))
        return "\t\x03" "04Invalid channel name\x03\n";
    if (clientList[fd]->getChannel() == channel)
        return "\t\x03" "You are already in " + channel + "\x03\n";

    if (!findChannel(channel, this->channels))
        createChannel(channel, fd);
    else {
        if (this->channels[channel]->isClosed() == "+i") { 
            if (!this->channels[channel]->isClient(clientList[fd]))
                return "\t\x03" "04You are not invited to this channel\x03\n";
        }

        if (this->channels[channel]->getPassword() != "") {
            if (this->channels[channel]->getPassword() != key)
                return "\t\x03" "04Incorrect channel key\x03\n";
        }
        
    }    
    return "";
}

/**
 *if ((this->channels[channel]->getConnectedClients() >= this->channels[channel]->getLimit()) 
        & (this->channels[channel]->getLimit() != 0))
        return "Channel is full\n";
    if (this->channels[channel]->isPrivate() == "+k")
    {
        if (this->channels[channel]->getPassword() != key)
            return "Invalid password\n";
        if (this->channels[channel]->getPassword() == key)
        {
            clientList[fd]->setChannel(channel);
            this->channels[channel]->addClient(clientList[fd]);
            this->channels[channel]->setConnectedClients();
            broadcast(channel, fd);
            return "";
        }
    }
    else
    {
        clientList[fd]->setChannel(channel);
        this->channels[channel]->addClient(clientList[fd]);
        this->channels[channel]->setConnectedClients();
        broadcast(channel, fd);
        return "";
    }
*/