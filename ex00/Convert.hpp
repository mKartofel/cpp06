/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:47:22 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 14:41:39 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP
# include <iostream>
# include <limits>
# include <string>
# include <cerrno>
# include <cstdlib>
# include <iomanip>
# define TYPE_UNSUPPORTED 0
# define TYPE_CHAR 1
# define TYPE_INT 2
# define TYPE_FLOAT 3
# define TYPE_DOUBLE 4


class Convert
{
private:
	Convert(void);
	Convert(Convert const & c);
	Convert & operator=(Convert const & c);
	int _findType(std::string const) const;
	bool _checkLimit(std::string const);
	void _charConvert(std::string const);
	void _intConvert(std::string const);
	void _floatConvert(std::string const);
	void _doubleConvert(std::string const);
	
	char _charValue;
	int _intValue;
	float _floatValue;
	double _doubleValue;
	std::string _pseudoLiteral;

	bool _conversionError;
	bool _outOfRangeError;

	bool _charError;
	bool _intError;
	bool _floatError;
	bool _doubleError;

public:
	Convert(std::string const);
	~Convert();

	void toChar(void) const;
	void toInt(void) const;
	void toFloat(void) const;
	void toDouble(void) const;
	bool getConversionError(void) const;
	bool getOutOfRangeError(void) const;
	void printCharValue(void) const;
	void printIntValue(void) const;
	void printFloatValue(void) const;
	void printDoubleValue(void) const;
};

std::ostream & operator<<(std::ostream & o, Convert const & c);

#endif
