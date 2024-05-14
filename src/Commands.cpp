/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:21:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/14 04:14:12 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Commands.hpp"
#include "../include/Request.hpp"

Commands::Commands() {}

Commands::Commands(std::map<int, Client*> clientList, std::string port, std::string passWord) {
    this->clientList = clientList;
    this->port = port;
    this->passWord = passWord;
}

Request Commands::parseResponse(std::string response) {
    Request request;
    request.status = 0;
    
    if (response[0] == ' ' || response[0] == '\0' || response[0] == '\n')
        request.status = 1;

    std::istringstream iss(response);
    std::vector<std::string> args;

    std::string cmd;
    iss >> cmd;

    for (std::string arg; iss >> arg;)
        args.push_back(arg);

    if (args.empty())
        request.status = 1;

    request.cmd = cmd;
    request.args = args;
    return request;
}

std::string Commands::parseRequest(Request request, int fd) {
    std::string response;
    if (request.status == 1)
        response = "Parssing Error\r\n";
    else if (request.cmd == "connect")
        response = connect(request, fd);
    else if (request.cmd == "NICK")
        std::cout << "NICK: " << fd << std::endl;
    else
        response = "Unknown command\r\n";
    return response;
}

std::string Commands::connect(Request request, int fd) {
    std::string response;

    if (request.args.size() != 3)
        response = "Not enough parameters\r\n";
    if (request.args[0] != "localhost")
        return "Invalid server\r\n";
    if (request.args[1] != this->port)
        return "Invalid port\r\n";
    if (request.args[2] != this->passWord)
        return "Invalid password\r\n";
    if (this->clientList[fd] && this->clientList[fd]->getAuthenticated() == 1)
        return "Already connected\r\n";
    else {
        this->clientList[fd] = new Client(fd);
        this->clientList[fd]->setAuthenticated(1);
        std::cout << "Client " << this->clientList[fd]->getAuthenticated() << " connected" << std::endl;
        this->clientList[fd]->setNickName("Default");
        this->clientList[fd]->setUserName("Default");
        
        response = "Welcome to the Internet Relay Network " + this->clientList[fd]->getNickName() + "!" + this->clientList[fd]->getUserName() + "@localhost\r\n";
    }
    return response;
}

Commands::~Commands() {}