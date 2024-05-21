/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:31:53 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 09:52:27 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"
#include "../../include/IrcServ.hpp"
#include "../../include/Utils.hpp"

std::string IrcServ::quit(Request request, int fd) {
    if (request.args.size() > 0)
        return "Too many arguments\r\n";
    if (!clientList[fd] || !clientList[fd]->getAuthenticated())
        return "You have to be connected to quit\r\n";
    if (clientList[fd]->getChannel() != "") {
        Channel* channel = findChannel(clientList[fd]->getChannel(), this->channels);
        channel->removeClient(clientList[fd]);
        channel->setConeectedClients();
    }
    clientList[fd]->setAuthenticated(0);
    clientList[fd]->setChannel("");
    clientList[fd]->setNickName("");
    clientList[fd]->setUserName("");
    return "See you soon!\r\n";
}