/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:48:25 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/08/15 16:40:51 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert() : _charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0), _pseudoLiteral(""), _conversionError(false), _outOfRangeError(false),
_charError(true), _intError(true), _floatError(true), _doubleError(true)
{
	return ;
}

Convert::Convert(std::string const s) : _charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0),  _pseudoLiteral(""), _conversionError(false), _outOfRangeError(false),
_charError(true), _intError(true), _floatError(true), _doubleError(true)
{
	if (_checkLimit(s) == true)
		return ;
		
	int type = _findType(s);
	if (type == TYPE_UNSUPPORTED)
	{
		std::cout << "Type unsupported" << std::endl;
		return ;
	}

	if (type == TYPE_CHAR)
		_charConvert(s);
	else if (type == TYPE_INT)
		_intConvert(s);
	else if (type == TYPE_FLOAT)
		_floatConvert(s);
	else if (type == TYPE_DOUBLE)
		_doubleConvert(s);
	return ;
}

Convert::Convert(Convert const & c)
{
	*this = c;
	return ;
}

Convert	&Convert::operator=(Convert const & c)
{
	(void)c;
	return (*this);
}

Convert::~Convert()
{
	return ;
}


/*Tests for a decimal digit character (between 0 and 9)*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Converts the initial portion of the string pointed to by nptr
 *	to long representation
 * 
 * @param nptr 
 * @return long 
 */
long	ft_atol(const std::string nptr)
{
	int		i;
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\r'
		|| nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}

/*Check if the argument is a valid C integer that does not overflow/underflow*/
int	arg_is_int(std::string arg)
{
	long	num;

	if (arg.length() > 10)
		return (0);
	num = ft_atol(arg);
	if (num <= 2147483647 && num >= -2147483648)
		return (1);
	return (0);
}

bool	Convert::_checkLimit(std::string const s)
{
	if (s == "+inf" || s == "-inf" || s == "nan")
	{
		_pseudoLiteral = s.substr(0, s.size());
		_floatError = false;
		_doubleError = false;
		return true;
	}
	if (s == "+inff" || s == "-inff" || s == "nanf")
	{
		_pseudoLiteral = s.substr(0, s.size() - 1);
		_floatError = false;
		_doubleError = false;
		return true;
	}
	return false;
}

int	Convert::_findType(std::string const s) const
{
	int		i = 0;
	bool	isInt = true;
	bool	isFloat = false;
	bool	noNumeric = true;

	if (s[0] && s[1] == '\0' && ft_isdigit(s[0]) == 0)
		return TYPE_CHAR;

	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		i++;
		noNumeric = false;
	}
	if (s[i] == '.')
	{
		isInt = false;
		i++;
		while (s[i] && ft_isdigit(s[i]))
		{
			noNumeric = false;
			i++;
		}
	}
	if (s[i] == 'f')
	{
		isFloat = true;
		i++;
	}
	if (s[i] || noNumeric || (isFloat && isInt))
		return TYPE_UNSUPPORTED;
	if (isFloat)
		return TYPE_FLOAT;
	if (isInt)
		return TYPE_INT;
	return TYPE_DOUBLE;
}

void Convert::_charConvert(std::string const s)
{
	_charValue = s[0];
	_charError = false;
	_intValue = static_cast<int>(_charValue);
	_intError = false;
	_floatValue = static_cast<float>(_charValue);
	_floatError = false;
	_doubleValue = static_cast<double>(_charValue);
	_doubleError = false;
}

void Convert::_intConvert(std::string const s)
{
	if (arg_is_int(s) == 0)
	{
		_outOfRangeError = true;
		return;
	}
	char const *str = s.c_str();
	_intValue = atoi(str);
	_intError = false;
	
	_floatValue = static_cast<float>(_intValue);
	_floatError = false;
	_doubleValue = static_cast<double>(_intValue);
	_doubleError = false;

	if (_intValue >= 0 && _intValue <= std::numeric_limits<char>::max())
	{
		_charValue = static_cast<char>(_intValue);
		_charError = false;
	}

}

void Convert::_floatConvert(std::string const s)
{
	char const *str = s.c_str();
	char *endptr = NULL;
	
	_floatValue =  std::strtof(str, &endptr);
	if (str == endptr)
	{
		_conversionError = true;
		return ;
	}
	if (errno == ERANGE)
	{
		_outOfRangeError = true;
		return ;
	}
	_floatError = false;

	_doubleValue = static_cast<double>(_floatValue);
	_doubleError = false;

	if (_floatValue >= std::numeric_limits<int>::min() && _floatValue <= std::numeric_limits<int>::max())
	{
		_intValue = static_cast<int>(_floatValue);
		_intError = false;
	}
	if (_floatValue >= 0 && _floatValue <= std::numeric_limits<char>::max())
	{
		_charValue = static_cast<char>(_floatValue);
		_charError = false;
	}
}

void Convert::_doubleConvert(std::string const s)
{
	char const *str = s.c_str();
	char *endptr = NULL;
	
	_doubleValue =  std::strtod(str, &endptr);
	if (str == endptr)
	{
		_conversionError = true;
		return ;
	}
	if (errno == ERANGE)
	{
		_outOfRangeError = true;
		return ;
	}
	_doubleError = false;

	if (_doubleValue >= -std::numeric_limits<float>::max() && _doubleValue <= std::numeric_limits<float>::max()) //the lowest possible value is the negative of the maximum possible value
	{
		_floatValue = static_cast<float>(_doubleValue);
		_floatError = false;
	}
	if (_doubleValue >= std::numeric_limits<int>::min() && _doubleValue <= std::numeric_limits<int>::max())
	{
		_intValue = static_cast<int>(_doubleValue);
		_intError = false;
	}
	if (_doubleValue >= 0 && _doubleValue <= std::numeric_limits<char>::max())
	{
		_charValue = static_cast<char>(_doubleValue);
		_charError = false;
	}
}


bool Convert::getConversionError(void) const
{
	return _conversionError;
}
bool Convert::getOutOfRangeError(void) const
{
	return _outOfRangeError;
}

std::ostream & operator<<(std::ostream & o, Convert const & c)
{
	if (c.getOutOfRangeError() == true)
		std::cout << "Value out of its type range" << std::endl;
	else if (c.getConversionError() == true)
		std::cout << "Conversion error" << std::endl;
	else
		{
			// o.precision(15);
			c.printCharValue();
			c.printIntValue();
			c.printFloatValue();
			c.printDoubleValue();
		}
	return o;
}

void Convert::printCharValue(void) const
{
	std::cout << "char: ";
	if (_charError == true)
		std::cout << "impossible" << std::endl;
	else if (std::isprint(_charValue) == 0)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << _charValue << std::endl;;
}

void Convert::printIntValue(void) const
{
	std::cout << "int: ";
	if (_intError == true)
		std::cout << "impossible" << std::endl;
	else
		std::cout << _intValue << std::endl;;
}
void Convert::printFloatValue(void) const
{
	std::cout << "float: ";
	if (_floatError == true)
		std::cout << "impossible" << std::endl;
	else if (_pseudoLiteral.empty() == false)
		std::cout << _pseudoLiteral << "f"  << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << _floatValue << "f" << std::endl;
}
void Convert::printDoubleValue(void) const
{
	std::cout << "double: ";
	if (_doubleError == true)
		std::cout << "impossible" << std::endl;
	else if (_pseudoLiteral.empty() == false)
		std::cout << _pseudoLiteral << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << _doubleValue << std::endl;
}


