/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 04:16:19 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 14:20:29 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Utils.hpp"

void    connectedMsg(int fd) {

    std::string msg = "";
    msg += "";
    msg += "\t\x03" "06██████╗  █████╗ ███╗   ██╗        ██╗██████╗  ██████╗\x03\n";
    msg += "\t\x03" "06██╔══██╗██╔══██╗████╗  ██║        ██║██╔══██╗██╔════╝\x03\n";
    msg += "\t\x03" "06██████╔╝███████║██╔██╗ ██║        ██║██████╔╝██║     \x03\n";
    msg += "\t\x03" "06██╔══██╗██╔══██╗██║╚██╗██║        ██║██╔══██╗██║     \x03\n";
    msg += "\t\x03" "06██████╔╝██║  ██║██║ ╚████║███████╗██║██║  ██║╚██████╗\x03\n";
    msg += "\t\x03" "06╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝  ╚═╝ ╚═════╝\x03\n\n";

    msg += "\t\x03" "08░▀█▀░█▀█░░█▀▀░█▀▀░▀█▀░░█▀▀░▀█▀░█▀█░█▀▄░▀█▀░█▀▀░█▀▄░░░░\x03\n";
    msg += "\t\x03" "08░░█░░█░█░░█░█░█▀▀░░█░░░▀▀█░░█░░█▀█░█▀▄░░█░░█▀▀░█░█░░▀░\x03\n";
    msg += "\t\x03" "08░░▀░░▀▀▀░░▀▀▀░▀▀▀░░▀░░░▀▀▀░░▀░░▀░▀░▀░▀░░▀░░▀▀▀░▀▀░░░▀░\x03\n\n";

    msg += "\t\x03" "15 STEP 1: Verify server password 🗝️\x03\n";
    msg += "\t\x03" "03\x02/PASS\x03 <password>\n";
    msg += "\t\x03" "15 STEP 2: Set your nickname 👤\x03\n";
    msg += "\t\x03" "03\x02/NICK\x03 <nickname>)\n";
    msg += "\t\x03" "15 STEP 3: Set your username 📝\x03\n";
    msg += "\t\x03" "03\x02/USER\x03 <username> <hostname> <servername> :<realname>\n\n";

    send(fd, msg.c_str(), msg.length(), 0);
}

void    registredMsg(int fd) {
    std::string msg = "";
    msg += "\t\x03" "08┓ ┏  ┓                                  \x03\n";
    msg += "\t\x03" "08┃┃┃┏┓┃┏┏┓┏┳┓┏┓  ╋┏┓  ┏┓┓┏┏┓  ┏┏┓┏┓┓┏┏┓┏┓\x03\n";
    msg += "\t\x03" "08┗┻┛┗ ┗┗┗┛┛┗┗┗   ┗┗┛  ┗┛┗┻┛   ┛┗ ┛ ┗┛┗ ┛ \x03\n";

    send(fd, msg.c_str(), msg.length(), 0);
}

std::string toStr(int num) {
    std::stringstream str;
    str << num;
    return str.str();
}

Channel* findChannel(const std::string& name, std::map<std::string, Channel*>& channels) {
    for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if (it->first == name) {
            return it->second;
        }
    }
    return NULL; 
}

bool    isValidChannelName(const std::string& name) {
    if (name[0] != '#')
        return false;
    return true;
}