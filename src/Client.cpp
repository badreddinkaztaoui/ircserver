/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:59:01 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/28 19:05:30 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {
    registrationStep = 0;
    clientFd = -1;
    isAuth = 0;
    nickName = "";
    userName = "";
    id = "";
    channel = "";
}

Client::Client(int fd) {
    registrationStep = 0;
    clientFd = fd;
    isAuth = 0;
    nickName = "";
    userName = "";
    id = "";
    channel = "";
}

Client::Client(Client const &org) {
    *this = org;
}

Client &Client::operator=(Client const &org) {
    if (this != &org) {
        clientFd = org.clientFd;
        isAuth = org.isAuth;
        nickName = org.nickName;
        userName = org.userName;
        id = org.id;
        channel = org.channel;
    }
    return *this;
}


std::string Client::getNickName() {
    return nickName;
}
std::string Client::getUserName() {
    return userName;
}

void    Client::setRegistrationStep(ssize_t step) {
    this->registrationStep = step;
}

ssize_t Client::getRegistrationStep() {
    return this->registrationStep;
}


void    Client::setAuthenticated(int auth) {
    isAuth = auth;
}

bool    Client::getAuthenticated() {
    return isAuth;
}

int Client::getClientFd() {
    return clientFd;
}

std::string Client::getChannel() {
    return channel;
}

void    Client::setNickName(std::string nickname) {
    nickName = nickname;
}
void    Client::setUserName(std::string username) {
    userName = username;
}

void    Client::setChannel(std::string channelName) {
    channel = channelName;
}

Client::~Client() {
    
}
