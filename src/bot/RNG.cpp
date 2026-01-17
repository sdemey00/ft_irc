/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNG.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:43:56 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/29 13:41:22 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNG.hpp"

#include <cstdlib>
#include <ctime>

void	RNG::seed() { srand(time(0)); }
int		RNG::roll() { return (rand() % 6) + 1; }
int		RNG::toss() { return (rand() % 2); }
