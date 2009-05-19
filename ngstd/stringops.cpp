#include <ngstd.hpp>

namespace ngstd
{
  using namespace ngstd;

  bool StringFitsPattern(const string & str, const string & pattern)
  {
    int patternpos = 0;
    int strpos = 0;

    int patternsize = -1;
    for(unsigned int i=0; patternsize < 0 && i < pattern.size(); i++)
      if(pattern[i] == 0)
	patternsize = i;
    if(patternsize < 0)
      patternsize = pattern.size();

    int strsize = -1;
    for(unsigned int i=0; strsize < 0 && i<str.size(); i++)
      if(str[i] == 0)
	strsize = i;
    if(strsize < 0)
      strsize = str.size();

    bool ok = true;

    while(ok &&
	  patternpos < patternsize && strpos < strsize)
      {
	string nextpart = "";
	int nextpartsize = 0;
	int mindistance = 0;
	int maxdistance = 0;
	int strdistance;
	
	while(patternpos < patternsize &&
	      (pattern[patternpos] == '?' ||
	       pattern[patternpos] == '*'))
	  {
	    if(pattern[patternpos] == '?')
	      {
		mindistance++;
		if(maxdistance >= 0)
		  maxdistance++;
	      }
	    else if(pattern[patternpos] == '*')
	      maxdistance = -1;

	    patternpos++;
	  }

	while(patternpos < patternsize &&
	      pattern[patternpos] != '?' &&
	      pattern[patternpos] != '*')
	  {
	    nextpart += pattern[patternpos];
	    nextpartsize++;
	    patternpos++;
	  }
	


	unsigned int foundpos;
	
	if(nextpartsize == 0)
	  foundpos = strsize;
	else
	  {
	    foundpos = str.find(nextpart,strpos);
	    ok = (foundpos != str.size());
	  }
	
	if(ok)
	  {
	    strdistance = foundpos - strpos;
	    ok = (mindistance <= strdistance && 
		  (maxdistance == -1 || strdistance <= maxdistance));
	    
	    strpos =  foundpos + nextpartsize;
	  }
	
      }

    if(strpos < strsize)
      ok = false;

    //    (*testout) << "\"" << str << "\" fits \"" << pattern << "\" ? " << ok << endl;
    return ok;
  }








}
