/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:05:13 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/14 03:45:02 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H

#include "IrcServ.hpp"

class IrcServ;
class Client {
    private :
        int                 clientFd;
        bool                isAuth;
        std::string         nickName;
        std::string         userName;
        const std::string   port;
        std::string         id;
        std::string         channel;
        

    public :
        Client();
        Client(int fd);
        // Getters
        int         getClientFd();
        std::string getNickName();
        std::string getUserName();
        bool        getAuthenticated();
        std::string getChannel();
        // Setters
        void        setAuthenticated(int auth);
        void        setNickName(std::string nickname);
        void        setUserName(std::string username);
        void        setChannel(std::string channel);

        ~Client();
};

#endif