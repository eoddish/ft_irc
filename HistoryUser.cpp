/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HistoryUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:15:05 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/19 14:39:54 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "History.hpp"

HistoryUser::HistoryUser() {}

HistoryUser::HistoryUser(const User &NewOld) {
	this->_OldNickName = NewOld.getNickName();
	this->_OldRealName = NewOld.getRealName();
	this->_OldUserName = NewOld.getUserName();
	this->_TimeRegister;
	this->_OldHostName = NewOld.getHostName();
}

HistoryUser::HistoryUser(const HistoryUser &NewHistory) {
	*this = NewHistory;
}

HistoryUser&	HistoryUser::operator= (const HistoryUser &NewHistory) {
	if (this != &NewHistory) {
		*this = NewHistory;
	}
	return (*this);
}

HistoryUser::~HistoryUser() {}

void	HistoryUser::setOldNickName(const std::string OldName) {
	this->_OldNickName = OldName;
}

std::string	HistoryUser::getOldNickName(void) const {
	return (this->getOldNickName);
}

void	HistoryUser::setOldUserName(const std::string OldName) {
	this->getOldUserName = OldName;
}

std::string	HistoryUser::getOldUserName(void) const {
	return (this->_OldUserName);
}

void	HistoryUser::setOldRealName(const std::string OldName) {
	this->_OldRealName = OldName;
}

std::string	HistoryUser::getOldRealName(void) const {
	return (this->_OldRealName);
}

void	HistoryUser::setTimeRegister(const time_t OldTime) {
	this->_TimeRegister = OldTime;
}

time_t	HistoryUser::getTimeRegister(void) const {
	return (this->_TimeRegister);
}

void	HistoryUser::setOldHostName(const std::string OldName) {
	this->_OldHostName = OldName;
}


std::string	HistoryUser::getOldHostName(void) const {
	return (this->_OldHostName);
}

