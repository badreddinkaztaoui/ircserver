/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:31:53 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 15:02:00 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"
#include "../../include/IrcServ.hpp"

std::string IrcServ::quit(Request request, int fd) {
    if (request.args.size() > 0)
        return "Too many arguments\r\n";
    if (!clientList[fd] || !clientList[fd]->getAuthenticated())
        return "You have to be connected to quit\r\n";
        
    std::cout << "Client " << clientList[fd]->getNickName() << " has disconnected" << std::endl;
    
    if (clientList[fd]->getChannel() != "") {
        this->channels[clientList[fd]->getChannel()]->removeClient(clientList[fd]);
        this->channels[clientList[fd]->getChannel()]->setConnectedClients();
    }
    clientList[fd]->setChannel("");
    clientList[fd]->setAuthenticated(0);
    return "See you soon!\r\n";
}