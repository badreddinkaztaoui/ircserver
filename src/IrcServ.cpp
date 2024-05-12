/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:41:23 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/12 16:51:52 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServ.hpp"

#define MAX_BUFF 4096
#define MAX_EVENTS 10

IrcServ::IrcServ(): clientList() {}

IrcServ::IrcServ(char **av): clientList() {
    this->port = av[1];
    this->passWord = av[2];
}

void    errorFunction(const char *error, int serverSocket) {
    std::cout << error << std::endl;
    close (serverSocket);
    exit (1);
}

void    IrcServ::acceptSocket(int serverSocket, int epollfd) {
    int         clientSocket;
    sockaddr_in clientAddress;
    socklen_t   clientAddressSize = sizeof(clientAddress);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    if (clientSocket < 0)
        errorFunction("Accept Failed", serverSocket);

    epoll_event  event;
    event.events = EPOLLIN;
    event.data.fd = clientSocket;
    int epollctlfd2 = epoll_ctl(epollfd, EPOLL_CTL_ADD, clientSocket, &event);

    if (epollctlfd2 < 0)
        errorFunction("Can't add client.", serverSocket);
}

void    IrcServ::multiClient(int serverSocket, int epollfd) {

    while (1) {
        epoll_event events[MAX_EVENTS];
        int epwfd = epoll_wait(epollfd, events, MAX_EVENTS, -1);

        if (epwfd < 0)
            errorFunction("Waiting for events failed.", serverSocket);
    
        for (int i = 0; i < epwfd; i++) {
            if (events[i].data.fd == serverSocket) {
                this->acceptSocket(serverSocket, epollfd);
            } else {
                char    buffer[MAX_BUFF] = {0};
                int     bitsReaded = 0;
                ssize_t recvData = recv(events[i].data.fd, buffer + bitsReaded, sizeof(buffer) - bitsReaded, 0);

                if (recvData == 0) {
                    epoll_ctl(serverSocket, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    std::cout << "Client " << events[i].data.fd << " Disconnected" << std::endl;
                    close(events[i].data.fd);

                    //! -------------------------------------------
                    //TODO: Kick client from channel if he is in one
                    //! -------------------------------------------

                    delete clientList[events[i].data.fd];
                    clientList.erase(events[i].data.fd);
                    break;
                } else {
                    bitsReaded += recvData;
                    if (bitsReaded < MAX_BUFF) {
                        std::cout << "Message: " << buffer << std::endl;
                    } else {
                        std::cout << "Message is too long." << std::endl;
                        break;
                    }
                }
            } 
        }
    }
}

void    IrcServ::createServer() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        errorFunction("Socket Not Created Yet For The Server", serverSocket);

    sockaddr_in serverAddress;
    int bindPort = atoi(this->port.c_str());
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(bindPort);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    int optVal = 1;

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0)
        errorFunction("Setsockopt Faild", serverSocket);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0 )
        errorFunction("Bind Faild", serverSocket);

    if (listen(serverSocket, SOMAXCONN))
        errorFunction("Listen Failed", serverSocket);

    int epollfd = epoll_create(1);
    if (epollfd < 0)
        errorFunction("epoll_create failed", serverSocket);

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    int epollctlfd1 = epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event);
    if (epollctlfd1 < 0)
        errorFunction("EPOLL CTL1 FAILD", serverSocket);

    multiClient(serverSocket, epollfd);
}

IrcServ::~IrcServ() {}