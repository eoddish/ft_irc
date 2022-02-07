/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:29:59 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/07 19:58:44 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sys/socket.h>

int Server::getPort( void ) const {

	return _port;
}

std::string Server::getPassword( void ) const {

	return _password;
}

void Server::setPort( int port ) {

	_port = port;
}

void Server::setPassword( std::string password ) {

	_password = password;
}

