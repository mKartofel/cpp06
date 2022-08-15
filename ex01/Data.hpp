/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:16:36 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 17:18:32 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DATA_H_
# define DATA_H_

# include <string>
# include <iostream>

struct Data {
	int a;
	std::string b;
	double c;
};

std::ostream &operator<<(std::ostream &o, Data const &d);

#endif