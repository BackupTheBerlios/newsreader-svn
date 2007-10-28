#pragma once

#include "cycle_iterator.h"

/// Pool which is based on any STL Sequence containers 
/// and has only one public iterator - cycle iterator
template <class T,class Y=std::list<T> >
class AOPool
{
    Y container;
    cycle_iterator<Y> cit_;
	typedef typename Y::iterator iterator;
public:
    typedef cycle_iterator<Y> citerator;
    AOPool():cit_(container){};
    void insert(const T& obj)
    {
        container.push_back(obj);
    }

	void initialize()
	{
        cit_.set_container();
	}

    citerator  getAO()
    {
		citerator it = cit_;
		++cit_;
        return it;
    }
	std::size_t get_size() const
	{
		return container.size();
	}

	void stop()
	{
		iterator it = container.begin();
		for(;it!=container.end();++it)
			(*it)->stop();

	}
};
