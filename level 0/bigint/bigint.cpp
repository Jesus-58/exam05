#include    "bigint.hpp"

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num)
{
	std::stringstream ss;
	ss << num;
	this->str = ss.str();
}

bigint::bigint(const bigint &other) : str(other.str) {}

bigint  &bigint::operator=(const bigint &other)
{
	if (this != &other)
		this->str = other.str;
	return *this;
}

bigint::~bigint() {}

std::string	bigint::getstr() const
{
	return (this->str);
}

std::string	reverse(const std::string &str)
{
	std::string reversestr;
	for (size_t i = str.length(); i > 0; i--)
		reversestr.push_back(str[i-1]);
	return (reversestr);
}

std::string	addition(const bigint &other1, const bigint &other2)
{
	std::string str1 = reverse(other1.getstr());
	std::string str2 = reverse(other2.getstr());
	std::string result;
	size_t	len1 = str1.length();
	size_t	len2 = str2.length();

	if (len1 > len2)
	{
		int diff = len1 - len2;
		while (diff > 0)
		{
			str2.push_back('0');
			diff--;
		}
	}
	else if (len2 > len1)
	{
		int diff = len2 - len1;
		while (diff > 0)
		{
			str1.push_back('0');
			diff--;
		}
	}

	int carry = 0;
	int digit1;
	int digit2;
	size_t len = str1.length();
	for (size_t i = 0; i < len; i++)
	{
		digit1 = str1[i] - '0';
		digit2 = str2[i] - '0';
		int res = digit1 + digit2 + carry;
		if (res > 9)
		{
			carry = res / 10;
			result.push_back((res % 10) + '0');
		}
		else
			result.push_back(res + '0');
	}
	if (carry != 0)
		result.push_back(carry + '0');
	return (reverse(result));
}

bigint  bigint::operator+(const bigint &other) const
{
	bigint  tmp(other);
	tmp.str.clear();
	std::string result = addition(*this, other);
	tmp.str = result;
	return (tmp);
}

bigint	&bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return (*this);
}

bigint	&bigint::operator++()
{
	*this += bigint(1);
	return *this;
}

bigint	bigint::operator++(int)
{
	bigint tmp = *this;

	*this += bigint(1);
	return (tmp);
}

bigint	bigint::operator<<(unsigned int num) const
{
	bigint	tmp = *this;
	tmp.str.insert(tmp.str.end(), num, '0');
	return (tmp);
}

bigint	bigint::operator>>(unsigned int num) const
{
	bigint	tmp = *this;
	size_t	len = tmp.str.length();
	if (num >= len)
		tmp.str = "0";
	else
		tmp.str.erase(tmp.str.length() - num, num);
	return (tmp);
}

bigint	&bigint::operator<<=(unsigned int num)
{
	*this = *this << num;
	return (*this);
}

bigint	&bigint::operator>>=(unsigned int num)
{
	*this = *this >> num;
	return (*this);
}

unsigned int	strtouint(std::string str)
{
	std::stringstream ss(str);
	unsigned int result;
	ss >> result;
	return (result);
}

bigint	bigint::operator<<(const bigint &other) const
{
	bigint	tmp;
	tmp = *this << strtouint(other.str);
	return tmp;
}

bigint	bigint::operator>>(const bigint &other) const
{
	bigint	tmp;
	tmp = *this >> strtouint(other.str);
	return tmp;
}

bigint	&bigint::operator<<=(const bigint &other)
{
	*this = *this << strtouint(other.str);
	return *this;
}

bigint	&bigint::operator>>=(const bigint &other)
{
	*this = *this >> strtouint(other.str);
	return *this;
}

bool	bigint::operator==(const bigint &other) const
{
	return (this->getstr() == other.getstr());
}

bool	bigint::operator!=(const bigint &other) const
{
	return (!(*this == other));
}

bool	bigint::operator<(const bigint &other) const
{
	std::string str1 = this->str;
	std::string str2 = other.str;
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	if (len1 != len2)
		return (len1 < len2);
	return (str1 < str2);
}

bool	bigint::operator>(const bigint &other) const
{
	return (!(*this < other));
}

bool	bigint::operator<=(const bigint &other) const
{
	return ((*this < other) || (*this == other));
}

bool	bigint::operator>=(const bigint &other) const
{
	return ((*this > other) || (*this == other));
}

std::ostream	&operator<<(std::ostream &os, const bigint &other)
{
	os << other.getstr();
	return os;
}