/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:13:25 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:32:20 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"	// Errors

const char* Errors::Port::what()				const throw() { return "Port is not a number"; }
const char* Errors::Socket::what()				const throw() { return "Error on socket()"; }
const char* Errors::Fcntl::what()				const throw() { return "Error on fcntl()"; }
const char* Errors::SetSockOpt::what()			const throw() { return "Error on setsockopt()"; }
const char* Errors::Bind::what()				const throw() { return "Error on bind()"; }
const char* Errors::Listen::what()				const throw() { return "Error on listen()"; }
const char* Errors::Accept::what()				const throw() { return "Error on accept()"; }
const char* Errors::InvalidBufferSize::what()	const throw() { return "BUFFER_SIZE is invalid."; }
const char* Errors::Connect::what()				const throw() { return "Error on connect() : Server might not up."; }
const char* Errors::Recv::what()				const throw() { return "Error on recv()"; }
