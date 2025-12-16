/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:06:41 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/16 08:46:40 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>		// cerr, endl
#include <exception>	// exception

#include "Server.hpp"	// Server

int main(int argc, char** argv) {
	argc--; argv++;
	if (argc != 2) {
		std::cerr << "Usage : ./ft_irc <port> <password>\n";
		return 1;
	}
	try {
		Server s(argv[0], argv[1]);
		s.run();
	}
	catch (std::exception &e) { std::cerr << e.what() << "\n"; return 1; }
	return 0;
}