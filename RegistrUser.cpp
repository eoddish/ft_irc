/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistrUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:56:39 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/14 21:12:00 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ErrorMess.hpp"
#include "CmdMess.hpp"

#include <cctype>
#include <string>

/*std::string		Server::PassCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() == 0)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS));
	else if (this->getPassword() != Msg.getParamets()[0]) //Ошибка, непредусмотренная стандартом
		std::cout << "Uncorrect password!" << std::endl;
	else if (user.getStatusRegistr() == true) //Проверка на повторную ошибочную регистрацию
		return (PrintError("" , "", ERR_ALREADYREGISTRED));
	return ("");
}
*/
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

std::string		Server::NickCommand(Message &Msg, User *puser) {

	User user = *puser;
	std::string nickname = Msg.getParamets()[1];

	if (Msg.getParamets().size() == 1) {
		return (PrintError("", "", ERR_NONICKNAMEGIVEN));
	}
	else if (this->CorrectNick(Msg.getParamets()[1]) == false) {
		return (PrintError(Msg.getParamets()[1], "", ERR_ERRONEUSNICKNAME));
	}
	else if (this->CheckConcidence(Msg.getParamets()[1]) == true) {
		if (user.getStatusRegistr() == false)
			return (PrintError(Msg.getParamets()[1], "", ERR_NICKCOLLISION));
		else
			return (PrintError(Msg.getParamets()[1], "", ERR_NICKNAMEINUSE));
	}

	
	if ( !puser )
		user = User();
	user.setNickName(Msg.getParamets()[1]);
	_UsersCheck[nickname] = &user; 
	
	return ("");
}

std::string		Server::UserCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() < 3)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS));
	else if (user.getStatusRegistr() == true)
		return (PrintError("" , "", ERR_ALREADYREGISTRED));
	user.setUserName(Msg.getParamets()[1]);
	user.setRealName(Msg.getParamets()[2]);
	return (0);
}
/*
std::string		Server::OperCommand(Message &Msg, User &user) {

	std::string Password = Msg.getParamets()[1];
	if (Password.size() == 0)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS));
	// if ()
	// 	return (ERR_NOOPERHOST); //если сервер не настроен на поддержку клиенского хоста для сообщения OPER
	// if ()
	// 	return (ERR_PASSWDMISMATCH)// если пароль неверный или неуказан
	return (CmdMess(user, RPL_YOUREOPER, "", "", "", "", "", "", ""));
}
*/

std::string		Server::QuitCommand(Message &Msg, User &user ) {
	(void)user;
	std::cout << "QuitMessage" << std::endl;
	return ( Msg.getParamets()[0] );
}
