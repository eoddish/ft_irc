/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   History.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/18 18:19:54 by nagrivan         ###   ########.fr       */
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
