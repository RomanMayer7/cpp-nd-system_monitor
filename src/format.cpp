#include <string>

#include "format.h"

using std::string;

// DONE: format helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
 { 

  string result;
  // compute h, m, s
  string h = std::to_string(seconds / 3600);
  string m = std::to_string((seconds % 3600) / 60);
  string s = std::to_string((seconds % 3600) % 60);
  
  if(h.length()<2)
  {
      h= "0"+h;
  }

  if(m.length()<2)
  {
      m= "0"+m;
  }

  if(s.length()<2)
  {
      s= "0"+s;
  }

  if (h.compare("00") != 0) {
    result = h + ':' + m + ":" + s;
  }
  else {
    result =  m + ":" + s;
  }

  return result;
 }