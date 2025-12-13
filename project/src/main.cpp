/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:06:41 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 16:12:40 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char** argv) {
	argc--; argv++;
	if (argc != 2) {
		std::cerr << "Usage : ./ft_irc <port> <password>" << std::endl;
		return 1;
	}
	Server s;
	try { s = Server(argv[0], argv[1]); }
	catch (std::exception &e) { std::cerr << e.what() << std::endl; return 1; }
	s.run();
	return 0;
}