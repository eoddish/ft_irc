/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utills.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:19:50 by nagrivan          #+#    #+#             */
/*   Updated: 2022/02/15 18:53:42 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::queue<std::string>	ft_split(std::string Str, char Delimiter) {
	int		NumberStr = 0;
	std::queue<std::string>	Result;
	
	for (int i = 0; i < Str.size(); i++) {
		if (Str[i] == Delimiter) {
			Result.push(Str.substr(NumberStr, i));
			NumberStr = i + 1;
		}
	}
	return (Result);
}

std::queue<std::string>	ListMaskUser(std::string Mask, bool Param) {}
