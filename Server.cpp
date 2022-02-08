/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:29:59 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/08 20:43:39 by eoddish          ###   ########.fr       */
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

void  Server::ft_time( void ){	

	time_t rawtime;
	time ( &rawtime );

	std::string t = ctime( &rawtime );

	std::cout << t;  

}


void Server::parse() {

	_functions["time"] =  &Server::ft_time;

	std::string str;
	std::vector<std::string> vct;


	std::getline( std::cin, str );
	if ( str.size() > 510 )
		return;

	// CHECK IF THERE'S A PREFIX 
	if ( str[0] == ':' ) {

		str.erase( str.begin() );

		//std::string nick;
		//std::string user;
		//std::strign host;

		str.erase( 0, str.find(" ") );
	}
		

	vct = ft_split( str, vct );
	if ( vct.size() > 16 )
		return;

	vct[0] = ft_tolower( vct[0] );

	/*
	for ( std::vector<std::string>::iterator it = vct.begin(); it != vct.end(); ++it ) {

		std::cout << *it << std::endl;
	}	
	*/
	_functions[vct[0]]();
}

std::vector<std::string> & Server::ft_split( std::string & str, std::vector<std::string> & vct ) {

	size_t start = 0;
	size_t end = 0;

	while ( true ) {

		for ( start = end; str[start] == ' '; )
			++start;

		end = str.find( " ", start );

		if ( end == std::string::npos ) {

			if ( start !=  str.size() )
				vct.push_back( str.substr( start, std::string::npos ) );
			break;
		}
		
		vct.push_back( str.substr( start, end - start ) );
	}
	
	return vct;
}

std::string & Server::ft_tolower( std::string & str ) {

	for ( std::string::iterator it = str.begin(); it != str.end(); ++it ) {

		*it = std::tolower( *it );
	}

	return str;
}
