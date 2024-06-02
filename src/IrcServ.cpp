/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:41:23 by nben-ais          #+#    #+#             */
/*   Updated: 2024/05/28 19:04:37 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServ.hpp"
#include "../include/Request.hpp"

#define MAX_BUFF 4096
#define MAX_EVENTS 20

IrcServ::IrcServ(): clientList() {
    this->port = "";
    this->passWord = "";
}

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

    clientList[clientSocket] = new Client(clientSocket);

    epoll_event  event;
    event.events = EPOLLIN;
    event.data.fd = clientSocket;
    int epollctlfd2 = epoll_ctl(epollfd, EPOLL_CTL_ADD, clientSocket, &event);

    if (epollctlfd2 < 0)
        errorFunction("Can't add client.", serverSocket);
}


void IrcServ::multiClient(int serverSocket, int epollfd) {
    while (1) {
        epoll_event events[MAX_EVENTS];
        int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

        if (nfds < 0) {
            errorFunction("epoll_wait failed", serverSocket); 
            return;
        }

        for (int i = 0; i < nfds; ++i) {
            int fd = events[i].data.fd;

            if (fd == serverSocket) { 
                this->acceptSocket(serverSocket, epollfd);
            } else {
                std::string receivedData;
                char buffer[MAX_BUFF];
                ssize_t bytesRead = 0;

                while ((bytesRead = recv(fd, buffer, MAX_BUFF - receivedData.size() - 1, 0)) > 0) {
                    buffer[bytesRead] = '\0'; 
                    receivedData += buffer;

                    std::cout << "Received data: " << receivedData;
                    
                    if (receivedData.find("\r\n") != std::string::npos) {
                        Request request = parseResponse(receivedData);
                        std::string response = parseRequest(request, fd);
                        send(fd, response.c_str(), response.size(), 0);
                        receivedData.clear();
                        break;
                    } else if (receivedData.size() >= MAX_BUFF) {
                        send(fd, "Message too long\r\n", 24, 0);
                        if (clientList[fd]->getChannel() != "")
                            channels[clientList[fd]->getChannel()]->removeClient(clientList[fd]);
                        break;
                    }
                }
                if (bytesRead <= 0) {
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
                    std::cout << "Client " << fd << " disconnected\n";
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


IrcServ::~IrcServ() {
    for (std::map<int, Client*>::iterator it = this->clientList.begin(); it != this->clientList.end(); ++it) {
        delete it->second; 
    }
    this->clientList.clear();

    for (std::map<std::string, Channel*>::iterator it = this->channels.begin(); it != this->channels.end(); ++it) {
        delete it->second; 
    }
    this->channels.clear();
}