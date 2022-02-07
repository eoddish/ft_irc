/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:27:07 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/07 19:42:27 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class Server {

public:

	int getPort() const;
	std::string getPassword() const;	
	void setPort( int port ); 
	void setPassword( std::string passwrod );

private:

	int _port;
	std::string _password;
		
};
