/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:06:27 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/27 20:27:17 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Client {

	std::string commandDcc(Message &msg,User &user );
    std::string commandDccSend(Message &msg,User &user);
    std::string commandDccGet(Message &msg,User &user);

}
