/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:21:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/05/12 17:03:02 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Commands.hpp"

Commands::Commands() {}

Commands::~Commands() {}

Request Commands::parseResponse(std::string response) {
    Request request;

    std::cout << "Parsing response: " << response << std::endl;

    return request;
}

