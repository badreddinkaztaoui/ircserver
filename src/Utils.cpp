/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 04:16:19 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 09:35:22 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Utils.hpp"

std::string toStr(int num) {
    std::stringstream str;
    str << num;
    return str.str();
}

Channel* findChannel(const std::string& name, std::map<std::string, Channel*>& channels) {
    for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if (it->first == name) {
            return it->second;
        }
    }
    return NULL; 
}

bool    isValidChannelName(const std::string& name) {
    if (name[0] != '#')
        return false;
    return true;
}