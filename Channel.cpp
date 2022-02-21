/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:43:36 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/21 17:29:49 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string ChannelName) : _NameChannel(ChannelName) {}

Channel::~Channel() {}

Channel::Channel(const Channel &copy) {
	*this = copy;
}

Channel&	Channel::operator= (const Channel &copy) {
	if (this != &copy) {
		this->_NameChannel = copy._NameChannel;
		this->_OperatorChannel = copy._OperatorChannel;
		this->_Users = copy._Users;
	}
	return *this;
}

std::string	Channel::getNameChannel(void) const {
	return (this->_NameChannel);
}

std::string	Channel::getPassword(void) const {
	return (this->_Password);
}

std::string	Channel::getTopic(void) const {
	return (this->_Topic);
}

std::map<std::string, User *>	Channel::getUsers(void) {
	return (this->_Users);
}

std::vector<User *>	Channel::getOperatorChannel(void) {
	return (this->_OperatorChannel);
}

bool	Channel::CheckUsers(std::string	Name) {
	// if (this->_Users.empty() == true)
	// 	return (false);
	// for (int i = 0; this->_Users[i] != *this->_Users.end(); i++) {
	// 	if (this->_Users[i]->getNickName() == Name)
	// 		return (true);
	// }
	// return (false);
	if (this->_Users.empty() == true)
		return (false);
	try {
		this->_Users.at(Name);
		return (true);
	}
	catch (std::exception &e) {}
	return (false);
}

bool	Channel::CheckOperator(std::string Name) {
	for (int i = 0; this->_OperatorChannel[i] != *this->_OperatorChannel.end(); i++) {
		if (this->_OperatorChannel[i]->getNickName() == Name)
			return (true);
	}
	return (false);
}

bool	Channel::CheckSpeakers(std::string Name) {
	for (int i = 0; this->_SpeakersUser[i] != *this->_SpeakersUser.end(); i++) {
		if (this->_SpeakersUser[i]->getNickName() == Name)
			return (true);
	}
	return (false);
}

bool	Channel::CheckFlags(const char Flag) {
	for (int i = 0; this->_Flags[i] != *this->_Flags.end(); i++) {
		if (this->_Flags[i] == Flag)
			return (true);
	}
	return (false);
}

std::string 	Channel::PrintUsers(void) {
	std::string StrUsers;

	std::map<std::string, User *>::iterator UserBeg = this->_Users.begin();
	std::map<std::string, User *>::iterator UserEnd = this->_Users.end();
	for (; UserBeg != UserEnd; ) {
		StrUsers += "[ ";
		if (this->CheckOperator((*UserBeg).first) == true)
			StrUsers += "@";
		if (this->CheckSpeakers((*UserBeg).first) == true)
			StrUsers += "+";
		StrUsers += (*UserBeg).first + "]";
		if ((++UserBeg) != UserEnd)
			StrUsers += " ";
	}
	return (StrUsers);
}

void	Channel::pushOperator(User &NewOper) {
	this->_OperatorChannel.push_back(&NewOper);
}

void	Channel::popOperator(std::string Name) {
	if (this->_OperatorChannel.empty() == true)
		return ;
	std::vector<User *>::iterator	it_begin = this->_OperatorChannel.begin();
	std::vector<User *>::iterator	it_end = this->_OperatorChannel.end();
	for (; it_begin != it_end; it_begin++) {
		if ((*it_begin)->getNickName() == Name) {
			delete *it_begin;
			this->_OperatorChannel.erase(it_begin);
			return ;
		}
	}
}

void	Channel::pushUser(std::string Key, User &NewUser) {
	this->_Users[Key] = &NewUser;
}

void	Channel::popUser(std::string Name) {
	if (this->_Users.empty() == true)
		return ;
	this->_Users.erase(Name);
}

void	Channel::pushSpeaker(User &NewSpeak) {
	this->_SpeakersUser.push_back(&NewSpeak);
}

void	Channel::popSpeaker(std::string Name) {
	if (this->_SpeakersUser.empty() == true)
		return ;
	std::vector<User *>::iterator	it_begin = this->_SpeakersUser.begin();
	std::vector<User *>::iterator	it_end = this->_SpeakersUser.end();
	for (; it_begin != it_end; ++it_begin) {
		if ((*it_begin)->getNickName() == Name) {
			delete *it_begin;
			this->_OperatorChannel.erase(it_begin);
			return ;
		}
	}
}

void	Channel::pushFlag(const char flag) {
	this->_Flags.push_back(flag);
}

void	Channel::popFlag(const char flag) {
	if (this->_Flags.empty() == true)
		return ;
	std::vector<char >::iterator	it_begin = this->_Flags.begin();
	std::vector<char >::iterator	it_end = this->_Flags.end();
	for (; it_begin != it_end; it_begin++) {
		if ((*it_begin) == flag) {
			this->_Flags.erase(it_begin);
			return ;
		}
	}
}

void	Channel::setPassword(const std::string NewPassword) {
	this->_Password = NewPassword;
}

void	Channel::setTopic(const std::string NewTopic) {
	this->_Topic = NewTopic;
}

int	Channel::getLinitUsers(void) const {
	return (this->_LimitUsers);
}

void	Channel::setLimitUsers(const int NewLimit) {
	this->_LimitUsers = NewLimit;
}

std::vector<std::string>	Channel::getBanMask(void) const {
	return (this->_BanMask);
}

void	Channel::pushBanMask(const std::string BanMask) {
	this->_BanMask.push_back(BanMask);
}

void	Channel::popBanMask(const std::string BanMask) {
	if (this->_BanMask.empty() == true)
		return ;
	std::vector<std::string>::iterator	it_begin = this->_BanMask.begin();
	std::vector<std::string>::iterator	it_end = this->_BanMask.end();
	for (; it_begin != it_end; it_begin++) {
		if ((*it_begin) == BanMask) {
			this->_BanMask.erase(it_begin);
			return ;
		}
	}
}

void	Channel::SendUsers(std::string Command, std::string Mess, User &user) {
	
	std::map<std::string, User *>::iterator UserBeg = this->_Users.begin();
	std::map<std::string, User *>::iterator UserEnd = this->_Users.end();
	
	for (; UserBeg != UserEnd; ++UserBeg) {
		if (Command != "NOTICE") {
			SendMessage(*((*UserBeg).second), Mess);
			if ((*UserBeg).second->getMessageAway().size() > 0)
				SendMessage(user, CmdMess(*((*UserBeg).second), RPL_AWAY, (*UserBeg).first, (*UserBeg).second->getMessageAway(), "", "", "", "", ""));	
		}
		else {
			if ((*UserBeg).second->CheckUserFlags('s') == false)
				SendMessage(*((*UserBeg).second), Mess);
		}
	}
}
