/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Verbose.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:09:06 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/15 11:58:24 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Verbose.hpp"	// Verbose

#include <string>		// string
#include <iostream>		// ostream

Verbose verbose(std::cout);

Verbose::Verbose(std::ostream& os) {
	if (VERBOSE) { _os = &os; }
	else { _os = 0; }
}