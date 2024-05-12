/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:27:01 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/12 18:23:27 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include "Request.hpp"

class Commands
{
	private:
		Commands();
		~Commands();
	public:
        // Commands
		std::string connect(Request request, int fd);
        std::string nick(Request request, int fd);
        std::string user(Request request, int fd);
        std::string join(Request request, int fd);
        std::string join_message(std::string channel, int fd);
        std::string mode(Request request, int fd);
        std::string topic(Request request, int fd);
        std::string invite(Request request, int fd);
        std::string privmsg(Request request, int fd);
        std::string kick(Request request, int fd);
        std::string quit(Request request, int fd);
};

/* ----------------------- */
/* -- Utility functions -- */
/* ----------------------- */


/* ----------------------- */
/* -- String functions --- */
/* ----------------------- */

#endif