/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:18 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:19 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Message.hpp"
#include <string>

class Parser {
public:
    static Message  parse(const std::string& line);
};
