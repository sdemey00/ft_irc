/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:23:54 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/22 11:55:23 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>		// cerr, endl
#include <exception>	// exception

#include "Client.hpp"	// Client

int main(int argc, char** argv) {
	argc--; argv++;
	if (argc != 4) {
		std::cerr << "Usage : <address> <port> <password> <nicknames>" << std::endl;
		return 1;
	}
	try {
		Client c(argv[0], argv[1], argv[2], argv[3]);
		c.run();
	} catch(std::exception &e) { std::cout << e.what() << "\n"; return 1; }
	return 0;
}