/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:07:00 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/21 16:19:13 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "User.hpp"

User::User() : _NickName( "*" ), _StatusRegistr( false )  {

	std::cout << "Constructor User was started" << std::endl;
	this->_StatusRegistr = false;
	this->_StatusPass = false;
	this->_StatusOnline = false;
}

User::~User() {
	std::cout << "Destructor User was started" << std::endl;
}

User::User(const User &copy) {
	std::cout << "Copy constructor User was started" << std::endl;
	*this = copy;
}

User&	User::operator= (const User &copy) {
	std::cout << "Owerload operator '=' User was started" << std::endl;
	if (this != &copy)
		*this = copy;
	return (*this);
}

User&		User::operator++() {
	++this->_HowManyChannel;
	return *this;
}

User&		User::operator--() {
	--this->_HowManyChannel;
	return *this;
}

int	User::getFd(void) const {
	return (this->_fd);
}

time_t		User::getRegistrTime(void) const {
	return (this->_RegistrTime);
}

std::string	User::getUserName(void) const {
	return (this->_UserName);
}

std::string	User::getRealName(void) const {
	return (this->_RealName);
}

std::string User::getNickName(void) const {
	return (this->_NickName);
}

std::string	User::getMessageAway(void) const {
	return (this->_MessageAway);
}

std::string	User::getHostName(void) const {
	return (this->_HostName);
}

bool		User::getStatusRegistr(void) const {
	return(this ->_StatusRegistr);
}

bool		User::getStatusPass(void) const {
	return(this->_StatusPass);
}

bool		User::getStatusOnline(void) const {
	return(this->_StatusOnline);
}

void		User::setFd( int fd ) {
	this->_fd = fd;
}

void		User::setRegistrTime(time_t NewTime) {
	this->_RegistrTime = NewTime;
}

void		User::setUserName(std::string Username) {
	this->_UserName = Username;
}

void		User::setRealName(std::string Realname) {
	this->_RealName = Realname;
}

void		User::setNickName(std::string Nickname) {
	this->_NickName = Nickname;
}

void		User::setHostName(std::string HostName) {
	this->_HostName = HostName;
}

void		User::setMessageAway(std::string MsdAway) {
	this->_MessageAway = MsdAway;
}

void		User::setStatusRegistr(bool StatusRegistr) {
	this->_StatusRegistr = StatusRegistr;
}

void		User::setStatusPass(bool StatusPass) {
	this->_StatusPass = StatusPass;
}

void		User::setStatusOnline(bool StatusOnline) {
	this->_StatusOnline = StatusOnline;
}

void		User::setFlagsStatus(const char flag) {
	this->_FlagsStatus.push_back(flag);
}

void		User::popFlag(const char flag) {
	if (this->_FlagsStatus.empty() == true)
		return ;
	std::vector<char >::iterator	it_begin = this->_FlagsStatus.begin();
	std::vector<char >::iterator	it_end = this->_FlagsStatus.end();
	for (; it_begin != it_end; it_begin++) {
		if ((*it_begin) == flag) {
			this->_FlagsStatus.erase(it_begin);
			return ;
		}
	}
}

bool	User::CheckUserFlags(const char Flag) {
	for (int i = 0; this->_FlagsStatus[i] != *this->_FlagsStatus.end(); i++) {
		if (this->_FlagsStatus[i] == Flag)
			return (true);
	}
	return (false);
}
/*
std::string	User::PrintInfo(void) const {
	std::string Result;
	
	std::map<std::string, Channel *>::const_iterator Beg = this->_UseChannel.begin();
	std::map<std::string, Channel *>::const_iterator End = this->_UseChannel.end();
	for (; Beg != End; ) {
		Result += (*Beg).first + this->getNickName() + "[ ";
		if ((*Beg).second->CheckOperator(this->getNickName()) == true)
			Result += "@";
		if ((*Beg).second->CheckSpeakers(this->getNickName()) == true)
			Result += "+";
		Result += (*Beg).first + "]";
		if ((++Beg) != End)
			Result += " ";
	}
   	Result	+= ":" + this->_RealName + ",";
	return (Result);
}

void		User::pushChannel( Channel &NewChannel) {
	(this->_UseChannel)[NewChannel.getNameChannel()] = &NewChannel;
}

void		User::popChannel(const std::string ChannelName) {
	if (this->_UseChannel.empty() == true)
		return ;
	this->_UseChannel.erase(ChannelName);
}
*/
