/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelOper.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:37:38 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/18 14:51:43 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"
#include "../ErrorMess.hpp"
#include "../CmdMess.hpp"

#include <cctype>
#include <string>

bool	Server::CheckChannels(std::string CheckName) {
	if (this->_ChannelCheck.empty() == true)
		return (false);
	try {
		this->_ChannelCheck.at(CheckName);
		return (true);
	}
	catch (std::exception &e) {}
	return (false);
}

bool	Server::CorrectCommandName(std::string NameChannel) {
	if (NameChannel.size() < 2 && NameChannel.size() > 200)
		return (false);
	else if (NameChannel[0] != '&' && NameChannel[0] != '#')
		return (false);
	else if (NameChannel.find_first_of(' ', NameChannel.size()) != std::string::npos
			|| NameChannel.find_first_of(',', NameChannel.size()) != std::string::npos
			|| NameChannel.find_first_of(7, NameChannel.size()) != std::string::npos)
		return (false);
	return (true);
}

// std::string		Server::ModeCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().size() < 1)
// 		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));

// 	std::string	Name = Msg.getParamets()[0];

// 	if (Name[0] == '#' || Name[0] == '&') {
// 		if (this->CheckChannels(Name) == false)
// 			return (PrintError(Name, "", ERR_NOSUCHCHANNEL, user));
// 		else if (this->_ChannelCheck.at(Name)->CheckUsers(user.getNickName()) == false)
// 			return PrintError(Name, "", ERR_NOTONCHANNEL, user);
// 		else if (this->_ChannelCheck.at(Name)->CheckOperator(user.getNickName()) == false)
// 			return (PrintError(Name, "", ERR_CHANOPRIVSNEEDED, user));
// 		else if (Msg.getParamets().size() == 1) {
// 			std::string flags; 
// 			for (int i = 0; i < this->_ChannelCheck.at(Name)->getFlags().size(); i++) {
// 				flags = this->_ChannelCheck.at(Name)->getFlags()[i];
// 			}
// 			return (CmdMess(user, RPL_CHANNELMODEIS, Name, flags, "", "", "", "", ""));
// 		}
// 		else if (Msg.getParamets()[1][0] != '+' && Msg.getParamets()[1][0] != '-')
// 			return (PrintError(Msg.getParamets()[1]), "", ERR_UNKNOWNMODE, user);
// 		else {
// 			if (Msg.getParamets()[1] == "+o" || Msg.getParamets()[1] == "-o") {
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 				std::string	NickName = Msg.getParamets()[2];
// 				if (this->_ChannelCheck.at(Name)->CheckUsers(NickName) == false)
// 					return ("");
// 				else {
// 					if (Msg.getParamets()[1] == "+o") {
// 						this->_ChannelCheck.at(Name)->getUsers().at(NickName)->setFlagsStatus('o');
// 						this->_ChannelCheck.at(Name)->getOperatorChannel().push_back(this->_ChannelCheck.at(Name)->getUsers().at(NickName));
// 					}
// 					else {
// 						this->_ChannelCheck.at(Name)->getUsers().at(NickName)->popFlag('o');
// 						this->_ChannelCheck.at(Name)->popOperator(NickName);
// 					}
// 				}
// 			}
// 			else if (Msg.getParamets()[1] == "+p") {
// 				this->_ChannelCheck.at(Name)->pushFlag('p');
// 			}
// 			else if (Msg.getParamets()[1] == "-p") {
// 				this->_ChannelCheck.at(Name)->popFlag('p');
// 			}
// 			else if (Msg.getParamets()[1] == "+s") {
// 				this->_ChannelCheck.at(Name)->pushFlag('s');
// 			}
// 			else if (Msg.getParamets()[1] == "-s") {
// 				this->_ChannelCheck.at(Name)->popFlag('s');
// 			}
// 			else if (Msg.getParamets()[1] == "+i") {
// 				this->_ChannelCheck.at(Name)->pushFlag('i');
// 			}
// 			else if (Msg.getParamets()[1] == "-i") {
// 				this->_ChannelCheck.at(Name)->popFlag('i');
// 			}
// 			else if (Msg.getParamets()[1] == "+n") {
// 				this->_ChannelCheck.at(Name)->pushFlag('n');
// 			}
// 			else if (Msg.getParamets()[1] == "-n") {
// 				this->_ChannelCheck.at(Name)->popFlag('n');
// 			}
// 			else if (Msg.getParamets()[1] == "+m") {
// 				this->_ChannelCheck.at(Name)->pushFlag('m');
// 			}
// 			else if (Msg.getParamets()[1] == "-m") {
// 				this->_ChannelCheck.at(Name)->popFlag('m');
// 			}
// 			else if (Msg.getParamets()[1] == "+l") {
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 				this->_ChannelCheck.at(Name)->setLimitUsers(std::atoi(Msg.getParamets()[2].c_str()));
// 			}
// 			else if (Msg.getParamets()[1] == "-l") {
// 				this->_ChannelCheck.at(Name)->setLimitUsers(0);
// 			}
// 			else if (Msg.getParamets()[1] == "+b") {
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 				this->_ChannelCheck.at(Name)->pushBanMask(Msg.getParamets()[2]);
// 				return (CmdMess(user, RPL_BANLIST, Name, Msg.getParamets()[2]));
// 			}
// 			else if (Msg.getParamets()[1] == "-b") {
// 				this->_ChannelCheck.at(Name)->popBanMask(Msg.getParamets()[2]);
// 				return (CmdMess(user, RPL_ENDOFBANLIST, Name, "", "", "", "", "", ""));
// 			}
// 			else if (Msg.getParamets()[1] == "+v" || Msg.getParamets()[1] == "-v") {
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 				std::string	NickName = Msg.getParamets()[2];
// 				if (this->_ChannelCheck.at(Name)->CheckUsers(NickName) == false)
// 					return ;
// 				else {
// 					if (Msg.getParamets()[1] == "+v") {
// 						this->_ChannelCheck.at(Name)->getUsers().at(NickName)->setFlagsStatus('v');
// 						this->_ChannelCheck.at(Name)->getSpeakersUsers().push_back(this->_ChannelCheck.at(Name)->getUsers().at(NickName));
// 					}
// 					else {
// 						this->_ChannelCheck.at(Name)->getUsers().at(NickName)->popFlag('v');
// 						this->_ChannelCheck.at(Name)->popSpeaker(NickName);
// 					}
// 				}
// 			}
// 			else if (Msg.getParamets()[1] == "+k") {
// 				if (this->_ChannelCheck.at(Name)->getPassword().size())
// 					return (PrintError(Name, "", ERR_KEYSET, user));
// 				if (Msg.getParamets().size() < 3)
// 					return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS));
// 				this->_ChannelCheck.at(Name)->setPassword(Msg.getParamets()[2]);
// 			}
// 			else if (Msg.getParamets()[1] == "-k") {
// 				this->_ChannelCheck.at(Name)->setPassword("");
// 			}
// 			else {
// 				return (PrintError("", "", ERR_UMODEUNKNOWNFLAG, user));
// 			}
// 		}	
// 	} // работа с каналами
// 	else {
// 		std::string	WhoIsFlag;
// 		std::string Flag;
// 		if (Msg.getParamets().size() == 1) {
// 			WhoIsFlag = user.getNickName();
// 			Flag = Msg.getParamets()[0];
// 		}
// 		else if (Msg.getParamets().size() == 2) {
// 			if (Msg.getParamets()[0].empty() == true)
// 				return (PrintError(user.getNickName(), "", ERR_NOSUCHNICK, user));
// 			WhoIsFlag = Msg.getParamets()[0];
// 			Flag = Msg.getParamets()[1];
// 		}
// 		if (Msg.getParamets()[1][0] != '+' && Msg.getParamets()[1][0] != '-')
// 			return (PrintError(Msg.getParamets()[1]), "", ERR_UNKNOWNMODE, user);
// 		else if (Flag == "+i") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->setFlagsStatus('i');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "-i") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->popFlag('i');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "+s") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->setFlagsStatus('s');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "-s") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->popFlag('s');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "+o") {
// 			try {
// 				if (WhoIsFlag != user.getNickName())
// 					this->_UsersCheck.at(WhoIsFlag)->setFlagsStatus('o');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "-o") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->popFlag('o');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "+w") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->setFlagsStatus('w');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else if (Flag == "-w") {
// 			try {
// 				this->_UsersCheck.at(WhoIsFlag)->popFlag('w');
// 			}
// 			catch(const std::exception& e) {}
// 		}
// 		else {
// 			return (PrintError("", "", ERR_UMODEUNKNOWNFLAG, user));
// 		}
// 	} // работа с пользователями

