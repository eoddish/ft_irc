/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendingMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:30:13 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/21 19:17:04 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"
#include "../Message.hpp"
#include "../ErrorMess.hpp"
#include "../CmdMess.hpp"

#include <cctype>
#include <string>


std::string		Server::PrivmsgCommand(Message &Msg, User &user) {
	if (Msg.getParamets().size() == 1)
		return (PrintError(user.getNickName(), "", ERR_NORECIPIENT, user));
	if (Msg.getParamets().size() == 2)
		return (PrintError("", "", ERR_NOTEXTTOSEND, user));
	
	std::queue<std::string>	Reseivers = split(Msg.getParamets()[1], ',');
	
	std::cout << Reseivers.size() << std::endl;
	for (; Reseivers.size() > 0; Reseivers.pop()) {
		// if ()
			// return (ERR_TOOMANYTARGETS); //
		
		
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
				this->_ChannelCheck.at(Reseivers.front())->SendUsers(Msg.getCommand(), Msg.getParamets()[1], user);
			}
		}
		
		else if (this->CheckConcidence(Reseivers.front()) == true) {
			if (Msg.getCommand() == "NOTICE") {
				if (this->_UsersCheck.at(Reseivers.front())->CheckUserFlags('s') == false)
					SendMessage(*(_UsersCheck.at(Reseivers.front())), Msg.getParamets()[1]);
			}

			else {
				
				std::string sendline = ":" + user.getNickName() + " PRIVMSG";
				for ( size_t i = 1; i < Msg.getParamets().size(); i++ )
					sendline += " " +  Msg.getParamets()[i];
				SendMessage(*(_UsersCheck.at(Reseivers.front())), sendline);
				if (this->_UsersCheck.at(Reseivers.front())->getMessageAway().size() > 0)
				{
					SendMessage(user, CmdMess(*(_UsersCheck.at(Reseivers.front())), RPL_AWAY, Reseivers.front(), this->_UsersCheck.at(Reseivers.front())->getMessageAway(), "", "", "", "", ""));
				}

			}
		}
		
		else
			return (PrintError(Reseivers.front(), "", ERR_NOSUCHNICK, user));
			
	}
	// if ()
//		return (ERR_WILDTOPLEVEL);
	// if ()
	// 	return (ERR_NOTOPLEVEL);
	return ("");
}
/*
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
			SendMessage(CmdMess(user, RPL_WHOISIDLE,ListNames.front(), this->_UsersCheck.at(ListNames.front()))); //???????????????????? ?????????????? ??????????, ?????????????????? ?? "??????????????" ??????????
			SendMessage(CmdMess(user, RPL_ENDOFWHOIS, ListNames.front(), "", "", "", "", "", ""));
		}
	}
	return ("");
}

std::string		Server::WhoWasCommand(Message &Msg, User &user) {
	if (Msg.getParamets().empty() == true) {
		return (PrintError("", "", ERR_NONICKNAMEGIVEN, user));
	}
	
	std::queue<std::string> ResultSearch = this->_HistoryUser.PrintOldUsers(Msg.getParamets()[0]);

	if (ResultSearch.empty() == true)
		return (PrintError(Msg.getParamets()[0], "", ERR_WASNOSUCHNICK, user));

	int	NumberMess = 0;
	if (Msg.getParamets().size() == 2) {
		NumberMess = atoi(Msg.getParamets()[1].c_str());
	}
	int	NumIter = 0;
	for (; ResultSearch.size() > 0; ResultSearch.pop()) {
		if (NumberMess != 0 && NumberMess == NumIter)
			break;
		SendMessage(CmdMess(user, RPL_WHOWASUSER, ResultSearch.front()));
		NumIter++;
	}
	
	return (CmdMess(user, RPL_ENDOFWHOWAS, Msg.getMessage()[0], "", "", "", "", "", "",""));
}
*/
