#ifndef DATE_TIME_DATE_FORMATTING_LOCALES_HPP___
#define DATE_TIME_DATE_FORMATTING_LOCALES_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#ifndef BOOST_NO_STD_LOCALE

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_names_put.hpp"
#include "boost/date_time/parse_format_base.hpp"
//#include <string>
#include <sstream>
#include <iomanip>


namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class facet_type,
	   class charT = char>
  class ostream_month_formatter
  {
  public:
    typedef typename facet_type::month_type month_type;
    typedef std::basic_ostream<charT> ostream_type;

    //! Formats a month as as string into an output iterator
    static void format_month(const month_type& month,
			     ostream_type& os,
			     const facet_type& f,
			     month_format_spec fs)
    {

      switch (fs) 
      {
        case month_as_short_string: 
        { 
	  std::ostreambuf_iterator<charT> oitr(os);
	  f.put_month_short(oitr, month.as_enum());
          break;
        }
        case month_as_long_string: 
        { 
	  std::ostreambuf_iterator<charT> oitr(os);
	  f.put_month_long(oitr, month.as_enum());
          break;
        }
        case month_as_integer: 
        { 
	  os << std::setw(2) << std::setfill('0') << month;
          break;
        }
     
      }
    } // format_month

  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type,
	   class facet_type,
	   class charT = char>
  class ostream_ymd_formatter
  {
  public:
    typedef typename ymd_type::month_type month_type;
    typedef ostream_month_formatter<facet_type> month_formatter;
    typedef std::basic_ostream<charT> ostream_type;
    typedef std::basic_string<charT> foo_type;

    //! Convert ymd to a standard string formatting policies
    /*! This is standard code for handling date formatting with
     *  year-month-day based date information.  This function 
     *  uses the format_type to control whether the string will
     *  contain separator characters, and if so what the character
     *  will be.  In addtion, it can format the month as either
     *  an integer or a string as controled by the formatting 
     *  policy
     */ 
    //     static string_type ymd_to_string(ymd_type ymd)
//     {
//       std::ostringstream ss;
//       facet_type dnp;
//       ymd_put(ymd, ss, dnp);
//       return ss.str();
//       }

    // Put ymd to ostream -- part of ostream refactor
    static void ymd_put(ymd_type ymd, 
			ostream_type& os,
			const facet_type& f)
    {
      os << ymd.year;
      std::ostreambuf_iterator<charT> oitr(os);
      if (f.has_date_sep_chars()) {
	f.month_sep_char(oitr);
      }
      month_formatter::format_month(ymd.month, os, 
 				    f, month_as_short_string);


      if (f.has_date_sep_chars()) {
	f.day_sep_char(oitr);
      }
      os  << std::setw(2) << std::setfill('0') 
	  << ymd.day;
    }

  };


  //! Convert a date to string using format policies
  template<class date_type,
	   class facet_type,
	   class charT = char>
  class ostream_date_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename date_type::ymd_type ymd_type;

    //! Put date into an ostream 
    static void date_put(const date_type& d, 
			 ostream_type& os,
			 const facet_type& f)
    {
      special_values sv = d.as_special();
      if (sv == not_special) {
	ymd_type ymd = d.year_month_day();
	ostream_ymd_formatter<ymd_type, facet_type, charT>::ymd_put(ymd, os, f);
      }
      else { // output a special value
	std::ostreambuf_iterator<charT> coi(os);
	f.put_special_value(coi, sv);
      }
    }    
 

    //! Put date into an ostream 
    static void date_put(const date_type& d, 
			 ostream_type& os)
    {
      //retrieve the local from the ostream
      std::locale locale = os.getloc();
      if (std::has_facet<facet_type>(locale)) {
	//	std::cout << "Good Deal Dude" << std::endl;
	const facet_type& f = std::use_facet<facet_type>(locale);
	date_put(d, os, f);
      }
      else {
	//default to something sensible if no facet installed
	facet_type default_facet;
	date_put(d, os, default_facet);
      }
    } // date_to_ostream    
  }; //class date_formatter

  
} } //namespace date_time

#endif

/* Copyright (c) 2002
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */
#endif
