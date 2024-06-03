/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:59:01 by nben-ais          #+#    #+#             */
/*   Updated: 2024/06/02 19:28:43 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {
    registrationStep = 0;
    clientFd = -1;
    isAuth = 0;
    isRegistered = 0;
    nickName = "";
    userName = "";
    realName = "";
    hostName = "";
    serverName = "";
    id = "";
    channel = "";
}

Client::Client(int fd) {
    registrationStep = 0;
    clientFd = fd;
    isAuth = 0;
    isRegistered = 0;
    nickName = "";
    userName = "";
    realName = "";
    hostName = "";
    serverName = "";
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
        isRegistered = org.isRegistered;
        nickName = org.nickName;
        userName = org.userName;
        realName = org.realName;
        hostName = org.hostName;
        serverName = org.serverName;
        registrationStep = org.registrationStep;
        id = org.id;
        channel = org.channel;
    }
    return *this;
}

ssize_t Client::getRegistrationStep() {
    return this->registrationStep;
}

int Client::getClientFd() {
    return clientFd;
}

bool    Client::getIsRegistered() {
    return isRegistered;
}

bool    Client::getAuthenticated() {
    return isAuth;
}

std::string Client::getNickName() {
    return nickName;
}
std::string Client::getUserName() {
    return userName;
}

std::string Client::getRealName() {
    return realName;
}

std::string Client::getHostname() {
    return hostName;
}

std::string Client::getServername() {
    return serverName;
}

std::string Client::getChannel() {
    return channel;
}

// Setters

void    Client::setAuthenticated(int auth) {
    isAuth = auth;
}

void    Client::setIsRegistered(bool reg) {
    isRegistered = reg;
}

void    Client::setRegistrationStep(ssize_t step) {
    this->registrationStep = step;
}

void    Client::setNickName(std::string nickname) {
    nickName = nickname;
}
void    Client::setUserName(std::string username) {
    userName = username;
}

void    Client::setRealName(std::string realname) {
    realName = realname;
}

void    Client::setHostname(std::string hostname) {
    hostName = hostname;
}

void    Client::setServername(std::string servername) {
    serverName = servername;
}

void    Client::setChannel(std::string channelName) {
    channel = channelName;
}

Client::~Client() {
    
}
