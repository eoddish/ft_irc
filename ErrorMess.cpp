/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMess.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:42:09 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/18 17:52:47 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorMess.hpp"


std::string	PrintError(std::string Parametr1, std::string Parametr2, int CodeError, User &user) {

	std::ostringstream s;
	s << CodeError;
	std::string result( s.str() );
	result += " " + user.getNickName() + " ";

	switch (CodeError)
	{
	case ERR_NOSUCHNICK:
		result += Parametr1 + " :No such nick/channel";
		break;
	case ERR_NOSUCHSERVER:
		result += Parametr1 + " :No such server";
		break;
	case ERR_NOSUCHCHANNEL:
		result += Parametr1 + " :No such channel";
		break;
	case ERR_CANNOTSENDTOCHAN:
		result += Parametr1 + " :Cannot send to channel";
		break;
	case ERR_TOOMANYCHANNELS:
		result += Parametr1 + " :You have joined too many channels";
		break;
	case ERR_WASNOSUCHNICK:
		result +=  Parametr1 + " :There was no such nickname";
		break;
	case ERR_TOOMANYTARGETS:
		result += Parametr1 + " :Duplicate recipients. No message delivered";
		break;
	case ERR_NOORIGIN:
		result += ":No origin specified";
		break;
	case ERR_NORECIPIENT:
		result += ":No recipient given (" + Parametr1 + ")";
		break;
	case ERR_NOTEXTTOSEND:
		result += ":No text to send";
		break;
	case ERR_NOTOPLEVEL:
		result += Parametr1 + " :No toplevel domain specified";
		break;
	case ERR_WILDTOPLEVEL:
		result += Parametr1 + " :Wildcard in toplevel domain";
		break;
	case ERR_UNKNOWNCOMMAND:
		result += Parametr1 + " :Unknown command";
		break;
	case ERR_NOMOTD:
		result += ":MOTD File is missing";
		break;
	case ERR_NOADMININFO:
		result += Parametr1 + " :No administrative info available";
		break;
	case ERR_FILEERROR:
		result += ":File error doing " + Parametr1 + " on " + Parametr2;
		break;
	case ERR_NONICKNAMEGIVEN:
		result += ":No nickname given";
		break;
	case ERR_ERRONEUSNICKNAME:
		result += Parametr1 + " :Erroneous nickname";
		break;
	case ERR_NICKNAMEINUSE:
		result += Parametr1 + " :Nickname is already in use";
		break;
	case ERR_NICKCOLLISION:
		result += Parametr1 + " :Nickname collision KILL";
		break;
	case ERR_USERNOTINCHANNEL:
		result += Parametr1 + " " + Parametr2 + " :They aren't on that channel";
		break;
	case ERR_NOTONCHANNEL:
		result += Parametr1 + " :You're not on that channel";
		break;
	case ERR_USERONCHANNEL:
		result += Parametr1 + " " + Parametr2 + " :is already on channel";
		break;
	case ERR_NOLOGIN:
		result += Parametr1 + " :User not logged in";
		break;
	case ERR_SUMMONDISABLED:
		result += ":SUMMON has been disabled";
		break;
	case ERR_USERSDISABLED:
		result += ":USERS has been disabled";
		break;
	case ERR_NOTREGISTERED:
		result += ":You have not registered";
		break;
	case ERR_NEEDMOREPARAMS:
		result += Parametr1 + " :Not enough parameters";
		break;
	case ERR_ALREADYREGISTRED:
		result += ":You may not reregister";
		break;
	case ERR_NOPERMFORHOST:
		result += ":Your host isn't among the privileged";
		break;
	case ERR_PASSWDMISMATCH:
		result += ":Password incorrect";
		break;
	case ERR_YOUREBANNEDCREEP:
		result += ":You are banned from this server";
		break;
	case ERR_KEYSET:
		result += Parametr1 + " :Channel key already set";
		break;
	case ERR_CHANNELISFULL:
		result += Parametr1  + " :Cannot join channel (+l)";
		break;
	case ERR_UNKNOWNMODE:
		result += Parametr1 + " :is unknown mode char to me";
		break;
	case ERR_INVITEONLYCHAN:
		result += Parametr1 + " :Cannot join channel (+i)";
		break;
	case ERR_BANNEDFROMCHAN:
		result += Parametr1 + " :Cannot join channel (+b)";
		break;
	case ERR_BADCHANNELKEY:
		result += Parametr1 + " :Cannot join channel (+k)";
		break;
	case ERR_NOPRIVILEGES:
		result += ":Permission Denied- You're not an IRC operator";
		break;
	case ERR_CHANOPRIVSNEEDED:
		result += Parametr1 + " :You're not channel operator";
		break;
	case ERR_CANTKILLSERVER:
		result += ":You cant kill a server!";
		break;
	case ERR_NOOPERHOST:
		result += ":No O-lines for your host";
		break;
	case ERR_UMODEUNKNOWNFLAG:
		result += ":Unknown MODE flag";
		break;
	case ERR_USERSDONTMATCH:
		result += ":Cant change mode for other users";
		break;
	default:
		result += ":Unknown errors";
		break;
	}
	return result;
}
