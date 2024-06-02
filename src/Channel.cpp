/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 04:47:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 11:43:01 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/IrcServ.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client* owner) {
    this->name = name;
    this->owner = owner;
    this->topic = "Default topic";
    this->clients.push_back(owner);
    this->connectedClients = 1;
    this->creationTime = time(0);
    this->limit = 5;
    this->l = false;
    this->k = false;
    this->t = false;
    this->i = false;
}

void    IrcServ::createChannel(std::string name, int fd) {
    this->channels[name] = new Channel(name, this->clientList[fd]);
    this->channels[name]->setConeectedClients();
    this->channels[name]->setOperator(clientList[fd]->getClientFd());
    this->clientList[fd]->setChannel(name);
    broadcast(name, fd);
}

Client* Channel::getOwner() {
    return this->owner;
}

std::string Channel::getName() {
    return this->name;
}

std::string Channel::getTopic() {
    return this->topic;
}

std::string Channel::getPassword() {
    return this->password;
}

int     Channel::getConnectedClients() {
    return this->connectedClients;
}

time_t  Channel::getCreationTime() {
    return this->creationTime;
}

int     Channel::getLimit() {
    return this->limit;
}

void    Channel::setTopic(std::string topic) {
    this->topic = topic;
}

void    Channel::setOperator(int fd) {
    this->operators.push_back(fd);
    this->l = true;
    this->k = false;
    this->t = true;
    this->i = false;
}

void    Channel::setLimit(int limit) {
    this->limit = limit;
}

void    Channel::setConeectedClients() {
    this->connectedClients = this->clients.size();
}

void    Channel::setPassword(std::string password) {
    this->password = password;
}

void Channel::addClient(Client* client) {
    this->clients.push_back(client);
}

void Channel::removeClient(Client* client) {
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->clients[i] == client) {
            this->clients.erase(this->clients.begin() + i);
            sendToAll(client->getNickName() + " Has left the channel\r\n");
            return ;
        }
    }
}

void Channel::addOperator(int fd) {
    this->operators.push_back(fd);
}

void Channel::removeOperator(int fd) {
    this->operators.erase(std::remove(this->operators.begin(), this->operators.end(), fd), this->operators.end());}

void Channel::sendToInvited(std::string msg) {
    std::cout << msg << std::endl;
    //------------------------//
    //  TODO: TO BE IMPLEMENTED
    //------------------------//
    // for (size_t i = 0; i < this->clients.size(); i++) {
    //     if (this->clients[i]->getInvited())
    //         send(this->clients[i]->getClientFd(), msg.c_str(), msg.size(), 0);
    // }
}

void Channel::sendToAll(std::string msg) {
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->clients[i]->getAuthenticated())
            send(this->clients[i]->getClientFd(), msg.c_str(), msg.size(), 0);
    }
}

bool Channel::isOperator(int fd) {
    return std::find(this->operators.begin(), this->operators.end(), fd) != this->operators.end();
}

bool Channel::isClient(Client* client) {
    return std::find(this->clients.begin(), this->clients.end(), client) != this->clients.end();
}

std::string Channel::isClosed() {
    if (this->i)
        return "+i";
    return "-i";
}

std::string Channel::isPrivate() {
    if (this->k)
        return "+k";
    return "-k";
}

bool Channel::canSetTopic(int fd) {
    if (this->isOperator(fd) && this->t)
        return true;
    return false;
}

Channel::~Channel() {}

