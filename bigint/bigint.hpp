#pragma once

#include    <iostream>
#include    <string>

class   bigint
{
    private:

        std::string num;
        void    removeZeros()
        {
            size_t  pos = num.find_first_not_of('0');
            if (pos == std::string::npos)
                num = "0";
            else
                num.erase(0, pos);
        }

    public:

        bigint() : num(0) {}
        bigint(const std::string &n) : num(n) {removeZeros();}
        bigint(unsigned int n) : num(std::to_string(n)) {}

        bigint  operator+(const bigint &other) const
        {
            std::string a = num;
            std::string b = other.num;
            std::string result "";

            while (a.size() < b.size())
                a = '0' + a;
            while (b.size() < a.size())
                b = '0' + b;
            int carry = 0;
            for (int i = a.size() - 1; i >= 0; i--)
            {
                int sum = (a[i] - '0') + (b[i] -'0') + carry;
                carry = sum / 10;
                sum %= 10;
                result.insert(result.begin(), '0' + sum);
            }
            if (carry)
                result.insert(result.begin(), '0' + carry);
            bigint res(result);
            res.removeZeros();
            return res;
        }
        
        bigint  &operator+=(const bigint &other)
        {
            *this = *this + other;
            return *this;
        }

        bigint  &operator++()
        {
            *this = *this + bigint(1);
            return *this;
        }

        bigint  operator++(int)
        {
            bigint  tmp = *this;
            ++(*this);
            return tmp;
        }

        bigint  operator<<(int shift) const
        {
            if (num == "0")
                return bigint("0");
            return bigint(num + std::string(shift, '0'));
        }

        bigint  operator>>(int shift) const
        {
            if (shift >= (int)num.size())
                return bigint("0");
            bigint res(num.substr(0, num.size() - shift));
            res.removeZeros();
            return res;
        }

        bigint  &operator<<=(int shift)
        {
            *this = *this << shift;
            return *this;
        }

        bigint  &operator>>=(int shift)
        {
            *this = *this >> shift;
            return *this;
        }

        bool    operator<(const bigint &other) const
        {
            if (num.size() != other.num.size())
                return num.size() < other.num.size();
            return num < other.num;
        }

        bool    operator>(const bigint &other) const
        {
            return other < *this;
        }

        bool    operator<=(const bigint &other) const
        {
            return !(*this > other);
        }

        bool    operator>=(const bigint &other) const
        {
            return !(*this < other);
        }

        bool    operator==(const bigint &other) const
        {
            return num == other.num;
        }

        bool    operator!=(const bigint &other) const
        {
            return !(*this == other);
        }

        friend std::ostream &operator<<(std::ostream &os, const bigint &other)
        {
            os << other.num;
            return os;
        }
}