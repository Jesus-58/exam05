#pragma once

#include    <iostream>

class   vect2
{
	private:
		int x;
		int y;

	public:
		vect2() : x(0), y(0) {}
		vect2(int num1, int num2) : x(num1), y(num2) {}
		vect2(const vect2 &other) : x(other.x), y(other.y) {}
		vect2	&operator=(const vect2 &other)
		{
			if (this != &other)
			{
				this->x = other.x;
				this->y = other.y;
			}
			return *this;
		}
		~vect2() {}

		int	operator[](int index) const
		{
			if (index == 0)
				return this->x;
			return this->y;
		}

		int &operator[](int index)
		{
			if (index == 0)
				return this->x;
			return this->y;
		}

		vect2	operator-() const
		{
			vect2	tmp;
			tmp.x = -this->x;
			tmp.y = -this->y;
			return tmp;
		}

		vect2	operator*(int num) const
		{
			vect2	tmp;
			tmp.x = num * this->x;
			tmp.y = num * this->y;
			return tmp;
		}

		vect2	&operator*=(int num)
		{
			this->x *= num;
			this->y *= num;
			return (*this);
		}

		vect2	&operator+=(const vect2 &other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		vect2	&operator-=(const vect2 &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}
		vect2	&operator*=(const vect2 &other)
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		vect2	operator+(const vect2 &other) const
		{
			vect2	tmp = *this;
			tmp.x += other.x;
			tmp.y += other.y;
			return (tmp);
		}

		vect2	operator-(const vect2 &other) const
		{
			vect2	tmp = *this;
			tmp.x -= other.x;
			tmp.y -= other.y;
			return (tmp);
		}

		vect2	operator*(const vect2 &other) const
		{
			vect2	tmp = *this;
			tmp.x *= other.x;
			tmp.y *= other.y;
			return (tmp);
		}
		
		vect2	&operator++()
		{
			this->x += 1;
			this->y += 1;
			return (*this);
		}
		vect2	operator++(int)
		{
			vect2	tmp = *this;
			++(*this);
			return (tmp);
		}
		vect2	&operator--()
		{
			this->x -= 1;
			this->y -= 1;
			return (*this);
		}
		vect2	operator--(int)
		{
			vect2	tmp = *this;
			--(*this);
			return (tmp);
		}

		bool	operator==(const vect2 &other) const
		{
			return ((this->x == other.x) && (this->y == other.y));
		}

		bool	operator!=(const vect2 &other) const
		{
			return (!(*this == other));
		}
};

vect2	operator*(int num, const vect2 &other)
{
	vect2	tmp(other);
	tmp *= num;
	return (tmp);
}

std::ostream	&operator<<(std::ostream &os, const vect2 &other)
{
	os << "{" << other[0] << "; " << other[1] << "}";
	return os;
}