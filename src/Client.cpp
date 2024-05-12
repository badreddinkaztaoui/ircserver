/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:59:01 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/12 17:01:14 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {
    clientFd = -1;
    isAuth = 0;
    nickName = "";
    userName = "";
    id = "";
    channel = "";
}

Client::Client(int fd) {
    clientFd = fd;
    isAuth = 0;
    nickName = "";
    userName = "";
    id = "";
    channel = "";
}

std::string Client::getNickName() {
    return nickName;
}
std::string Client::getUserName() {
    return userName;
}

bool    Client::getAuthenticated() {
    return isAuth;
}

int Client::getClientFd() {
    return clientFd;
}

void    Client::setNickName(std::string nickname) {
    nickName = nickname;
}
void    Client::setUserName(std::string username) {
    userName = username;
}

Client::~Client() {
    
}
