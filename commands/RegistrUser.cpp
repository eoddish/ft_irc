/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistrUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:56:39 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/18 18:20:36 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"
#include "../ErrorMess.hpp"
#include "../CmdMess.hpp"

#include <cctype>
#include <string>

std::string		Server::PassCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() == 1)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user ));
	else if (this->getPassword() != Msg.getParamets()[1]) //Ошибка, непредусмотренная стандартом
	{
		std::cout << "Uncorrect password!" << std::endl;
		return ("quit");
	}
	else if (user.getStatusRegistr() == true) //Проверка на повторную ошибочную регистрацию
		return (PrintError("" , "", ERR_ALREADYREGISTRED, user ));
	user.setStatusPass( true );
	return ("");
}

bool	Server::CorrectNick(std::string Nickname) {
	if (Nickname.size() > 9)
		return (false);
	std::string SpecSymbol = "\\-[]^{}";
	for (unsigned long i = 0; i < Nickname.size(); i++) {
		if (isprint(Nickname[i]) == false)
			return (false);
		else if (isalnum(Nickname[i]) == false
			&& (Nickname.find_first_of(SpecSymbol)) == std::string::npos)
			return (false);
	}
	return (true);
}

bool	Server::CheckConcidence(std::string CheckData) {
	// if (this->_UsersCheck.empty() == true)
	// 	return (false);
	// for (int i = 0; this->_UsersCheck[i] != *this->_UsersCheck.end(); i++) {
	// 	if (this->_UsersCheck[i]->getNickName() == CheckData)
	// 		return (true);
	// }
	// return (false);

	if (this->_UsersCheck.empty() == true)
		return (false);
	try {
		this->_UsersCheck.at(CheckData);
		return (true);
	}
	catch (std::exception &e) {}
	return (false);
}

std::string		Server::NickCommand(Message &Msg, User & user) {
	std::string nickname = Msg.getParamets()[1];

	// check password
	if ( !user.getStatusPass() )
		return( "quit" );

	// check errors 
	if (Msg.getParamets().size() == 1) {
		return (PrintError("", "", ERR_NONICKNAMEGIVEN, user ));
	}
	else if (this->CorrectNick(Msg.getParamets()[1]) == false) {
		return ( PrintError(Msg.getParamets()[1], "", ERR_ERRONEUSNICKNAME, user ));
	}
	else if (this->CheckConcidence(Msg.getParamets()[1]) == true) {
		// existing user

		if ( _UsersCheck[nickname]->getStatusRegistr() == false ) {

		std::cout << "*" << std::endl;
			_UsersCheck[nickname]->setFd( user.getFd() );
			delete _users[user.getFd()];
			_users[user.getFd()] = _UsersCheck[nickname];
		}
		else if (user.getStatusRegistr() == false)
			return ( PrintError(Msg.getParamets()[1], "", ERR_NICKCOLLISION, user ));
		else
			return (PrintError(Msg.getParamets()[1], "", ERR_NICKNAMEINUSE, user ));
	} else {

		

		// regular nick command
		if ( user.getStatusRegistr() == true ) {

			_UsersCheck[nickname] = _UsersCheck[user.getNickName()]; 
			_UsersCheck.erase( user.getNickName() );
			user.setNickName(Msg.getParamets()[1]);

			return ( "You're now known as " + nickname);
		}
		
		// new user	
		user.setNickName(Msg.getParamets()[1]);
		_UsersCheck[nickname] = _users[user.getFd()]; 

		
	}
	return ( "" );
}

std::string		Server::UserCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() < 5)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user ));
	else if (user.getStatusRegistr() == true)
		return (PrintError("" , "", ERR_ALREADYREGISTRED, user ));
	user.setUserName(Msg.getParamets()[1]);
	std::string realname;

	realname = Msg.getParamets()[4];
	if ( Msg.getParamets()[4][0] == ':' )
		realname.erase( realname.begin() );	
	
	size_t i = 5;
	while ( i < Msg.getParamets().size() ) {

		realname += " " + Msg.getParamets()[i];
		i++;
	}

	user.setRealName( realname );
	user.setStatusRegistr( true );

	std::string result;
	result = "001 " + user.getNickName() + " :Welcome to the Internet Relay Network " + user.getNickName() + "\r\n";
	result += ":ircserv 002 eoddish :Your host is ircserv, running version 1.0\r\n";
	result += ":ircserv 003 eoddish :This server was created <date>\r\n";
	result +=":ircserv 004 eoddish :ircserv 1.0 <available user modes> <available channel modes>";



	return (result);
}

	 std::string     Server::OperCommand(Message &Msg, User &user) {

	std::string Password = Msg.getParamets()[1];
	if (Password.size() == 0)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user ));
	// if ()
	// 	return (ERR_NOOPERHOST); //если сервер не настроен на поддержку клиенского хоста для сообщения OPER
	// if ()
	// 	return (ERR_PASSWDMISMATCH)// если пароль неверный или неуказан
	return (CmdMess(user, RPL_YOUREOPER, "", "", "", "", "", "", ""));
}


std::string		Server::QuitCommand(Message &Msg, User &user ) {

	std::cout << user.getNickName() <<  " quits" << std::endl;
	//user.setStatusRegistr( false );
	//_users.erase( user.getFd() ); 
	return ( Msg.getParamets()[0] );
}
