/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Verbose.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:07:44 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/15 12:05:24 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>	// string
#include <iostream>	// ostream

#ifndef VERBOSE
# define VERBOSE 0
#endif

class Verbose {
	std::ostream* _os;

public:
	Verbose(std::ostream& os);

	template<typename T>
	Verbose& operator<<(const T& value) {
		if (_os) { (*_os) << value; }
		return *this;
	}
};

extern Verbose verbose;
