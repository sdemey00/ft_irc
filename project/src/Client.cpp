/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/21 02:54:07 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <unistd.h>			// close

Client::Client() :
	read_buffer(""),
	sock_len(sizeof(sock_addr)),
	init(0)
{
	stash[0] = 0;
	stash[BUFFER_SIZE] = 0;
}

Client::~Client() {
	if (init)
		close(fd);
}
