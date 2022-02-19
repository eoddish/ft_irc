/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utills.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:19:50 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/19 21:06:37 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::queue<std::string>	split(std::string Str, char Delimiter) {
	int		NumberStr = 0;
	std::queue<std::string>	Result;
	
	for (size_t i = 0; i < Str.size(); i++) {
		if (Str[i] == Delimiter) {
			Result.push(Str.substr(NumberStr, i));
			NumberStr = i + 1;
		}
	}
	if ( Result.size() == 0 )
			Result.push(Str);
	return (Result);
}

int	CheckMask(std::string Mask) {
	size_t symbol = Mask.find_first_of('*');
	if (symbol == 0) {
		return (1);
	}
	else if (symbol == Mask.size() - 1) {
		return (2);
	}
	else {
		return (3);
	}
	return (0);
}

std::queue<std::string>	Server::ListMaskUser(std::string Mask, bool Param) {
	std::queue<std::string> Result;
	std::string	tmpMask;
	int flag = CheckMask(Mask);

	switch (flag)
	{
	case 1:
		Mask.erase(Mask.find_first_of('*'), 1);
		break;
	case 2:
		Mask.erase(Mask.find_first_of('*'));
		break;
	case 3:
		tmpMask = Mask.erase(0, Mask.find_first_of('*'));
		Mask.erase(Mask.find_first_of('*'), Mask.size());
		break;
	default:
		break;
	}
	
	std::map<std::string, User *>::iterator beg;
	std::map<std::string, User *>::iterator end;
	if (Param == false) {
		beg = this->_UsersCheck.begin();
		end = this->_UsersCheck.end();

	}
	else {
		beg = this->_IRC_operator.begin();
		end = this->_IRC_operator.end();
	}
	
	for (; beg != end; ++beg) {
		switch (flag)
		{
		case 1:
			if ((*beg).first.rfind(Mask) != std::string::npos) {
				if ((*beg).second->CheckUserFlags('i') == false) {
					Result.push((*beg).first);
				}
			}
			break;
		case 2:
			if ((*beg).first.find(Mask) != std::string::npos) {
				if ((*beg).second->CheckUserFlags('i') == false) {
					Result.push((*beg).first);
				}
			}
			break;
		case 3:
			if ((*beg).first.rfind(tmpMask) != std::string::npos
				&& (*beg).first.find(Mask) != std::string::npos) {
				if ((*beg).second->CheckUserFlags('i') == false) {
					Result.push((*beg).first);
				}
			}
			break;
		default:
			break;
		}
	}

	return (Result);
}
