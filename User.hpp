/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:01:19 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/15 20:06:47 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>

class User
{
private:
	int							_LimitChannel;
	int							_HowManyChannel;
	std::string					_UserName;
	std::string					_RealName;
	std::string					_NickName;

	std::string					_MessageAway;
	
	std::vector<char >			_FlagsStatus;
	bool						_StatusRegistr;


	int _fd;

public:
	User();
	virtual ~User();
	User(const User &copy);
	User&	operator= (const User &copy);

	int getFd( void ) const;
	std::string	getUserName(void) const;
	std::string	getRealName(void) const;
	std::string getNickName(void) const;
	std::string getMessageAway(void) const;
	bool		getStatusRegistr(void) const;
	std::vector<char> getFlagsStatus(void) const;
	int			getLimitChannel(void) const;
	int			getHowManyChannel(void) const;
	
	void		setFd( int fd );
	void		setUserName(std::string Username);
	void		setRealName(std::string Realname);
	void		setNickName(std::string Nickname);
	void		setMessageAway(std::string MsdAway);
	void		setStatusRegistr(bool StatusRegistr);
	void		setLimitChannel(int NewLimit);
	User&		operator++();
	User&		operator--();
	
	void		setFlagsStatus(const char flag);

	void		popFlag(const char flag);
};

