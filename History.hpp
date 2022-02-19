/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   History.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:44:41 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/19 14:55:33 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "User.hpp"
#include <queue>

class User;

class HistoryUser
{
private:
	std::string		_OldNickName;
	std::string		_OldUserName;
	std::string		_OldRealName;
	std::string		_OldHostName;
	time_t			_TimeRegister;
	HistoryUser();
	HistoryUser(const HistoryUser &NewHistory);
	HistoryUser&	operator= (const HistoryUser &NewHistory);
public:
	HistoryUser(const User &NewOld);
	virtual ~HistoryUser();

	void	setOldNickName(const std::string OldName) const;
	std::string	getOldNickName(void);

	void	setOldUserName(const std::string OldName) const;
	std::string	getOldUserName(void);

	void	setOldRealName(const std::string OldName) const;
	std::string	getOldRealName(void);

	void	setOldHostName(const std::string OldName) const;
	std::string	getOldHostName(void);

	void	setTimeRegister(const time_t OldTime) const;
	time_t	getTimeRegister(void);
};

class History
{
private:
	std::vector<HistoryUser *>	_UsersList;
public:

	History();
	History(const History &copy);
	History&	operator= (const History &copy);
	History(const HistoryUser &NewOld);
	virtual ~History();

	void	setUsersList(std::vector<HistoryUser *> &NewHistory);
	std::vector<HistoryUser *>	getUsersList(void) const;
	
	std::queue<std::string> PrintOldUsers(std::string Name);
};