// 	// return (ERR_USERSDONTMATCH);
// 	// return (RPL_UMODEIS);
// 	return ("");
// }

// std::string		Server::TopicCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().size() < 1)
// 		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));

// 	std::string NameChannel = Msg.getParamets()[0];
// 	std::string NewTopic = Msg.getParamets()[1];
	
// 	if (this->CheckChannels(NameChannel) == false)
// 		return (PrintError(NameChannel, "", ERR_NOTONCHANNEL, user));
// 	else if (this->_ChannelCheck.at(NameChannel)->CheckUsers(user.getNickName()) == false)
// 		return (PrintError(NameChannel, "", ERR_NOTONCHANNEL, user));
// 	else {
// 		if (Msg.getParamets().size() == 1) {
// 			if (this->_ChannelCheck.at(NameChannel)->getTopic().empty() == true)
// 				return (RPL_NOTOPIC); // FFFFFFFFFFFF
// 			return (RPL_TOPIC); // FFFFFFFFFFFF
// 		}
// 		else {
// 			if (this->_ChannelCheck.at(NameChannel)->CheckFlags('t') == true) {
// 				if (this->_ChannelCheck.at(NameChannel)->CheckOperator(user.getNickName()) == false)
// 					return (PrintError(NameChannel, "", ERR_CHANOPRIVSNEEDED, user));
// 				this->_ChannelCheck.at(NameChannel)->setTopic(NewTopic);
// 			}
// 			this->_ChannelCheck.at(NameChannel)->setTopic(NewTopic);
// 		}
// 	}
// 	return ("");
// }

