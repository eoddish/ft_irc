/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:08:23 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/07 19:37:30 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "Server.hpp"


int main( int argc, char **argv ) {

	if ( argc != 3 ) {

		std::cout << "./ircserv [PORT] [PASSWORD]" << std::endl;
		return -1;
	}

	Server srv;

	srv.setPort( atoi( argv[1] ) );
	srv.setPassword( argv[2] );

	std::cout <<  "port: " << srv.getPort();
	std::cout <<  " " << "password: " << srv.getPassword() << std::endl;

	return 0;
}
