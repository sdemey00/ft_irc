/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:12:48 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/22 15:19:13 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

#include <cctype>		// isdigit
#include <string>		// size_t, string
#include <cstdlib>		// strtol
#include <cstring>		// strlen
#include <cerrno>		// errno
#include <climits>		// INT_MAX

bool isdigit(char* str, const long unsigned int& len) {
	for (long unsigned int i = 0; i < len; i++) {
		if (!std::isdigit(str[i]))
			return 0;
	}
	return 1;
}

bool	isValidName(const std::string &nick) {
	for (size_t i = 0; i < nick.length(); i++) {
		if ((!std::isdigit(nick[i]) && !std::isalpha(nick[i]) && nick[i] != '_')
			|| nick[i] == '#') {
			return (0) ;
		}
	}
	return (1) ;
}

bool	parsePositiveInt(const std::string &s, int &out) {
    char *end;
    errno = 0;
	char *str = (char*)s.c_str();
	if (!isdigit(str, std::strlen(str)))
		return (false);
    long value = std::strtol(s.c_str(), &end, 10);
    if (*end != '\0' || errno != 0 || value < 0 || value > INT_MAX)
        return (false);
    out = static_cast<int>(value);
    return (true);
}