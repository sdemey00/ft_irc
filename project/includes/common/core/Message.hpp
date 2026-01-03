/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:17 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/23 14:37:56 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>		// vector
#include <iostream>		// ostream

class Message {
	public:
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;
	std::string					trailing;
};

std::ostream& operator<<(std::ostream& os, const Message& msg);
