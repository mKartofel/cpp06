/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:33:26 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 13:57:15 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

#include <iostream>
#include <exception>

int main(int argc, char **argv) 
{
  if (argc != 2) 
  {
	std::cout << "Wrong number of arguments" << std::endl;
	return 1;
  }

	try 
	{
		Convert c(argv[1]);
		std::cout << c;
	}
	catch (std::exception &e) 
	{
		std::cout << e.what() << std::endl;
	}
    
}