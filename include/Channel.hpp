/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 04:07:05 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/20 04:53:37 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Client.hpp"
#include "IrcServ.hpp"

class Channel {
private:
    time_t                      creationTime;
    Client*                     owner;
    std::string                 name;
    std::string                 topic;
    std::string                 password;
    std::vector<Client*>        clients;
    std::vector<Client*>        operators;
    std::vector<Client*>        connectedClients;
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
    std::vector<Client*>        getConnectedClients();
    time_t                      getCreationTime();
    int                         getLimit();

    // Setters
    void                        setTopic(std::string topic);
    void                        setLimit(int limit);

    // Methods
    void                        addClient(Client* client);
    void                        removeClient(Client* client);
    void                        addOperator(Client* client);
    void                        removeOperator(Client* client);
    void                        sendToOne(std::string msg);
    void                        sendToAll(std::string msg);

    // Checkers
    bool                        isOperator(Client* client);
    bool                        isClient(Client* client);

    ~Channel();
};

#endif