std::string		Server::JoinCommand(Message &Msg, User &user) {
	if (Msg.getParamets().empty() == true)
		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
	else {
		std::queue<std::string> NameChannel = split(Msg.getParamets()[0], ',');
		std::queue<std::string> Keys;
		if (Msg.getParamets().size() == 2)
			Keys = split(Msg.getParamets()[1], ',');
		for (; NameChannel.size() > 0; NameChannel.pop()) {
			if (this->CheckChannels(NameChannel.front()) == false && this->CorrectCommandName(NameChannel.front()) == false)
				return (PrintError(NameChannel.front(), "", ERR_NOSUCHCHANNEL, user));
			else if (user.getHowManyChannel() == user.getLimitChannel()) {
				return (PrintError(NameChannel.front(), "", ERR_TOOMANYCHANNELS, user));
			}
			else if (Keys.size() > 0 && this->_ChannelCheck.at(NameChannel.front())->getPassword().size() > 0) {
				if (Keys.front() != this->_ChannelCheck.at(NameChannel.front())->getPassword()) {
					return (PrintError(NameChannel.front(), "", ERR_BADCHANNELKEY, user));
				}
				Keys.pop();
			}
			else if (this->_ChannelCheck.at(NameChannel.front())->CheckFlags('l') == true) {
				if (this->_ChannelCheck.at(NameChannel.front())->getLinitUsers() == this->_ChannelCheck.at(NameChannel.front())->getUsers().empty() == true)
					return (PrintError(NameChannel.front(), "", ERR_CHANNELISFULL, user));
			}
			else if (this->_ChannelCheck.at(NameChannel.front())->CheckFlags('i') == true) {
				return (PrintError(NameChannel.front(), "", ERR_INVITEONLYCHAN, user));
			}
			else if (this->_ChannelCheck.at(NameChannel.front())->getBanMask().size() > 0) {
				if (this->_ChannelCheck.at(NameChannel.front())->CheckBanMask(user.getNickName()) == true)
					return (PrintError(NameChannel.front(), "", ERR_BANNEDFROMCHAN, user));
			}
			else {
				if (this->CheckChannels(NameChannel.front()) == false)
				{
					Channel	NewChannel = new Channel(NameChannel.front());
					this->_ChannelCheck.insert(NameChannel.front(), *NewChannel);
					this->_ChannelCheck.at(NameChannel.front())->pushOperator(user);
				}
				this->_ChannelCheck.at(NameChannel.front())->pushUser(user.getNickName(), user);
				this->_UsersCheck.at(user.getUserName())->pushChannel(this->_ChannelCheck.at(NameChannel.front()));
				++user;
				return(CmdMess(user, RPL_TOPIC, NameChannel.front(), this->_ChannelCheck.at(NameChannel.front())->getTopic(), "", "", "", "", ""));
			}
		}
	}
	return ("");
}

