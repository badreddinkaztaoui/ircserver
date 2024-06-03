/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:37:47 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 14:38:18 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/IrcServ.hpp"
#include "../../include/Request.hpp"

std::string IrcServ::mode(Request request, int fd) {
    if (!clientList[fd])
        return "\t\x03" "04You're not connected to the server\x03\n";
    if (clientList[fd] && clientList[fd]->getAuthenticated() == 0)
        return "\t\x03" "04You have to be authenticated to change mode\x03\n";
    if (request.args.size() < 2)
        return "\t\x03" "04Not enough arguments\x03\n";
    return "";
}