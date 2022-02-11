/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:08:23 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/11 19:32:48 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "Server.hpp"
#include "ErrorMess.hpp"


int main( int argc, char **argv ) {

	if ( argc != 3 ) {

		std::cout << "./ircserv [PORT] [PASSWORD]" << std::endl;
		return -1;
	}

	Server srv;

	srv.setPort( atoi( argv[1] ) );
	srv.setPassword( argv[2] );

	srv.ft_socket();
//	srv.parse( );

	return 0;
}
