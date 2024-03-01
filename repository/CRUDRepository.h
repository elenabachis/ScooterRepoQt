#pragma once

#include <vector>

template<class T>
class CrudRepository {
public:

    virtual bool create(T new_entity) = 0;

    virtual void read(std::vector<T>& elements) = 0;

    virtual bool update(T entity) = 0;

    virtual bool remove(T entity) = 0;
};


