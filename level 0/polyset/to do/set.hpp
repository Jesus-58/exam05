#pragma once

#include    "searchable_bag.hpp"

class   set
{
    private:

        searchable_bag  &bag;

    public:

        set(searchable_bag &bg);
        ~set();

        bool    has(int value) const;
        void    insert(int value);
        void    insert(int *value, int count);
        void    print() const;
        void    clear();

        searchable_bag  &get_bag();
};