/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:34:40 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:42:17 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/Message.hpp"

#include <iostream>		// ostream

std::ostream& operator<<(std::ostream& os, const Message& msg) {
	os << "MESSAGE PRINT:" << std::endl;
	os << "Prefix: " << msg.prefix << std::endl;
	os << "Command: " << msg.command << std::endl;
	os << "Params: ";
	for (std::vector<std::string>::const_iterator it = msg.params.begin(); it != msg.params.end(); ++it) {
		os << " " << *it << " |";
	}
	os << std::endl;
	return os;
}
