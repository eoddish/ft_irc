/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:50:55 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/14 17:24:51 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

class Message
{
private:
	std::string					_Sender;
	std::string					_Receiver;
	std::string					_Payload;
	std::string					_Command;
	std::string					_Message;
public:
	std::vector<std::string>	_Paramets;
	Message();
	virtual ~Message();
	Message(const Message &copy);
	Message&	operator= (const Message &copy);
	
	std::string	getSender(void);
	std::string	getReceiver(void);
	std::string	getPayload(void);
	std::string	getCommand(void);
	std::string	getMessage(void);
	std::vector<std::string> & getParamets(void);
	
	void		setSender(std::string Sender);
	void		setReceiver(std::string Receiver);
	void		setPayload(std::string Payload);
	void		setCommand(std::string Command);
	void		setMessage(std::string Message);
	void		setParamets(std::vector<std::string> & param);
};
