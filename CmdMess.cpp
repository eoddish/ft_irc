/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMess.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:39:11 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/17 19:15:05 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdMess.hpp"

std::string		CmdMess(User &user, int CodeMess,\
						std::string Parametr1, std::string Parametr2, \
						std::string Parametr3, std::string Parametr4, \
						std::string Parametr5, std::string Parametr6, \
						std::string Parametr7) {
	std::ostringstream s;
	s << CodeMess;
	std::string result( s.str() );
	result += " " + user.getNickName() + " ";
	switch (CodeMess)
	{
	case RPL_NONE:
		result += "Dummy reply number. Not used.";
		break;
	case RPL_USERHOST:
		result += ":[" + Parametr1 + "{" + Parametr2 + Parametr3 + "}]" ;
		break;
	case RPL_ISON:
		result += ":[" + Parametr1 + "{" + Parametr2 + Parametr3 + "}]" ;
		break;
	case RPL_AWAY:
		result += Parametr1 + " :" + Parametr2;
		break;
	case RPL_UNAWAY:
		result += ":You are no longer marked as being away";
		break;
	case RPL_NOWAWAY:
		result += ":You have been marked as being away";
		break;
	case RPL_WHOISUSER:
		result += Parametr1 + " " + Parametr2 + " " + Parametr3 + " * :" + Parametr4;
		break;
	case RPL_WHOISSERVER:
		result += Parametr1 + " " + Parametr2 + " :" + Parametr3;
		break;
	case RPL_WHOISOPERATOR:
		result += Parametr1 + " :is an IRC operator";
		break;
	case RPL_WHOISIDLE:
		result += Parametr1 + " " + Parametr2 + " :seconds idle";
		break;
	case RPL_ENDOFWHOIS:
		result += Parametr1 + " :End of /WHOIS list";
		break;
	case RPL_WHOISCHANNELS:
		result += Parametr1 + " :" + Parametr2;
		break;
	case RPL_WHOWASUSER:
		result += Parametr1 + " " + Parametr2 + " " + Parametr3 + " * :" + Parametr4;
		break;
	case RPL_ENDOFWHOWAS:
		result += Parametr1 + " :End of WHOWAS";
		break;
	case RPL_LISTSTART:
		result += "Channel :Users  Name";
		break;
	case RPL_LIST:
		result += Parametr1 + " " + Parametr2 + " :" + Parametr3;
		break;
	case RPL_LISTEND:
		result += ":End of /LIST";
		break;
	case RPL_CHANNELMODEIS:
		result += Parametr1 + " " + Parametr2 + "  " + Parametr3;
		break;
	case RPL_NOTOPIC:
		result += Parametr1 + " :No topic is set";
		break;
	case RPL_TOPIC:
		result += Parametr1 + " :" + Parametr2;
		break;
	case RPL_INVITING:
		result += Parametr1 + " " + Parametr2;
		break;
	case RPL_SUMMONING:
		result += Parametr1 + " :Summoning user to IRC";
		break;
	case RPL_VERSION:
		result += Parametr1 + "." + Parametr2 + " " + Parametr3 + " :" + Parametr4;
		break;
	case RPL_WHOREPLY:
		// result += Parametr1 + " "+ Parametr2 + " " + Parametr3 + " " + Parametr4 + " " + Parametr5 + " <H|G>[*][@|+] :" + Parametr6 + " " + Parametr7;
		result += Parametr1 + Parametr2;
		break;
	case RPL_ENDOFWHO:
		result += Parametr1 + " :End of /WHO list";
		break;
	case RPL_NAMREPLY:
		result += Parametr1 + " :" + Parametr2;
		break;
	case RPL_ENDOFNAMES:
		result += Parametr1 + " :End of /NAMES list";
		break;
	case RPL_LINKS:
		result += Parametr1 + " " + Parametr2 + " :" + Parametr3 + " " + Parametr4;
		break;
	case RPL_ENDOFLINKS:
		result += Parametr1 + " :End of /LINKS list";
		break;
	case RPL_BANLIST:
		result += Parametr1 + " " + Parametr2;
		break;
	case RPL_ENDOFBANLIST:
		result += Parametr1 + " :End of channel ban list";
		break;
	case RPL_INFO:
		result += ":" + Parametr1;
		break;
	case RPL_ENDOFINFO:
		result += ":End of /INFO list";
		break;
	case RPL_MOTDSTART:
		result += ":- " + Parametr1 + " Message of the day - ";
		break;
	case RPL_MOTD:
		result += ":- " + Parametr1;
		break;
	case RPL_ENDOFMOTD:
		result += ":End of /MOTD command";
		break;
	case RPL_YOUREOPER:
		result += ":You are now an IRC operator";
		break;
	case RPL_REHASHING:
		result += Parametr1 + " :Rehashing";
		break;
	case RPL_TIME:
		result += Parametr1 + " :" + Parametr2;
		break;
	case RPL_USERSSTART:
		result += ":UserID   Terminal  Host";
		break;
	case RPL_USERS:
		result += ":%-8s %-9s %-8s";
		break;
	case RPL_ENDOFUSERS:
		result += ":End of users";
		break;
	case RPL_NOUSERS:
		result += ":Nobody logged in";
		break;
	case RPL_TRACELINK:
		result += "Link " + Parametr1 + " & " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_TRACECONNECTING:
		result += "Try. " + Parametr1 + " " + Parametr2;
		break;
	case RPL_TRACEHANDSHAKE:
		result += "H.S. " + Parametr1 + " " + Parametr2;
		break;
	case RPL_TRACEUNKNOWN:
		result += "???? " + Parametr1 +" [" + Parametr2 + "]";
		break;
	case RPL_TRACEOPERATOR:
		result += "Oper " + Parametr1 + " " + Parametr2;
		break;
	case RPL_TRACEUSER:
		result += "User " + Parametr1 + " " + Parametr2;
		break;
	case RPL_TRACESERVER:
		result += "Serv " + Parametr1 + " <int>S <int>C " + Parametr2 + " <nick!user|*!*>@<host|server>";
		break;
	case RPL_TRACENEWTYPE:
		result += Parametr1 + " "  + "0 " + Parametr2;
		break;
	case RPL_TRACELOG:
		result += "File " + Parametr1 + " " + Parametr2;
		break;
	case RPL_STATSLINKINFO:
		result += Parametr1 + " " + Parametr2 + " " + Parametr3 + " " + Parametr4 + " " + Parametr5 + " " + Parametr6 + " " + Parametr7;
		break;
	case RPL_STATSCOMMANDS:
		result += Parametr1 + " " + Parametr2;
		break;
	case RPL_STATSCLINE:
		result += "C " + Parametr1 + " * " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_STATSNLINE:
		result += "N " + Parametr1 + " * " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_STATSILINE:
		result += "I " + Parametr1 + " * " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_STATSKLINE:
		result += "K " + Parametr1 + " * " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_STATSYLINE:
		result += "Y " + Parametr1 + " " + Parametr2 + " " + Parametr3 + " " + Parametr4;
		break;
	case RPL_ENDOFSTATS:
		result += Parametr1 + " :End of /STATS report";
		break;
	case RPL_UMODEIS:
		result += Parametr1;
		break;
	case RPL_STATSLLINE:
		result += "L " + Parametr1 + " * " + Parametr2 + " " + Parametr3;
		break;
	case RPL_STATSUPTIME:
		result += ":Server Up %d days %d:%02d:%02d";
		break;
	case RPL_STATSOLINE:
		result += "O " + Parametr1 + " * " + Parametr2;
		break;
	case RPL_STATSHLINE:
		result += "H " + Parametr1 + " * " + Parametr2;
		break;
	case RPL_LUSERCLIENT:
		result += ":There are "+ Parametr1 + " users and " + Parametr2 + " invisible on " + Parametr3 + " servers";
		break;
	case RPL_LUSEROP:
		result += Parametr1 + " :operator(s) online";
		break;
	case RPL_LUSERUNKNOWN:
		result += Parametr1 + " :unknown connection(s)";
		break;
	case RPL_LUSERCHANNELS:
		result += Parametr1 + " :channels formed";
		break;
	case RPL_LUSERME:
		result += ":I have " + Parametr1 + " clients and " + Parametr2 + " servers";
		break;
	case RPL_ADMINME:
		result += Parametr1 + " :Administrative info";
		break;
	case RPL_ADMINLOC1:
		result += ":" + Parametr1;
		break;
	case RPL_ADMINLOC2:
		result += ":" + Parametr1;
		break;
	case RPL_ADMINEMAIL:
		result += ":" + Parametr1;
		break;
	default:
		result += "Inknow message";
		break;
	}
	return (result);
}
