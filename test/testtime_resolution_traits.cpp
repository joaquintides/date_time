

#include "boost/gdtl/time_resolution_traits.hpp"
#include "boost/gdtl/testfrmwk.hpp"


int
main() 
{
  using namespace boost::gdtl;
  check("milli traits num digits",  milli_res::num_fractional_digits() == 3);
  check("milli traits resolution adjust",  
	milli_res::res_adjust() == 1000);
  check("milli tick calculations",  
	milli_res::to_tick_count(0,0,0,1) == 1);
  check("milli tick calculations",  
	milli_res::to_tick_count(0,0,1,1) == 1001);
  check("milli tick calculations",  
	milli_res::to_tick_count(0,1,0,0) == 60000);
  boost::int64_t one_hour_milli = 3600*1000;
  check("milli tick calculations",  
	milli_res::to_tick_count(1,0,0,0) == one_hour_milli);
  
  check("micro traits num digits",  micro_res::num_fractional_digits() == 6);
  check("micro traits resolution adjust",  
	micro_res::res_adjust() == 1000000);
  check("micro tick calculations",  
	micro_res::to_tick_count(0,0,0,1) == 1);
  check("micro tick calculations",  
	micro_res::to_tick_count(0,0,1,1) == 1000001);
  check("micro tick calculations",  
	micro_res::to_tick_count(0,1,0,0) == 60000000);
  boost::int64_t one_hour_micro = 3600*1000;
  one_hour_micro = one_hour_micro*1000; //avoid compiler overflow!
  check("micro tick calculations",  
	micro_res::to_tick_count(1,0,0,0) == one_hour_micro);

  check("nano traits num digits",  nano_res::num_fractional_digits() == 9);
  check("nano traits resolution adjust",  
	nano_res::res_adjust() == 1000000000);
  check("nano tick calculations",  
	nano_res::to_tick_count(0,0,0,1) == 1);
  check("nano tick calculations",  
	nano_res::to_tick_count(0,0,1,1) == 1000000001);
  check("nano tick calculations",  
	nano_res::to_tick_count(0,1,0,0) == 60000000000);

  std::cout << one_hour_micro << std::endl;
  boost::int64_t one_hour_nano = one_hour_micro*1000;
  std::cout << one_hour_nano << std::endl;
  check("nano tick calculations",  
	nano_res::to_tick_count(1,0,0,0) == one_hour_nano);


  printTestStats();
  return 0;
}