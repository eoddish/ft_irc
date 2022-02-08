/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:08:23 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/08 20:14:49 by eoddish          ###   ########.fr       */
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

	//srv._functions["time"] =  &srv.ft_time;
	srv.parse(  );

	return 0;
}
