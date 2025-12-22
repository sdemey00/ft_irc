/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/22 16:43:00 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Client.hpp"

#include <unistd.h>			// close
#include <poll.h>			// POLLIN

Client::Client() : read_buffer("") {
	stash[0] = 0;
	stash[BUFFER_SIZE] = 0;
}
