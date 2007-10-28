
#include <list>
#include <vector>
#include <deque>
#include <iostream>

#include "AOPool.h"
#include <boost/test/minimal.hpp>

#pragma comment(lib,"libboost_unit_test_framework-vc80-mt-gd-1_34.lib")


int test_main(int, char *[])
{
	typedef AOPool<int,std::deque<int> > TPoolType;
	TPoolType pool;
	pool.insert(1);
	pool.insert(2);
	pool.insert(3);
	pool.insert(4);
	pool.insert(5);
	pool.insert(6);
    //TPoolType::citerator cit = pool.getAO();
	pool.initialize();

	for(int i=0;i<20;++i)
	{
		//BOOST_REQUIRE( *(cit)==((i%pool.get_size())+1) ); 
		//++cit;
		//cit++;
		BOOST_REQUIRE( *(pool.getAO())==((i%pool.get_size())+1) ); 
		//std::cout<<*(pool.getAO())<<std::endl;
	}
	return 0;
}
