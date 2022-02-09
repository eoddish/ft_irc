/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:29:59 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/09 19:28:39 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( ) : _port( 0 ), _password( "default" ), _name( "ircserv" ) {

	_functions["time"] =  &Server::ft_time;
}

Server::Server( Server const & other ) {

	*this = other;
}

Server::~Server( ) {

}

Server & Server::operator=( Server const & other ) {

	if ( this != &other ) {

		_port = other._port;
		_password = other._password;
		_name = other._name;
	}

	return *this;
}

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

void  Server::ft_time( void ) {	

	time_t rawtime;
	time ( &rawtime );

	std::string t = ctime( &rawtime );

	std::cout << this->_name << " ";
	std::cout << t;

}


void Server::parse() {


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


	if ( _functions.find( vct[0] ) == _functions.end() ) {

		std::cerr << vct[0];
		PrintError( 421 );
		return;
	}

	(this->*_functions[vct[0]])();
}

void Server::ft_socket() {

	int server_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_size;

	server_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( server_sock < 0 )
		std::cout << "Socket error" << std::endl; 

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( _port );
	server_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );


	if ( bind( server_sock, ( struct sockaddr * ) & server_addr, sizeof( server_addr ) ) != 0 )
		std::cout << "Bind error" << std::endl;

	if ( listen( server_sock, 3 ) != 0 )
		std::cout << "Listen error" << std::endl;


	client_addr_size = sizeof( client_addr );

	while ( 1 ) {
		accept( server_sock, ( struct sockaddr * ) & client_addr, & client_addr_size );

		std::cout << "Connection established" << std::endl;
		std::string ip = inet_ntoa ( client_addr.sin_addr );


		std::cout << "Connection established with ip " << ip << std::endl;


		
	}

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
