/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:10:50 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 13:37:16 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>

struct Errors {
	struct PortError 	: std::exception { virtual const char* what() const throw(); };
	struct SocketError 	: std::exception { virtual const char* what() const throw(); };
	struct BindError 	: std::exception { virtual const char* what() const throw(); };
	struct ListenError 	: std::exception { virtual const char* what() const throw(); };
	struct AcceptError 	: std::exception { virtual const char* what() const throw(); };
};