// std::string		Server::InviteCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().size() < 1)
// 		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 	std::string NickName = Msg.getParamets()[0];
// 	std::string NameChannel = Msg.getParamets()[1];
// 	if (NickName.empty() == true)
// 		return (PrintError(user.getNickName(), "", ERR_NOSUCHNICK, user));
// 	else if (this->CheckChannels(NameChannel) == false)
// 		return (PrintError(NameChannel, "", ERR_NOTONCHANNEL, user));
// 	else if (this->CheckConcidence(NickName) == false)
// 		return (PrintError(user.getNickName(), "", ERR_NOSUCHNICK, user));
// 	else if (this->_ChannelCheck.at(NameChannel)->CheckUsers(NickName) == true)
// 		return (PrintError(NickName, NameChannel, ERR_USERONCHANNEL, user));
// 	else {
// 		if (this->_ChannelCheck.at(NameChannel)->CheckFlags('i') == true) {
// 			if (this->_ChannelCheck.at(NameChannel)->CheckOperator(user.getNickName()) == false)
// 				return (PrintError(NameChannel, "", ERR_CHANOPRIVSNEEDED, user));
// 		}
// 		this->_ChannelCheck.at(NameChannel)->pushUser(NickName, this->ImputUser(Msg.getParamets()[0])); //this->_UsersCheck.at(NickName)
// 	}
// 	if (this->_UsersCheck.at(NickName)->getMessageAway().empty == false)
// 		CmdMess(user, RPL_AWAY, NickName, this->_UsersCheck.at(NickName)->getMessageAway(), "", "", "", "", "");
// 	return (CmdMess(user, RPL_INVITING, NameChannel, NickName));
// }

// std::string		Server::KickCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().size() < 2)
// 		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 	std::string	Name = Msg.getParamets()[0];
// 	std::string NickName = Msg.getParamets()[1];
// 	std::string message;
// 	if (this->CheckChannels(Name) == false)
// 		return (PrintError(Name, "", ERR_NOSUCHCHANNEL, user));
// 	else if (this->_ChannelCheck.at(Name)->CheckUsers(user.getNickName()) == false)
// 		return (PrintError(Name, "", ERR_NOTONCHANNEL, user));
// 	else {
// 		if (this->_ChannelCheck.at(Name)->CheckOperator(user.getNickName()) == false)
// 			return (PrintError(Name, "", ERR_CHANOPRIVSNEEDED, user));
// 		this->_ChannelCheck.at(Name)->popUser(NickName);
// 		--(this->_UsersCheck.at(NickName));
// 		message = "KICK " +  this->_ChannelCheck.at(Name)->getNameChannel() + " " + NickName + " :";
// 		if (Msg.getParamets().size() == 3)
// 			message += Msg.getParamets()[2];
// 		else
// 			message += user.getNickName();
// 	}
// 	return (message);
// }

// std::string		Server::PartCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().size() < 1)
// 		return (PrintError(Msg.getCommand(), "", ERR_NEEDMOREPARAMS, user));
// 	std::queue<std::string>	NameChannel = ft_split(Msg.getParamets()[0]);
// 	// for (int i = 0; i < Msg.getParamets().size(); i++) {
// 	// 	if (this->CheckChannels(Msg.getParamets()[i]) == true) {
// 	// 		if (this->_ChannelCheck.at(Msg.getParamets()[i])->CheckUsers(user.getNickName()) == true) {
// 	// 			this->_ChannelCheck.at(Msg.getParamets()[i])->popUser(user.getNickName());
// 	// 			//вывести сообщение
// 	// 		}
// 	for (; NameChannel.size() > 0; NameChannel.pop()) {
// 		if (this->CheckChannels(NameChannel.front()) == true) {
// 			if (this->_ChannelCheck.at(NameChannel.front())->CheckUsers(user.getNickName()) == true) {
// 				this->_ChannelCheck.at(NameChannel.front())->popUser(user.getNickName());
// 				SendMessage(user, user.getNickName() + " gouing out of: " + NameChannel.front() + "\n");
// 			}
// 			else
// 				return (PrintError(NameChannel, "", ERR_NOTONCHANNEL, user));
// 		}
// 		else {
// 			return (PrintError(Name, "", ERR_NOSUCHCHANNEL, user));
// 		}
// 	}
// 	return ("");
// }

