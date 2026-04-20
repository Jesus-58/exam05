#pragma once

#include    "searchable_bag.hpp"

class   set
{
    private:

        searchable_bag  &bag;
        set();
        set(const set &other);
        set &operator=(const set &other);
    public:

        set(searchable_bag &bg) : bag(bg) {}
        ~set() {}

        bool    has(int value) const
        {
            return (bag.has(value));
        }

        void    insert(int value)
        {
            if (!(bag.has(value)))
                bag.insert(value);
        }

        void    insert(int *values, int count)
        {
            for (int i = 0; i < count; i++)
                insert(values[i]);
        }
        
        void    print() const
        {
            bag.print();
        }

        void    clear()
        {
            bag.clear();
        }

        searchable_bag  &get_bag()
        {
            return (bag);
        }
};