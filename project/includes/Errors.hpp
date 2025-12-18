/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:10:50 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/16 09:17:57 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>	// exception

struct Errors {
	struct Port 				: std::exception { virtual const char* what() const throw(); };
	struct Socket 				: std::exception { virtual const char* what() const throw(); };
	struct Fcntl 				: std::exception { virtual const char* what() const throw(); };
	struct SetSockOpt 			: std::exception { virtual const char* what() const throw(); };
	struct Bind 				: std::exception { virtual const char* what() const throw(); };
	struct Listen 				: std::exception { virtual const char* what() const throw(); };
	struct Accept 				: std::exception { virtual const char* what() const throw(); };
	struct InvalidBufferSize 	: std::exception { virtual const char* what() const throw(); };
};
