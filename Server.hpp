/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:27:07 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/15 20:09:28 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "ErrorMess.hpp"
#include "CmdMess.hpp"
#include "User.hpp"
#include "Message.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>


#ifndef SERVER_HPP
# define SERVER_HPP

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
	
	std::string parse( std::string input , User & user );
	void ft_socket();


	
	// Commands
	
	std::string     PassCommand(Message &Msg, User &user);
    std::string     NickCommand(Message &Msg, User &user);
    std::string     UserCommand(Message &Msg, User &user);
    std::string     QuitCommand(Message &Msg, User &user);
    std::string     OperCommand(Message &Msg, User &user);


    bool    CorrectNick(std::string Nickname);
    bool    CheckConcidence(std::string CheckData);
	
	std::string ft_cap( Message &msg, User &user  );
	std::string ft_time( Message &msg, User &user );
	std::string ft_ping( Message &msg, User &user );


	std::map<std::string, User *>       _UsersCheck;
	std::map< int, User > 		_users;

protected:

	// Types

	typedef std::string (Server::*func)( Message &, User &);

	// Members
	
	int _port;
	std::string _password;
	std::string _name;
 	std::map< std::string,  func  > _functions;	

	// Member functions
	
	std::vector<std::string> & ft_split( std::string & str, std::vector<std::string> & vct );
	std::string & ft_tolower( std::string & str );
		
};
#endif
