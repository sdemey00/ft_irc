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

#include <cctype>	// isdigit

bool isdigit(char* str, const long unsigned int& len) {
	for (long unsigned int i = 0; i < len; i++) {
		if (!std::isdigit(str[i]))
			return 0;
	}
	return 1;
}
