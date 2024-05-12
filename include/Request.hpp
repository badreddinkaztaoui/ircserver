/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:14:37 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/12 18:41:48 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>

class Request {
public:
    std::string                 cmd;
    std::vector<std::string>    args;
    int                         status;

    Request();
    Request(std::string cmd, std::vector<std::string> args, int status);
    ~Request();
};

#endif