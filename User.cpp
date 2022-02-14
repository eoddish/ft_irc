/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:07:00 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/14 15:52:12 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "User.hpp"

User::User() {
	std::cout << "Constructor User was started" << std::endl;
	this->_StatusRegistr = false;
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

bool		User::getStatusRegistr(void) const {
	return(this ->_StatusRegistr);
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

void		User::setMessageAway(std::string MsdAway) {
	this->_MessageAway = MsdAway;
}

void		User::setStatusRegistr(bool StatusRegistr) {
	this->_StatusRegistr = StatusRegistr;
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
