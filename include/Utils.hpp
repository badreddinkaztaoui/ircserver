/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 04:17:14 by bkaztaou          #+#    #+#             */
/*   Updated: 2024/06/03 14:15:36 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <map>
#include "Channel.hpp"

std::string toStr(int num);
Channel*    findChannel(const std::string& name, std::map<std::string, Channel*>& channels);
bool        isValidChannelName(const std::string& name);
void        connectedMsg(int fd);
void        registredMsg(int fd);


#endif