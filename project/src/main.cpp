/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:06:41 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 11:52:47 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

int main(int argc, char** argv) {
	argc--; argv++;
	if (argc != 2) {
		std::cerr << "Usage : ./ft_irc <port> <password>" << std::endl;
		return 1;
	}
	Server s;
	try { s = Server(argv[0], argv[1]); }
	catch (std::exception &e) { std::cerr << "Port is not number" << std::endl; return 1; }
	s.run();
	return 0;
}