/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 04:07:05 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/21 10:02:17 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>

#include "Client.hpp"
#include "IrcServ.hpp"

class Client;

class Channel {
private:
    time_t                      creationTime;
    Client*                     owner;
    std::string                 name;
    std::string                 topic;
    std::string                 password;
    std::vector<Client*>        clients;
    std::vector<int>            operators;
    int                         connectedClients;
    int                         limit;
    bool                        l;
    bool                        k;
    bool                        t;
    bool                        i;
public:
    Channel();
    Channel(std::string name, Client* owner);

    // Getters
    Client*                     getOwner();
    std::string                 getName();
    std::string                 getTopic();
    std::string                 getPassword();
    time_t                      getCreationTime();
    int                         getConnectedClients();
    int                         getLimit();

    // Setters
    void                        setTopic(std::string topic);
    void                        setOperator(int fd);
    void                        setPassword(std::string password);
    void                        setConeectedClients();
    void                        setLimit(int limit);

    // Methods
    void                        addClient(Client* client);
    void                        removeClient(Client* client);
    void                        addOperator(int fd);
    void                        removeOperator(int fd);
    void                        sendToInvited(std::string msg);
    void                        sendToAll(std::string msg);

    // Checkers
    bool                        isOperator(int fd);
    bool                        isClient(Client* client);
    std::string                 isPrivate();
    std::string                 isClosed();
    bool                        canSetTopic(int fd);

    ~Channel();
};

#endif