// std::string		Server::NamesCommand(Message &Msg, User &user) {
// 	if (Msg.getParamets().empty() == true) {
// 		std::vector<std::string>	AllUsers;
		
// 		std::map<std::string, User *>::iterator map_beg = this->_UsersCheck.begin();
// 		std::map<std::string, User *>::iterator map_end = this->_UsersCheck.end();
		
// 		for (; map_beg != map_end; ++map_beg) {
// 			AllUsers.push_back((*map_beg).second->getNickName());
// 		}
		
// 		std::map<std::string, Channel *>::iterator Chan_beg = this->_ChannelCheck.begin();
// 		std::map<std::string, Channel *>::iterator Chan_end = this->_ChannelCheck.end();
		
// 		for (; Chan_beg != Chan_end; ++Chan_beg) {
// 			if ((*Chan_beg).second->CheckFlags('p') == false && (*Chan_beg).second->CheckFlags('s') == false) {
// 				SendMessage(user, CmdMess(user, RPL_NAMREPLY, (*Chan_beg).first, (*Chan_beg).second->PrintUsers(), "", "", "", "", ""));
// 				for (int i = 0; i < AllUsers.size(); i++) {
// 					if ((*Chan_beg).second->CheckUsers(AllUsers[i]))
// 						AllUsers.erase((*Chan_beg) + i--);
// 				}
// 			}
// 		}

// 		std::string ListNames;
// 		for (int i = 0; i < AllUsers.size(); i++) {
// 			ListNames += AllUsers[i];
// 			if (i != (AllUsers.size() - 1))
// 				ListNames += " ";
// 		}
// 		SendMessage(user, ListNames);
// 	}
// 	else {
// 		std::queue<std::string>	NameChannel = ft_split(Msg.getParamets()[0]);
// 		for (; NameChannel.size() > 0; NameChannel.pop()) {
// 			if (this->CheckChannels(NameChannel.front()) == true) {
// 				if (this->_ChannelCheck.at(NameChannel.front())->CheckFlags('p') == false 
// 					&& this->_ChannelCheck.at(NameChannel.front())->CheckFlags('s') == false) {
// 						std::string ListUsers = this->_ChannelCheck.at(NameChannel.front())->PrintUsers();
// 						SendMessage(user, CmdMess(user, RPL_NAMREPLY, NameChannel.front(), ListUsers, "", "", "", "", ""));
// 					}
// 				}
// 			else
// 				return (CmdMess(user, RPL_ENDOFNAMES, NameChannel.front(), "", "", "", "", "", ""));
// 		}
// 	}
// 	return ("");
// }

// std::string		Server::ListCommand(Message &Msg, User &user) {
	
// 	std::vector<std::string> ListChannel;
	
// 	if (Msg.getParamets().empty() == true) {
// 		std::map<std::string, Channel *>::iterator map_beg = this->_ChannelCheck.begin();
// 		std::map<std::string, Channel *>::iterator map_end = this->_ChannelCheck.end();
// 		for (; map_beg != map_end; ++map_beg) {
// 			ListChannel.push_back((*map_beg).first);
// 		}
// 	}
// 	else {
// 		std::queue<std::string>	NameChannel = ft_split(Msg.getParamets()[0]);
// 		for (; NameChannel.size() > 0; NameChannel.pop()) {
// 			if (this->CheckChannels(NameChannel.front()) == false)
// 				return ("");
// 			ListChannel.push_back(this->_ChannelCheck.at(NameChannel.front())->getNameChannel());
// 		}
// 	}
// 	SendMessage(user, CmdMess(user, RPL_LISTSTART, "", "", "", "", "", "", ""));
// 	for (size_t i = 0; i < ListChannel.size(); i++) {
// 		SendMessage(user, CmdMess(user, RPL_LIST, ListChannel[i], "", "", "", "", "", ""));
// 		return (RPL_LIST);
// 	}
// 	return (CmdMess(user, RPL_LISTEND, "", "", "", "", "", "", ""));
// }
