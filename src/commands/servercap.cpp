/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servercap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:48:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/28 14:37:54 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"
#include "../../include/Utils.hpp"

std::string randname() {
    std::string name = "user";
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 8; i++)
        name += charset[rand() % charset.length()];
    return name;
}

bool isvalidname(std::string name, std::vector<std::string> names) {
    if (name.empty())
        return false;
    if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
        return false;
    for (size_t i = 0; i < names.size(); i++) {
        if (names[i] == name)
            return false;
    }
    return true;
}

std::string IrcServ::serverCap(Request request, int fd) {
    Client *client = clientList[fd];
    
    if (!client)
        return "You are not connected\n";
    
    if (request.args[0] == "LS" && request.args[1] == "302") {
        welcomeMessage(fd);
    }
    return "";
}
