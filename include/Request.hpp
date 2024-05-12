/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:14:37 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/12 16:57:25 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>

class Request {
private:
    std::string                 cmd;
    std::vector<std::string>    args;
    int                         status;
public:
    Request();
    Request(std::string cmd, std::vector<std::string> args, int status);
    ~Request();
};

#endif