/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:25:42 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/19 21:21:18 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>	// ofstream
#include <string>	// string

extern std::ofstream logger;

struct Log {
	static std::string print_memory(const char* str, const unsigned int& length);
	static std::string time_label();
	static void recv(bool complete, int fd, const char* str, const long unsigned int& len);
	static void send(int fd, const char* str, const long unsigned int& len);
	static void disconnected(int fd, const std::string& nick);
};
