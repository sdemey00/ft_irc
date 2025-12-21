/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:23:54 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/21 04:25:10 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>	// cerr, endl

int main(int argc, char** argv) {
	argc--; argv++;
	if (argc != 2) {
		std::cerr << "Usage : <port> <password>" << std::endl;
		return 1;
	}
	
	return 0;
}