/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   History.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/19 14:00:36 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "History.hpp"

History::History() {}

History::History(const HistoryUser &NewOld) {
	this->_UsersList.push_back(NewOld);
}

History::History(const History &copy) {
	*this = copy;
}

History&	History::operator= (const HistoryUser &NewHistory) {
	if (this != &NewHistory) {
		*this = NewHistory;
	}
	return (*this);
}

History::~History() {}

void	History::setUsersList(std::vector<HistoryUser *> &NewHistory) {
	this->_UsersList = NewHistory;
}

std::vector<HistoryUser *>	History::getUsersList(void) const {
	return (this->_UsersList);
}

std::queue<std::string>	History::PrintOldUsers(std::string Name) {
	
	std::queue<std::string> Result;
	for (int i = 0; i < this->_UsersList.size(); i++) {
		if (this->_UsersList[i]->getOldNickName() == Name) {
			std::string StrRes = this->_UsersList[i]->getOldNickName() + " ";
			StrRes += this->_UsersList[i]->getOldUserName() + " ";
			StrRes += this->_UsersList[i]->getOldHostName() + " * :";
			StrRes += this->_UsersList[i]->getOldRealName() + "\n";

			Result.push(StrRes);
		}
	}
	return (Result);
}
