/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:03 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 17:34:57 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include <stdint.h>

uintptr_t serialize(Data *ptr) 
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data * deserialize(uintptr_t raw) 
{
	return reinterpret_cast<Data*>(raw);
}

int main (void)
{
	Data d;
	d.a = 42;
	d.b = "quarante deux";
	d.c = 21.21;
	
	std::cout << "Struct before: " << std::endl << d << std::endl;
	
	std::cout << std::endl << "struct address before serialization : " << &d << std::endl;
	uintptr_t s = serialize(&d);
	std::cout << std::endl << "Serialized struct address : " << s << std::endl;
	Data * ptrd = deserialize(s);
	std::cout << std::endl << "Deserialized struct address : " << ptrd << std::endl;

	std::cout << std::endl << "Struct after: " << std::endl << *ptrd << std::endl;
}