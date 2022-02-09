/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:27:07 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/09 18:55:50 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "ErrorMess.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


class Server {

public:

	// Coeplin's form
	
	Server();
	Server( Server const & other );
	~Server();

	Server & operator=( Server const & other );

	// Getters and Setters
	
	int getPort() const;
	std::string getPassword() const;	
	void setPort( int port ); 
	void setPassword( std::string passwrod );

	// Engine
	
	void parse();
	void ft_socket();

	// Commands
	
	void ft_time();


protected:

	// Types

	typedef void (Server::*func)( void );

	// Members
	
	int _port;
	std::string _password;
	std::string _name;
 	std::map< std::string,  func  > _functions;	

	// Member functions
	
	std::vector<std::string> & ft_split( std::string & str, std::vector<std::string> & vct );
	std::string & ft_tolower( std::string & str );
		
};
