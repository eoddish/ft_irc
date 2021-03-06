/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:01:19 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/19 18:50:50 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Server.hpp"
# include <iostream>
# include <vector>
# include <map>
# include <ctime>

class Channel;

class User
{
private:
	int							_LimitChannel;
	int							_HowManyChannel;
	time_t						_RegistrTime;
	std::string					_UserName;
	std::string					_RealName;
	std::string					_NickName;
	std::string					_HostName;

	std::string					_MessageAway;
	
	std::vector<char >			_FlagsStatus;
	bool						_StatusRegistr;
	bool						_StatusOnline;
	bool						_StatusPass;

	std::map<std::string, Channel *>	_UseChannel;

	int _fd;
	
public:
	User();
	virtual ~User();
	User(const User &copy);
	User&	operator= (const User &copy);

	int getFd( void ) const;
	time_t		getRegistrTime(void) const;
	std::string	getUserName(void) const;
	std::string	getRealName(void) const;
	std::string getNickName(void) const;
	std::string getMessageAway(void) const;
	std::string	getHostName(void) const;
	bool		getStatusRegistr(void) const;
	bool		getStatusPass(void) const;
	bool		getStatusOnline(void) const;
	std::vector<char> getFlagsStatus(void) const;
	int			getLimitChannel(void) const;
	int			getHowManyChannel(void) const;

	std::string	PrintInfo(void) const;
	
	void		setFd( int fd );
	void		setRegistrTime(time_t NewTime);
	void		setUserName(std::string Username);
	void		setRealName(std::string Realname);
	void		setNickName(std::string Nickname);
	void		setHostName(std::string HostName);
	void		setMessageAway(std::string MsdAway);
	void		setStatusRegistr(bool StatusRegistr);
	void		setStatusPass(bool StatusPass);
	void		setStatusOnline(bool StatusOnline);
	void		setLimitChannel(int NewLimit);
	User&		operator++();
	User&		operator--();

	bool		CheckUserFlags(const char Flag);
	
	void		setFlagsStatus(const char flag);

	void		popFlag(const char flag);

	void		pushChannel(Channel &NewChannel);
	void		popChannel(const std::string ChannelName);
};
