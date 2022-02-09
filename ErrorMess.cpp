/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMess.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:42:09 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/09 15:45:39 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorMess.hpp"

void	PrintError(int CodeError) {
	switch (CodeError)
	{
	case ERR_NOSUCHNICK:
		std::cerr << "<nickname> :No such nick/channel" << std::endl;
		break;
	case ERR_NOSUCHSERVER:
		std::cerr << "<server name> :No such server" << std::endl;
		break;
	case ERR_NOSUCHCHANNEL:
		std::cerr << "<channel name> :No such channel" << std::endl;
		break;
	case ERR_CANNOTSENDTOCHAN:
		std::cerr << "<channel name> :Cannot send to channel" << std::endl;
		break;
	case ERR_TOOMANYCHANNELS:
		std::cerr << "<channel name> :You have joined too many channels" << std::endl;
		break;
	case ERR_WASNOSUCHNICK:
		std::cerr << "<nickname> :There was no such nickname" << std::endl;
		break;
	case ERR_TOOMANYTARGETS:
		std::cerr << "<target> :Duplicate recipients. No message delivered" << std::endl;
		break;
	case ERR_NOORIGIN:
		std::cerr << ":No origin specified" << std::endl;
		break;
	case ERR_NORECIPIENT:
		std::cerr << ":No recipient given (<command>)" << std::endl;
		break;
	case ERR_NOTEXTTOSEND:
		std::cerr << ":No text to send" << std::endl;
		break;
	case ERR_NOTOPLEVEL:
		std::cerr << "<mask> :No toplevel domain specified" << std::endl;
		break;
	case ERR_WILDTOPLEVEL:
		std::cerr << "<mask> :Wildcard in toplevel domain" << std::endl;
		break;
	case ERR_UNKNOWNCOMMAND:
		std::cerr << " :Unknown command" << std::endl;
		break;
	case ERR_NOMOTD:
		std::cerr << ":MOTD File is missing" << std::endl;
		break;
	case ERR_NOADMININFO:
		std::cerr << "<server> :No administrative info available" << std::endl;
		break;
	case ERR_FILEERROR:
		std::cerr << ":File error doing <file op> on <file>" << std::endl;
		break;
	case ERR_NONICKNAMEGIVEN:
		std::cerr << ":No nickname given" << std::endl;
		break;
	case ERR_ERRONEUSNICKNAME:
		std::cerr << "<nick> :Erroneus nickname" << std::endl;
		break;
	case ERR_NICKNAMEINUSE:
		std::cerr << "<nick> :Nickname is already in use" << std::endl;
		break;
	case ERR_NICKCOLLISION:
		std::cerr << "<nick> :Nickname collision KILL" << std::endl;
		break;
	case ERR_USERNOTINCHANNEL:
		std::cerr << "<nick> <channel> :They aren't on that channel" << std::endl;
		break;
	case ERR_NOTONCHANNEL:
		std::cerr << "<channel> :You're not on that channel" << std::endl;
		break;
	case ERR_USERONCHANNEL:
		std::cerr << "<user> <channel> :is already on channel" << std::endl;
		break;
	case ERR_NOLOGIN:
		std::cerr << "<user> :User not logged in" << std::endl;
		break;
	case ERR_SUMMONDISABLED:
		std::cerr << ":SUMMON has been disabled" << std::endl;
		break;
	case ERR_USERSDISABLED:
		std::cerr << ":USERS has been disabled" << std::endl;
		break;
	case ERR_NOTREGISTERED:
		std::cerr << ":You have not registered" << std::endl;
		break;
	case ERR_NEEDMOREPARAMS:
		std::cerr << "<command> :Not enough parameters" << std::endl;
		break;
	case ERR_ALREADYREGISTRED:
		std::cerr << ":You may not reregister" << std::endl;
		break;
	case ERR_NOPERMFORHOST:
		std::cerr << ":Your host isn't among the privileged" << std::endl;
		break;
	case ERR_PASSWDMISMATCH:
		std::cerr << ":Password incorrect" << std::endl;
		break;
	case ERR_YOUREBANNEDCREEP:
		std::cerr << ":You are banned from this server" << std::endl;
		break;
	case ERR_KEYSET:
		std::cerr << "<channel> :Channel key already set" << std::endl;
		break;
	case ERR_CHANNELISFULL:
		std::cerr << "<channel> :Cannot join channel (+l)" << std::endl;
		break;
	case ERR_UNKNOWNMODE:
		std::cerr << "<char> :is unknown mode char to me" << std::endl;
		break;
	case ERR_INVITEONLYCHAN:
		std::cerr << "<channel> :Cannot join channel (+i)" << std::endl;
		break;
	case ERR_BANNEDFROMCHAN:
		std::cerr << "<channel> :Cannot join channel (+b)" << std::endl;
		break;
	case ERR_BADCHANNELKEY:
		std::cerr << "<channel> :Cannot join channel (+k)" << std::endl;
		break;
	case ERR_NOPRIVILEGES:
		std::cerr << ":Permission Denied- You're not an IRC operator" << std::endl;
		break;
	case ERR_CHANOPRIVSNEEDED:
		std::cerr << "<channel> :You're not channel operator" << std::endl;
		break;
	case ERR_CANTKILLSERVER:
		std::cerr << ":You cant kill a server!" << std::endl;
		break;
	case ERR_NOOPERHOST:
		std::cerr << ":No O-lines for your host" << std::endl;
		break;
	case ERR_UMODEUNKNOWNFLAG:
		std::cerr << ":Unknown MODE flag" << std::endl;
		break;
	case ERR_USERSDONTMATCH:
		std::cerr << ":Cant change mode for other users" << std::endl;
		break;
	default:
		std::cerr << ":Unknown errors" << std::endl;
		break;
	}
}
