/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 03:44:12 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 03:50:16 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::user(Request request, int fd) {
    std::string response;

    if (!clientList[fd])
        return "You are not connected\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
        return "You must authenticate first\n";
    if (request.args.size() < 1)
        return "Your username is set to: " + clientList[fd]->getUserName() + "\n";
    if (request.args[0].size() > 9)
        return "Username is too long\n";
    if (request.args[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789") != std::string::npos)
        return "Invalid username\n";
    clientList[fd]->setUserName(request.args[0]);
    response = "Your username is set to: " + request.args[0] + "\n";
    return response;
}