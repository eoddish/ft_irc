/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:43:03 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/17 20:13:03 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>
#include <vector>

#include "Server.hpp"

class Channel
{
private:
	std::string						_NameChannel;
	std::string						_Password;
	std::string						_Topic;
	int								_LimitUsers;
	
	std::map<std::string, User *>	_Users;
	std::vector<User *>				_OperatorChannel;
	std::vector<User *>				_SpeakersUser;
	
	std::vector<char>				_Flags;
	std::vector<std::string>		_BanMask;

public:
	Channel();
	Channel(std::string ChannelName);
	virtual ~Channel();
	Channel(const Channel &copy);
	Channel&	operator= (const Channel &copy);

	std::string	getNameChannel(void) const;
	std::string	getPassword(void) const;
	std::string getTopic(void) const;
	std::map<std::string, User *>	getUsers(void);
	std::vector<User *>	getOperatorChannel(void);
	std::vector<User *>	getSpeakersUsers(void);
	int	getLinitUsers(void) const;
	std::vector<std::string>	getBanMask(void) const;
	std::vector<char>	getFlags(void) const;

	std::string 	PrintUsers(void);

	bool	CheckUsers(std::string Name);
	bool	CheckOperator(std::string Name);
	bool	CheckSpeakers(std::string Name);
	bool	CheckFlags(const char Flag);
	bool	CheckBanMask(std::string Name);

	void	pushOperator(const User &NewOper);
	void	popOperator(std::string Name);
	void	pushUser(std::string Key, User &NewUser);
	void	popUser(std::string Name);
	void	pushSpeaker(const User &NewSpeak);
	void	popSpeaker(std::string Name);

	void	SendUsers(std::string Command, std::string Mess, User &user);

	void	pushFlag(const char flag);
	void	popFlag(const char flag);

	void	setPassword(const std::string NewPassword);
	void	setLimitUsers(const int NewLimit);
	void	setTopic(const std::string NewTopic);
	void	pushBanMask(const std::string BanMask);
	void	popBanMask(const std::string BanMask);
};
