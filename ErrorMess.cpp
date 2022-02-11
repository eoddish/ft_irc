/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMess.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:42:09 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/11 18:08:26 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorMess.hpp"

std::string	PrintError(int CodeError) {

	std::string result;
	switch (CodeError)
	{
	case ERR_NOSUCHNICK:
		result = "<nickname> :No such nick/channel";
		break;
	case ERR_NOSUCHSERVER:
		result = "<server name> :No such server";
		break;
	case ERR_NOSUCHCHANNEL:
		result = "<channel name> :No such channel";
		break;
	case ERR_CANNOTSENDTOCHAN:
		result = "<channel name> :Cannot send to channel";
		break;
	case ERR_TOOMANYCHANNELS:
		result = "<channel name> :You have joined too many channels";
		break;
	case ERR_WASNOSUCHNICK:
		result = "<nickname> :There was no such nickname";
		break;
	case ERR_TOOMANYTARGETS:
		result = "<target> :Duplicate recipients. No message delivered";
		break;
	case ERR_NOORIGIN:
		result = ":No origin specified";
		break;
	case ERR_NORECIPIENT:
		result = ":No recipient given (<command>)";
		break;
	case ERR_NOTEXTTOSEND:
		result = ":No text to send";
		break;
	case ERR_NOTOPLEVEL:
		result = "<mask> :No toplevel domain specified";
		break;
	case ERR_WILDTOPLEVEL:
		result = "<mask> :Wildcard in toplevel domain";
		break;
	case ERR_UNKNOWNCOMMAND:
		result = " :Unknown command";
		break;
	case ERR_NOMOTD:
		result = ":MOTD File is missing";
		break;
	case ERR_NOADMININFO:
		result = "<server> :No administrative info available";
		break;
	case ERR_FILEERROR:
		result = ":File error doing <file op> on <file>";
		break;
	case ERR_NONICKNAMEGIVEN:
		result = ":No nickname given";
		break;
	case ERR_ERRONEUSNICKNAME:
		result = "<nick> :Erroneus nickname";
		break;
	case ERR_NICKNAMEINUSE:
		result = "<nick> :Nickname is already in use";
		break;
	case ERR_NICKCOLLISION:
		result = "<nick> :Nickname collision KILL";
		break;
	case ERR_USERNOTINCHANNEL:
		result = "<nick> <channel> :They aren't on that channel";
		break;
	case ERR_NOTONCHANNEL:
		result = "<channel> :You're not on that channel";
		break;
	case ERR_USERONCHANNEL:
		result = "<user> <channel> :is already on channel";
		break;
	case ERR_NOLOGIN:
		result = "<user> :User not logged in";
		break;
	case ERR_SUMMONDISABLED:
		result = ":SUMMON has been disabled";
		break;
	case ERR_USERSDISABLED:
		result = ":USERS has been disabled";
		break;
	case ERR_NOTREGISTERED:
		result = ":You have not registered";
		break;
	case ERR_NEEDMOREPARAMS:
		result = "<command> :Not enough parameters";
		break;
	case ERR_ALREADYREGISTRED:
		result = ":You may not reregister";
		break;
	case ERR_NOPERMFORHOST:
		result = ":Your host isn't among the privileged";
		break;
	case ERR_PASSWDMISMATCH:
		result = ":Password incorrect";
		break;
	case ERR_YOUREBANNEDCREEP:
		result = ":You are banned from this server";
		break;
	case ERR_KEYSET:
		result = "<channel> :Channel key already set";
		break;
	case ERR_CHANNELISFULL:
		result = "<channel> :Cannot join channel (+l)";
		break;
	case ERR_UNKNOWNMODE:
		result = "<char> :is unknown mode char to me";
		break;
	case ERR_INVITEONLYCHAN:
		result = "<channel> :Cannot join channel (+i)";
		break;
	case ERR_BANNEDFROMCHAN:
		result = "<channel> :Cannot join channel (+b)";
		break;
	case ERR_BADCHANNELKEY:
		result = "<channel> :Cannot join channel (+k)";
		break;
	case ERR_NOPRIVILEGES:
		result = ":Permission Denied- You're not an IRC operator";
		break;
	case ERR_CHANOPRIVSNEEDED:
		result = "<channel> :You're not channel operator";
		break;
	case ERR_CANTKILLSERVER:
		result = ":You cant kill a server!";
		break;
	case ERR_NOOPERHOST:
		result = ":No O-lines for your host";
		break;
	case ERR_UMODEUNKNOWNFLAG:
		result = ":Unknown MODE flag";
		break;
	case ERR_USERSDONTMATCH:
		result = ":Cant change mode for other users";
		break;
	default:
		result = ":Unknown errors";
		break;
	}
	return result;
}
