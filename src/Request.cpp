/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:17:46 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/12 16:55:04 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Request.hpp"

Request::Request() {
    this->status = 0;
}

Request::Request(std::string cmd, std::vector<std::string> args, int status): cmd(cmd), args(args), status(status) {}

Request::~Request() {}