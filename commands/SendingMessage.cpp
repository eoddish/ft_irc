/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendingMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:30:13 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/18 20:17:12 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Server.hpp"
#include "ErrorMess.hpp"
#include "CmdMess.hpp"

#include <cctype>
#include <string>


std::string		Server::PrivmsgCommand(Message &Msg, User &user) {

	if (Msg.getReceiver().size() == 0)
		return (PrintError(user.getNickName(), "", ERR_NORECIPIENT, user));
	if (Msg.getParamets().size() == 1)
		return (PrintError("", "", ERR_NOTEXTTOSEND, user));
	
	std::queue<std::string>	Reseivers = ft_split(Msg.getParamets()[0], ",");
	
	for (; Reseivers.size() > 0; Reseivers.pop()) {
		
		// if ()
			// return (ERR_TOOMANYTARGETS);
		
		if (this->CheckChannels(Reseivers.front()) == true) {

			if (this->_ChannelCheck.at(Reseivers.front())->CheckUsers(user.getNickName()) == false
				&& this->_ChannelCheck.at(Reseivers.front())->CheckFlags('n'))
				return (PrintError(Reseivers.front(), "", ERR_CANNOTSENDTOCHAN, user));

			else if (this->_ChannelCheck.at(Reseivers.front())->CheckFlags('m')) {
				if (this->_ChannelCheck.at(Reseivers.front())->CheckOperator(user.getNickName()) == false
					&& this->_ChannelCheck.at(Reseivers.front())->CheckSpeakers(user.getNickName()) == false)
					return (PrintError(Reseivers.front(), "", ERR_CANNOTSENDTOCHAN, user));
			}
		
			else {
				if (this->_ChannelCheck.at(Reseivers.front()))
				this->_ChannelCheck.at(Reseivers.front())->SendUsers(Msg.getCommand(), getParamets()[1], user);
			}
		}
		
		else if (this->CheckConcidence(Reseivers.front()) == true) {
			if (Msg.getCommand() == "NOTICE") {
				if (this->_UsersCheck.at(Reseivers.front())->CheckUserFlags('s') == false)
					SendMessage(this->_UsersCheck.at(Reseivers.front()), Msg.getParamets()[1]);
			}
			else {
				SendMessage(this->_UsersCheck.at(Reseivers.front()), Msg.getParamets()[1]);
				if (this->_UsersCheck.at(Reseivers.front())->getMessageAway().size > 0);
					SendMessage(user, CmdMess(this->_UsersCheck.at(Reseivers.front()), RPL_AWAY, this->_UsersCheck.at(Reseivers.front()), this->_UsersCheck.at(Reseivers.front())->getMessageAway(), "", "", "", "", ""));
			}
		}
		
		else
			return (PrintError(Reseivers.front(), "", ERR_NOSUCHNICK, user));
	}
	// if ()
		return (ERR_WILDTOPLEVEL);
	// if ()
	// 	return (ERR_NOTOPLEVEL);
	return ("");
}

std::string		Server::AwayCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() == 0) {
		user.setMessageAway("");
		return (CmdMess(user, RPL_UNAWAY, "", "", "", "", "", "", ""));
	}
	user.setMessageAway(Msg.getParamets()[0]);
	return (CmdMess(user, RPL_NOWAWAY, "", "", "", "", "", "", ""));
}

std::string		Server::NoticeCommand(Message &Msg, User &user) {
	return (this->PrivmsgCommand(Msg, user));
}

std::string		Server::WhoCommand(Message &Msg, User &user) {
	
	std::queue<std::string> ListNickNames;
	if (Msg.getParamets().size() == 0)
		return ("");
	if (Msg.getParamets()[0].empty() == true) {
		if (Msg.getParamets()[1] == "o")
			ListNickNames = ListMaskUser("", true);
		else
			ListNickNames = ListMaskUser("", false);
	}
	else {
		if (Msg.getParamets()[1] == "o")
			ListNickNames = ListMaskUser(Msg.getParamets()[0], true);
		else
			ListNickNames = ListMaskUser(Msg.getParamets()[0], false);
	}
	for (; ListNickNames.size() > 0; ListNickNames.pop()) {
		SendMessage(CmdMess(user, RPL_WHOREPLY, this->_UsersCheck.at(ListNickNames.front())->PrintInfo(), this->_UsersCheck.at(ListNickNames.front())->getRealName(), "", "", "", "", "", ""));
		return (CmdMess(user, RPL_ENDOFWHO, ListNickNames.front(), "", "", "", "", "", ""));
	}
}

std::string		Server::WhoIsCommand(Message &Msg, User &user) {
	if (Msg.getParamets().empty() == true) {
		return (PrintError("", "", ERR_NONICKNAMEGIVEN, user));
	}
	else {
		std::queue<std::string>	ListNames = split(Msg.getParamets()[0], ',');
		
		for (; ListNames.size() > 0; ListNames.pop()) {
			
			if (this->CheckConcidence(ListNames.front()) == false) {
				SendMessage(PrintError(Msg.getParamets()[0], "", ERR_NOSUCHNICK, user));
			}
			
			if (this->CheckOperators(ListNames.front()) == true) {
				SendMessage(CmdMess(user, RPL_WHOISOPERATOR, this->_IRC_operator.at(ListNames.front())));
			}
			else {
				SendMessage(CmdMess(user, RPL_WHOISUSER, this->_UsersCheck.at(ListNames.front())->getNickName(), this->_UsersCheck.at(ListNames.front())->getUserName(),
						"", this->_UsersCheck.at(ListNames.front())->getRealName(), "", "", ""));
			}
			SendMessage(CmdMess(user, RPL_WHOISCHANNELS, this->_UsersCheck.at(ListNames.front())->PrintInfo(), "", "", "", "", "", ""));
			if ( this->_UsersCheck.at(ListNames.front())->getMessageAway().size() > 0)
				SendMessage(CmdMess(user, RPL_AWAY, ListNames.front(), this->_UsersCheck.at(ListNames.front())->getMessageAway(), "", "", "", "", ""));
			SendMessage(CmdMess(user, RPL_WHOISIDLE,ListNames.front(), this->_UsersCheck.at(ListNames.front()))); //необходимо вывести время, прошедшее с "простоя" юзера
			SendMessage(CmdMess(user, RPL_ENDOFWHOIS, ListNames.front(), "", "", "", "", "", ""));
		}
	}
	return ("");
}

std::string		Server::WhoWasCommand(Message &Msg, User &user) {
	if (Msg.getParamets().empty() == true) {
		return (PrintError("", "", ERR_NONICKNAMEGIVEN, user));
	}

	
	// return (PrintError(,, ERR_NONICKNAMEGIVEN, user));
	return (CmdMess(user, RPL_WHOWASUSER, ));
	return (CmdMess(user, RPL_ENDOFWHOWAS, ));
	return (CmdMess(user, RPL_WHOISSERVER, ));
	return (PrintError(,, ERR_WASNOSUCHNICK, user));
}
