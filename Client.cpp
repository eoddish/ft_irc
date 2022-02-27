/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:06:54 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/27 21:04:55 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

std::string Server::commandDcc( Message &msg,User &user) {

    if ( msg.getParamets()[1] == "send" )
        return commandDccSend(msg, user);
    else if ( msg.getParamets()[1] == "get" )
        return commandDccGet(msg, user);
    return("");
}

std::string Client::commandDccSend(Message &msg,User &user) {

	
	int sock = socket( AF_INET, SOCK_STREAM, 0 );
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( port );

	bind( sock, (struct sockaddr * ) &address, sizeof( address ) );
	listen( sock, 3 );
	

    (void)user;
    std::string nick = msg.getParamets()[2];
    std::ifstream ifs(msg.getParamets()[3], std::ifstream::binary);

    if ( !ifs.is_open() )
        return ( msg.getParamets()[3] + ": No such file or directory");

    std::string strname = msg.getParamets()[3];
    int len =  strname.size() - strname.rfind("/") - 1;
    strname = strname.substr( strname.rfind( "/") + 1, len);
    _streamNames[nick] = strname;
    _streamUsers[nick] = user.getNickName();

    char c;
    while ( ifs.get(c) ) {
        _streams[nick].push_back(c);
    }
    SendMessage( *_UsersCheck[nick], "DCC SEND from " + user.getNickName() );
    return ("DCC SEND request sent to " + nick + ": " + strname);
}

std::string Client::commandDccGet(Message &msg,User &user) {

    (void)msg;
    std::ofstream ofs;
    if ( _streamNames.find( user.getNickName() ) == _streamNames.end() )
        return ("");
    ofs.open(_streamNames[user.getNickName()], std::ofstream::binary);
    if (!ofs.is_open() ) {
        std::cout << "Failed to open" << std::endl;
        return ("");
    }

    std::string str = _streamNames[user.getNickName()];
    std::string sender = _streamUsers[user.getNickName()];

    ofs << _streams[user.getNickName()];
    _streams.erase(user.getNickName());
    _streamNames.erase(user.getNickName());
    _streamUsers.erase(user.getNickName());

    SendMessage( *_UsersCheck[sender], "DCC sent file " + str + " for " + user.getNickName() );
    return ("DCC received file " + str + " from " + _UsersCheck[sender]->getNickName());
}
