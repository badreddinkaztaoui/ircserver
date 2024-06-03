/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:27 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/02 18:42:29 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::pass(Request request, int fd) {
    std::string response;
    
    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 1)
        return "\t\x03" "07You are already authenticated\x03\n";
    if (request.args.size() < 1)
        return "\t\x03" "04No password provided\x03\n";
    if (request.args[0] != this->passWord)
        return "\t\x03" "04Invalid password ❌\x03\n";
    if (!clientList[fd]->getIsRegistered()) {
        if (clientList[fd]->getRegistrationStep() >= 1)
            return "\t\x03" "07You have already verified the server password\x03\n";
        this->clientList[fd]->setRegistrationStep(1);
        return "\t\x03" "03Step 1 completed ✅\x03\n";
    }
    return "";
}