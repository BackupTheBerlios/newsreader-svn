#pragma once

/// Cycle iterator
/// Can be used with all Sequence containers (list,vector deque)
template <class Container>
class cycle_iterator : public std::iterator<std::bidirectional_iterator_tag,typename Container::value_type>
{
public:
	typedef typename Container::reference reference;

	cycle_iterator(Container& c):m_ContainerRef(c)
	{
	}

    void set_container()
    {
        it = m_ContainerRef.begin();
    }

	cycle_iterator<Container>& begin()
	{
		return m_ContainerRef.begin();
	}

	reference operator*()
	{
		return (*it);
	}

	typename Container::iterator& operator++()
	{
		typename Container::iterator itend = m_ContainerRef.end();
		--itend;
		if(it == itend )
		{
			it=m_ContainerRef.begin();
			return it;
		}
		else
		{
			++(it);
			return it;
		}
	}

	typename Container::iterator& operator++(int)
	{

		if(it == (m_ContainerRef.end()-1))
		{
			it=m_ContainerRef.begin();
			return it;
		}
		else
		{
			return ++(it);
		}
	}

protected:
	Container& m_ContainerRef;
	typename Container::iterator it;
};