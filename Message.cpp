/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:57:06 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/17 15:57:30 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message() {}

Message::~Message() {}

Message::Message(const Message &copy) {
	*this = copy;
}

Message&	Message::operator= (const Message &copy) {
	if (this != &copy) {
		*this = copy;
	}
	return (*this);
}

std::string	Message::getSender(void) {
	return (this->_Sender);
}

std::string	Message::getReceiver(void) {
	return (this->_Receiver);
}

std::string	Message::getPayload(void) {
	return (this->_Payload);
}

std::string	Message::getCommand(void) {
	return (this->_Command);
}

std::string	Message::getMessage(void) {
	return (this->_Message);
}

std::vector<std::string> &Message::getParamets(void) {
	return (this->_Paramets);
}

void		Message::setSender(std::string Sender) {
	this->_Sender = Sender;
}

void		Message::setReceiver(std::string Receiver) {
	this->_Receiver = Receiver;
}

void		Message::setPayload(std::string Payload) {
	this->_Payload = Payload;
}

void		Message::setCommand(std::string Command) {
	this->_Command = Command;
}

void		Message::setMessage(std::string Msg) {
	this->_Message = Msg;
}

void		Message::setParamets(std::vector<std::string> &param) {
	this->_Paramets = param;
}
