/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:27:07 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/08 20:41:02 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>


class Server {

public:

	int getPort() const;
	std::string getPassword() const;	
	void setPort( int port ); 
	void setPassword( std::string passwrod );
	void parse();
	void static ft_time() ;

 	std::map<std::string,  void (*)( void )  > _functions;	

private:

	int _port;
	std::string _password;

	std::vector<std::string> & ft_split( std::string & str, std::vector<std::string> & vct );
	std::string & ft_tolower( std::string & str );
		
};
