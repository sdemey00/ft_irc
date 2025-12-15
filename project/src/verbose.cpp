/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:09:06 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 20:25:36 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbose.hpp"	// verbose

#include <string>		// string
#include <iostream>		// cout

void verbose(const std::string& s) {
	if (VERBOSE)
		std::cout << s;
}