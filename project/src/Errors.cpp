/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:13:25 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 13:37:03 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"

const char* Errors::PortError::what() const throw() { return "Port is not a number"; }
const char* Errors::SocketError::what() const throw() { return "Error on socket()"; }
const char* Errors::BindError::what() const throw() { return "Error on bind()"; }
const char* Errors::ListenError::what() const throw() { return "Error on listen()"; }
const char* Errors::AcceptError::what() const throw() { return "Error on accept()"; }