/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:49:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 18:04:18 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ctime>
# include <cstdlib>
# include <iostream>
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"

Base	*generate(void)
{
	int random = std::rand() % 3;
	switch (random) 
	{
		case 0:
			std::cout << "Creation of type A object" << std::endl;
			return new A;
		case 1: 
			std::cout << "Creation of type B object" << std::endl;
			return new B;
		case 2: 
			std::cout << "Creation of type C object" << std::endl;
			return new C;
	}
	return NULL;
}

void	identify(Base *p)
{
	//If dynamic cast fails, return NULL pointer
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p) != NULL)
		std::cout << "C" << std::endl;

}

void	identify(Base &p)
{
	//If dynamic_cast is used to convert to a reference type and the conversion is not possible, an exception of type bad_cast is thrown instead
	try
	{
		dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e) {}
	
	try
	{
		dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
	}
	catch(const std::exception& e) {}

	try
	{
		dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
	}
	catch(const std::exception& e) {}
}

int main (void)
{
	srand(time(NULL));
	
	Base * p = generate();

	if (p)
	{
		identify(p);
		identify(*p);
		
		delete p;
	}

	return 0;
}
