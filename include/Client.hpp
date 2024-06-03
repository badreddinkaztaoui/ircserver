/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:05:13 by nben-ais          #+#    #+#             */
/*   Updated: 2024/06/02 19:27:08 by bkaztaou         ###   ########.fr       */
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
        std::string         realName;
        std::string         hostName;
        std::string         serverName;
        const std::string   port;
        std::string         id;
        std::string         channel;
        ssize_t             registrationStep;
        bool                isRegistered;
        

    public :
        Client();
        Client(int fd);
        Client(Client const &org);
        Client &operator=(Client const &org);
        // Getters
        int         getClientFd();
        ssize_t     getRegistrationStep();
        std::string getNickName();
        std::string getUserName();
        std::string getRealName();
        std::string getHostname();
        std::string getServername();
        bool        getAuthenticated();
        bool        getIsRegistered();
        std::string getChannel();

        // Setters
        void        setRegistrationStep(ssize_t step);
        void        setAuthenticated(int auth);
        void        setIsRegistered(bool reg);
        void        setNickName(std::string nickname);
        void        setUserName(std::string username);
        void        setRealName(std::string realname);
        void        setHostname(std::string hostname);
        void        setServername(std::string servername);
        void        setChannel(std::string channel);

        ~Client();
};

#endif