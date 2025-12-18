/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:34:40 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:36:13 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void	Message::msgPrint() {
	std::cout << "MESSAGE PRINT:" << std::endl;
	std::cout << "Prefix: " << prefix << std::endl;
	std::cout << "Command: " << command << std::endl;
	std::cout << "Params: ";
    for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); ++it) {
        std::cout << " " << *it << " |";
    }
	std::cout << std::endl;
}
