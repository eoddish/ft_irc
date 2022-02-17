/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:27:07 by eoddish           #+#    #+#             */
<<<<<<< Updated upstream
<<<<<<< Updated upstream
/*   Updated: 2022/02/17 19:29:56 by nagrivan         ###   ########.fr       */
=======
/*   Updated: 2022/02/17 20:28:58 by eoddish          ###   ########.fr       */
>>>>>>> Stashed changes
=======
/*   Updated: 2022/02/17 20:28:58 by eoddish          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <queue>
#include <cstdlib>
#include "User.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "CmdMess.hpp"
#include "ErrorMess.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>

class Server {

public:

	Server();
	Server( Server const & other );
	~Server();

	Server & operator=( Server const & other );

	int getPort() const;
	std::string getPassword() const;	
	void setPort( int port ); 
	void setPassword( std::string passwrod );
	
	std::string parse( std::string input , User & user );
	void ft_socket();

		
	std::string ft_cap( Message &msg, User &user  );
	std::string ft_time( Message &msg, User &user );
	std::string ft_ping( Message &msg, User &user );

private:

	typedef std::string (Server::*func)( Message &, User &);
	int _port;
	std::string _password;

	std::map<std::string, User *>		_UsersCheck;
	std::map<std::string, Channel *>	_ChannelCheck;
	std::map<std::string, User *>		_IRC_operator;
	std::map< int, User > 				_users;
	
	std::string _name;
 	std::map< std::string,  func  > _functions;	

	// команды IRC
	std::string		PassCommand(Message &Msg, User &user);
	std::string		NickCommand(Message &Msg, User &user);
	std::string		UserCommand(Message &Msg, User &user);
	std::string		OperCommand(Message &Msg, User &user);
	std::string		QuitCommand(Message &Msg, User &user);

	std::string		ModeCommand(Message &Msg, User &user);
	std::string		TopicCommand(Message &Msg, User &user);
	std::string		JoinCommand(Message &Msg, User &user);
	std::string		InviteCommand(Message &Msg, User &user);
	std::string		KickCommand(Message &Msg, User &user);
	std::string		PartCommand(Message &Msg, User &user);

	std::string		PrivmsgCommand(Message &Msg, User &user);
	std::string		AwayCommand(Message &Msg, User &user);
	std::string		NoticeCommand(Message &Msg, User &user);
	std::string		NamesCommand(Message &Msg, User &user);
	std::string		ListCommand(Message &Msg, User &user);
	std::string		WhoCommand(Message &Msg, User &user);
	std::string		WhoIsCommand(Message &Msg, User &user);
	std::string		WhoWasCommand(Message &Msg, User &user);

	bool	CorrectNick(std::string Nickname);
	bool	CorrectCommandName(std::string NameChannel);
	bool	CheckConcidence(std::string CheckData);
	bool	CheckOperators(std::string NickName);
	bool	CheckChannels(std::string CheckName);

	User*	ImputUser(std::string NickName);

	std::vector<std::string> & ft_split( std::string & str, std::vector<std::string> & vct );
	std::string & ft_tolower( std::string & str );
};

std::queue<std::string>	split(std::string Str, char Delimiter);
bool	SendMessage(User &user,std::string Mess);
std::queue<std::string>	ListMaskUser(std::string Mask, bool Param);
