

#include "boost/gdtl/posix_time/posix_time.hpp"
#include "boost/gdtl/testfrmwk.hpp"

int
main() 
{

  using namespace boost::posix_time;
  using namespace boost::gregorian;
  date d1(2002,Jan,1);
  std::string d1_string("2002-Jan-01");
  std::string t1_string("01:02:03");
  std::string t1_result = d1_string + " " + t1_string;
  ptime t1(d1,time_duration(1,2,3)); //2002-Jan-1 01:02:03
  std::cout << to_simple_string(t1) << std::endl;
  check("simple:      " + t1_result, t1_result == to_simple_string(t1));
  std::string iso_result = "20020101T010203";
  check("iso:         " + iso_result, iso_result == to_iso_string(t1));
  std::string iso_ext_result = "2002-01-01T01:02:03";
  check("iso ext:     " + iso_ext_result, iso_ext_result == to_iso_extended_string(t1));



#ifdef BOOST_GDTL_HAS_MILLISECONDS

  if (time_duration::resolution() == boost::gdtl::milli) {
    ptime t4(d1,hours(1)+minutes(2)+seconds(3)+millisec(4));
    std::string r3 = to_simple_string(t4);
    check("simple subsecond: "+r3 , 
	  std::string("2002-Jan-01 01:02:03.004000") == r3);
  }

#endif

#ifdef BOOST_GDTL_HAS_MICROSECONDS

  if (time_duration::resolution() == boost::gdtl::micro) {
    ptime t3(d1,hours(1)+minutes(2)+seconds(3)+microsec(4));
    std::string result = to_simple_string(t3);
    check("simple subsecond: "+result , 
	  std::string("2002-Jan-01 01:02:03.000004") == to_simple_string(t3));
    
    time_duration td2 =  hours(-12)+minutes(4)+seconds(2)+microsec(1);
    //  time_duration td2 =  hours(-12)+minutes(4)+seconds(2)+millisec(1);
    std::string r2 = to_simple_string(td2);
    check("neg subsecond duration: "+r2 , 
	  std::string("-11:55:57.999999") == r2);
  }
#endif

#ifdef BOOST_GDTL_HAS_NANOSECONDS

  if (time_duration::resolution() == boost::gdtl::nano) {
    ptime t2(d1,hours(12) + minutes(5) + seconds(1));
    time_period p1(t1,t2); //last value in period is 12:05:00 1/10000 sec less than t2
    std::string period_result("["+t1_result + "/" + d1_string + " " + "12:05:00.999999999]" );
    check("simple:      " + period_result + "==" + to_simple_string(p1), period_result == to_simple_string(p1));
    
    ptime t3(d1,hours(1)+minutes(2)+seconds(3)+nanosec(4));
    std::string result = to_simple_string(t3);
    check("simple subsecond: "+result , 
	  std::string("2002-Jan-01 01:02:03.000000004") == to_simple_string(t3));
    
    time_duration td2 =  hours(-12)+minutes(4)+seconds(2)+nanosec(100);
    std::string r2 = to_simple_string(td2);
    check("neg subsecond duration: "+r2 , 
	  std::string("-11:55:57.999999900") == r2);
    
    ptime t4(d1,hours(1)+minutes(2)+seconds(3)+millisec(4));
    std::string r3 = to_simple_string(t4);
    check("simple subsecond: "+r3 , 
	  std::string("2002-Jan-01 01:02:03.004000000") == r3);
  }
#endif


  printTestStats();

  return 0;

}