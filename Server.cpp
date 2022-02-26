/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:29:59 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/26 21:21:53 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( ) : _port( 0 ), _password( "default" ), _name( "ircserv" ) {

	ft_config();

	_functions["time"] =  &Server::ft_time;
	_functions["ping"] =  &Server::ft_ping;
	_functions["cap"] = &Server::ft_cap;
	_functions["pass"] = &Server::PassCommand;
	_functions["nick"] = &Server::NickCommand;
	_functions["user"] = &Server::UserCommand;
	_functions["oper"] = &Server::OperCommand;
	_functions["quit"] = &Server::QuitCommand;
	_functions["privmsg"] = &Server::PrivmsgCommand;
	_functions["dcc"] = &Server::commandDcc;
	
	//_functions["join"] = &Server::JoinCommand;

}

Server::Server( Server const & other ) {

	*this = other;
}

Server::~Server( ) {

	for ( std::map< std::string, User*>::iterator it = _UsersCheck.begin(); it != _UsersCheck.end(); ++it ) 
		delete it->second;
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


std::string  Server::ft_time( Message &msg, User &user ) {	
	
	std::vector<std::string> & vct = msg.getParamets(); 

	std::cout << vct[0] << std::endl;

	time_t rawtime;
	time ( &rawtime );

	std::string res;
	res.append( "391 " );
	res.append( user.getNickName() );
	res.append( " ircserv :" );
	res.append( ctime( &rawtime ) );

	res.erase( res.end() - 1 );

	return res;

}

std::string Server::ft_ping( Message &msg, User &user ) {

	(void) user;
	std::vector<std::string> & vct  = msg.getParamets();
	std::string res = "PONG ";
	res.append( vct[1] );

	return res;
}


std::string Server::ft_cap( Message &msg, User &user ) {
	
	(void) user;
	std::vector<std::string> & vct = msg.getParamets();
	std::cout << vct[0] << std::endl;


	return "";
}

std::string Server::parse( std::string str, User & user ) {

	Message msg;
	std::vector<std::string> & vct = msg.getParamets();

	// CHECK IF THERE'S A PREFIX 
	if ( str[0] == ':' ) {

		str.erase( str.begin() );
		str.erase( 0, str.find(" ") );
	}

	vct = ft_split( str, vct );
	//if ( vct.size() > 16 )
	//	return;

	vct[0] = ft_tolower( vct[0] );

	if ( _functions.find( vct[0] ) == _functions.end() ) {

		std::string res;
		res.append( PrintError( vct[0], "", 421, user ) );
		return res; 
	}
	msg.setCommand( vct[0] );
	if ( vct[0] != "pass" && vct[0] != "nick" && vct[0] != "user" ) {
		if ( !user.getStatusRegistr() ) {
			return PrintError( user.getNickName(), "", ERR_NOTREGISTERED, user );
		}
	}
	return (this->*_functions[vct[0]])( msg, user );
}

void Server::ft_socket() {

	int  ret, option = 1;
	int server_sock = -1, fd = -1;
	bool close_conn, end_server = false, compress_array = false;
	char buf[512];
	struct sockaddr_in server_addr, client_addr;
	int timeout;
	struct pollfd fds[1024];
	int nfds = 1, cur_size = 0, i, j;
	socklen_t client_addr_size;

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
	server_addr.sin_port = htons( _port );
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
	timeout = -1;




	do {


		// call poll
		ret = poll( fds, nfds, timeout );
		if ( ret < 0 ) {

			perror( "poll() error" );
			break;
		}
		if ( ret == 0 ) {

			std::cout << "poll() timed out" << std::endl;
			break;
		}

		// find readable fds
		cur_size = nfds;
		for ( i = 0; i < cur_size; i++ ) {

			if ( fds[i].revents == 0 )
				continue;

			if ( !(fds[i].revents &  POLLIN) ) {

				/*if ( fds[i].revents & POLLHUP )
					std::cout << "POLLHUP" << std::endl;
				if ( fds[i].revents & POLLNVAL )
					std::cout << "POLLNVAL" << std::endl;
				if ( fds[i].revents & POLLERR )
					std::cout << "POLLERR" << std::endl;
				if ( fds[i].revents & POLLIN )
					std::cout << "POLLIN" << std::endl;
					*/

				std::cout << "Error: revents is not POLLIN!" << std::endl;
				end_server = true;
				break;
			}

			client_addr_size = sizeof( client_addr );
			if ( fds[i].fd == server_sock ) {

				do {

					// accept connections
					fd = accept( server_sock, ( struct sockaddr * ) & client_addr, & client_addr_size );
					if ( fd < 0 ) {

						if ( errno != EWOULDBLOCK ) {

							perror( "accept() error" );
							end_server = true;
						}
						break;
					}

					std::cout << "Connection established" << std::endl;
					std::string ip = inet_ntoa( client_addr.sin_addr );
					unsigned short port = ntohs( client_addr.sin_port ); 
					std::cout << "Connection established with ip " << ip;
					std::cout << " and port " << port << std::endl;

					fds[nfds].fd = fd;
					fds[nfds].events = POLLIN;
					++nfds;
					User*tmp = new User;
					(this->_users)[fd] = tmp;
					(this->_users)[fd]->setFd( fd );

				} while ( fd != -1 );

			} else {


				close_conn = false;

				do {

					// receive data
					bzero( buf, sizeof( buf ) );
					ret = recv( fds[i].fd, buf, sizeof( buf ), 0 );
					if ( ret < 0 ) {

						if ( errno != EWOULDBLOCK ) {

							perror( "recv() error" );
							close_conn = true;
						}
						break;
					}
					if ( ret == 0 ) {

						std::cout << "Connection closed" << std::endl;
						close_conn = true;
						break;
					}

					//len = ret;
					std::istringstream iss( buf );
					std::string str;

					while ( std::getline( iss, str ) ) {

					if ( !str.empty() && *(str.end() - 1) == '\r' )
						str.erase( str.end() - 1 );
					std::cout << "recv: " << str << std::endl;
					
					std::string sendline;

						sendline = parse( str, *_users[fds[i].fd] );

					// an error or quit command called
					int err = 0;
					if ( sendline.size() >= 12 ) {
						err = std::atoi( sendline.substr( 0, 3 ).c_str() );
					}
					//std::cout << "*" << err << "*" << std::endl;
					if ( sendline == "quit" || (err >= 433 && err <= 441)) {
	
						std::cout << "Connection closed" << std::endl;
						close_conn = true;
						break;
					}
					
					sendline = ":ircserv " + sendline;

					sendline.append ( "\r\n" );

					std::cout << "send: " << sendline;

					// send data

					char buf2[512];
					bzero( buf2, sizeof( buf2 ) );
					strcpy( buf2, sendline.data() );

					ret = send( fds[i].fd, buf2, sendline.size(), 0 );
					if ( ret < 0 ) {

						perror( "send() error" );
						close_conn = true;
						break;
					}
				}
					if ( close_conn )
						break;

				} while ( true );

				// clean closed connection
				if ( close_conn ) {

					if ( _UsersCheck.find( _users[fds[i].fd]->getNickName() ) != _UsersCheck.end() ) {
						_UsersCheck[_users[fds[i].fd]->getNickName()]->setStatusOnline( false );
						_UsersCheck[_users[fds[i].fd]->getNickName()]->setStatusRegistr( false );
						_UsersCheck[_users[fds[i].fd]->getNickName()]->setStatusPass( false );
					}
					_users.erase( fds[i].fd );

					
					close( fds[i].fd );
					fds[i].fd = -1;
					compress_array = true;
				}


			}

		}

		// compress fds
		if ( compress_array ) {

			compress_array = false;
			for ( i = 0; i < nfds; i++ ) {

				if ( fds[i].fd == -1 ) {

					for ( j = i; j < nfds; j++ )
						fds[j].fd = fds[j + 1].fd;
						
					i--;
					nfds--;
				}
			}
		}

	} while ( end_server == false );

	// clean up open sockets
	for ( i = 0; i < nfds; i++ ) {

		if ( fds[i].fd >= 0 )
			close( fds[i].fd );
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

std::string Server::commandDcc( Message &msg,User &user) {

	if ( msg.getParamets()[1] == "send" )
		return commandDccSend(msg, user);
	else if ( msg.getParamets()[1] == "get" )
		return commandDccGet(msg, user);
	return("");
}

std::string Server::commandDccSend(Message &msg,User &user) {

	(void)user;
	std::string nick = msg.getParamets()[2];	
	std::ifstream ifs(msg.getParamets()[3], std::ifstream::binary);

	ret = recv( fds[i].fd, buf, sizeof( buf ), 0 );
	if ( !ifs.is_open() )
		return ( msg.getParamets()[3] + ": No such file or directory");

	std::string strname = msg.getParamets()[3];
	int len =  strname.size() - strname.rfind("/") - 1;
	strname = strname.substr( strname.rfind( "/") + 1, len);
	_streamNames[nick] = strname;
	_streamUsers[nick] = user.getNickName();

	char c;
	while ( ifs.get(c) ) {
		_streams[nick].push_back(c);
	}
	SendMessage( *_UsersCheck[nick], "DCC SEND from " + user.getNickName() ); 
	return ("DCC SEND request sent to " + nick + ": " + strname);
}

std::string Server::commandDccGet(Message &msg,User &user) {

	(void)msg;
	std::ofstream ofs;
	if ( _streamNames.find( user.getNickName() ) == _streamNames.end() )
		return ("");
	ofs.open(_streamNames[user.getNickName()], std::ofstream::binary);
	if (!ofs.is_open() ) {
		std::cout << "Failed to open" << std::endl;
		return ("");
	}

	std::string str = _streamNames[user.getNickName()];
	std::string sender = _streamUsers[user.getNickName()];
	
	ofs << _streams[user.getNickName()];
	_streams.erase(user.getNickName());
	_streamNames.erase(user.getNickName());
	_streamUsers.erase(user.getNickName());
	
	SendMessage( *_UsersCheck[sender], "DCC sent file " + str + " for " + user.getNickName() ); 
	return ("DCC received file " + str + " from " + _UsersCheck[sender]->getNickName());
}



void Server::ft_config( ) {

	_opers.erase( _opers.begin(), _opers.end() );

	std::ifstream ifs ("config.JSON", std::ifstream::in);

	std::string str;

	while ( std::getline( ifs, str ) ) {

		if ( str.find( "operators" ) != str.npos ) {

				while ( std::getline( ifs, str ) && str.find( "}" ) == str.npos ) {
	
				size_t k = str.find( "\"" );
				if ( k == str.npos ) 
					continue;
				k++;
				size_t m = str.find( "\"",  k + 1 );
				if ( m == str.npos )
					continue;
				std::string oper = str.substr( k, m - k );
				str.erase( 0, m + 1 );
				k = str.find( "\"");
				k++;
				if ( k == str.npos )
					continue;
				m = str.find( "\"",  k + 1 );
				if ( m == str.npos )
					continue;
				std::string pass = str.substr( k, m - k );
				_opers[oper] = pass;

			}
				
		}
	
	}

}

bool	SendMessage(User &user,std::string Mess) {

	std::string sendline = Mess;
	sendline.append ( "\r\n" );

					char buf2[512];
					bzero( buf2, sizeof( buf2 ) );
					strcpy( buf2, sendline.data() );


	std::cout << "send: " << sendline;
	if (Mess.size() > 0)
		send(user.getFd(), buf2, sendline.size(), 0);
	return true;
}
