/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:29:06 by mmichele          #+#    #+#             */
/*   Updated: 2026/01/01 16:04:25 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"

#include <string>	// string
#include <sstream>	// stringstream
#include <iomanip>	// setw
#include <iostream>	// cout
#include <ctime>	// time
#include <cstring>	// strcmp

std::ofstream	logger;

std::string Log::print_memory(const char* str, const unsigned int& length) {
	const unsigned int	width = 12;
	long int			left = length;
	std::stringstream	res;

	while (left > 0) {
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				res << std::setw(4) << static_cast<int>(str[i + length - left]);
			}
			else { res << "    "; }
			res << " ";
		}
		res << ": \"";
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				if (std::isprint(str[i + length - left]))
					res << str[i + length - left];
				else
					res << "⍰";
			}
		}
		res << "\"\n";
		left -= width;
	}
	return res.str();
}

std::string Log::time_label() {
	std::stringstream res;
	time_t ttime = time(0);
	struct tm* ltime = localtime(&ttime);

	res << "[";
	res << std::setfill('0') << std::setw(2) << ltime->tm_hour << ":";
	res << std::setfill('0') << std::setw(2) << ltime->tm_min << ":";
	res << std::setfill('0') << std::setw(2) << ltime->tm_sec << "] ";
	return res.str();
}

void Log::recv(bool complete, int fd, const char* str, const long unsigned int& len) {
	logger << Log::time_label() << " ";
	if (complete) {
		logger << "Complete      (";
		//if (std::strncmp(str, "PING", 4) != 0)
			std::cout << Log::time_label() << CLR_ORANGE << "Received     " << CLR_RESET << std::setw(3) << fd << " : " << str << std::endl;
	}
	else { logger << "RECV          ("; }
	logger << std::setw(3) << fd << ") :\n";
	logger << Log::print_memory(str, len) << std::flush;
}

void Log::send(int fd, const char* str, const long unsigned int& len) {
	logger << Log::time_label() << "SENT           (" << std::setw(3) << fd << ") : \n" << Log::print_memory(str, len) << std::flush;
	//if (std::strncmp(str + len - 4, "PONG", 4) != 0)
		std::cout << Log::time_label() << CLR_CYAN << "Sent         " << CLR_RESET << std::setw(3) << fd << " : " << str << std::endl;
}

void Log::disconnected(int fd, const std::string& nick) {
	logger << Log::time_label() << "Disconnected " << std::setw(3) << fd << " : " << nick << std::endl;
	std::cout << Log::time_label() << CLR_RED << "Disconnected " << CLR_RESET << std::setw(3) << fd << " : " << nick << std::endl;
}