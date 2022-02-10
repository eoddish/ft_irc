/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:29:59 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/10 21:01:44 by eoddish          ###   ########.fr       */
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


void Server::parse(  ) {


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
	int ret;
	int option = 1;
	int timeout;

	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_size;
	char buf1[512];
	char buf2[512];
	struct pollfd fds[200];
	int nfds = 1;

	// create a socket
	server_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( server_sock < 0 ) {

		perror( "socket() error" );
		exit( -1 );
	}

	// allow reusing
	ret = setsockopt( server_sock, SOL_SOCKET, SO_REUSEADDR, ( char * ) & option, sizeof( option ) );
	if ( ret < 0 ) {

		perror( "setsockopt() error" );
		close( server_sock );
		exit( -1 );
	}

	// set to non-blocking
	ret = fcntl( server_sock, F_SETFL, O_NONBLOCK );
	if ( ret < 0 ) {

		perror( "fcntl() error" );
		close( server_sock );
		exit( -1 );
	}

	// bind the socket
	memset( &server_addr, 0, sizeof( server_addr ) );
	server_addr.sin_family = AF_INET;
//	memcpy( &server_addr.sin_addr, &inaddr_any, sizeof( inaddr_any ) );
	server_addr.sin_port = htons( _port );
//	server_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	server_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind( server_sock, ( struct sockaddr * ) & server_addr, sizeof( server_addr ) );
	if ( ret < 0 ) {

		perror( "bind() error" );
		close( server_sock );
		exit( -1 );
	}

	// listen
	ret = listen( server_sock, 128 ); 
	if ( ret < 0 ) {

		perror( "listen() error" );
		close( server_sock );
		exit( -1 );
	}

	// set up socket
	memset( fds, 0, sizeof( fds ) );
	fds[0].fd = server_sock;
	fds[0].events = POLLIN;
	timeout = 3 * 60 * 1000;



	client_addr_size = sizeof( client_addr );

	do {


		// call poll
		ret = poll( fds, nfds, timeout );
		if ( ret < 0 ) {

			perror( "poll() error" );
			break;
		}

		if ( ret == 0 )

		int fd = accept( server_sock, ( struct sockaddr * ) & client_addr, & client_addr_size );

		std::cout << "Connection established" << std::endl;
		std::string ip = inet_ntoa( client_addr.sin_addr );
		unsigned short port = ntohs( client_addr.sin_port ); 


		std::cout << "Connection established with ip " << ip;
		std::cout << " and port " << port << std::endl;

		recv( fd, buf1, 512, 0 );
		std::cout << buf1;	
		
		std::string _nick = "eoddish";

		std::string sendline = "001 ";
		sendline.append( _nick );
		sendline.append( " :Welcome to the Internet Relay Network " );
		sendline.append( _nick );
		sendline.append( "\n" );

		strcpy( buf2, sendline.c_str() );
		send( fd, buf2, 512, 0 );

		recv( fd, buf1, 512, 0 );
		std::cout << buf1;

		recv( fd, buf1, 512, 0 );
		std::cout << buf1;
	
		
		//parse();
	} while ( true );

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
