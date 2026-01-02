/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:08:40 by mmichele          #+#    #+#             */
/*   Updated: 2026/01/02 15:05:27 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sighandler.hpp"

#include <iostream>	// cout

#include "Log.hpp"	// logger

void sighandler(int sig) {
	(void)sig;
	std::cout << std::endl;
	logger << "Ctrl-C catched, closing program.\n";
	g_run_state = 0;
}