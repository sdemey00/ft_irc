/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:07:44 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 20:25:05 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>	// string

#ifndef VERBOSE
# define VERBOSE 0
#endif

void verbose(const std::string& s);
