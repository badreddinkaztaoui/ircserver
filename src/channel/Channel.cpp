/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 04:47:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 04:54:47 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client* owner) {
    this->name = name;
    this->owner = owner;
    this->creationTime = time(0);
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

std::vector<Client*> Channel::getConnectedClients() {
    return this->connectedClients;
}

time_t Channel::getCreationTime() {
    return this->creationTime;
}

int Channel::getLimit() {
    return this->limit;
}

void Channel::setTopic(std::string topic) {
    this->topic = topic;
}

void Channel::setLimit(int limit) {
    this->limit = limit;
}

void Channel::addClient(Client* client) {
    this->clients.push_back(client);
}

void Channel::removeClient(Client* client) {
    this->clients.erase(std::remove(this->clients.begin(), this->clients.end(), client), this->clients.end());
}

void Channel::addOperator(Client* client) {
    this->operators.push_back(client);
}

void Channel::removeOperator(Client* client) {
    this->operators.erase(std::remove(this->operators.begin(), this->operators.end(), client), this->operators.end());
}

void Channel::sendToOne(std::string msg) {
    std::cout << msg << std::endl;
    //TODO: add the sendToOne implementation
}

void Channel::sendToAll(std::string msg) {
    std::cout << msg << std::endl;
    //TODO: add the sendToAll implementation
}

bool Channel::isOperator(Client* client) {
    return std::find(this->operators.begin(), this->operators.end(), client) != this->operators.end();
}

bool Channel::isClient(Client* client) {
    return std::find(this->clients.begin(), this->clients.end(), client) != this->clients.end();
}

Channel::~Channel() {}

