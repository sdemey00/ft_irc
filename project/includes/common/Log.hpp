/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:25:42 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:15:53 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>	// ofstream
#include <string>	// string

#define CLR_RESET		"\e[0m"
#define CLR_GRAY		"\e[30m"
#define CLR_RED			"\e[31m"
#define CLR_GREEN		"\e[32m"
#define CLR_ORANGE		"\e[33m"
#define CLR_BLUE		"\e[34m"
#define CLR_PURPLE		"\e[35m"
#define CLR_CYAN		"\e[36m"
#define CLR_WHITE		"\e[37m"
#define CLR_DEFAULT		"\e[38m"

extern std::ofstream logger;

struct Log {
	static std::string print_memory(const char* str, const unsigned int& length);
	static std::string time_label();
	static void recv(bool complete, int fd, const char* str, const long unsigned int& len);
	static void send(int fd, const char* str, const long unsigned int& len);
	static void disconnected(int fd, const std::string& nick);
};
