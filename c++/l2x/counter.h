/*!
  @file		counter.h
  @brief	counter class definition
*/

#ifndef _COUNTER_H
#define _COUNTER_H

#include "hash.h"

#define PART_COUNTER			"part_c"
#define CHAPTER_COUNTER			"chapter_c"
#define SECTION_COUNTER			"section_c"
#define SUBSECTION_COUNTER		"subsection_c"
#define SUBSUBSECTION_COUNTER	"subsubsection_c"
#define PARAGRAPH_COUNTER		"paragraph_c"
#define SUBPARAGRAPH_COUNTER	"subparagraph_c"

class Counter: public HashTable
{
public:
	void Register_counter( char	*name, int value) /*!< register new counter with name 'name' and with starting value 'value' */
	{ Add(name,value); }
	int & operator[](const char *s)
	{ phash_item _pom = Find_item(s); if (_pom) return _pom->value; else return *(int *)0; } // if there isn't counter 's' then crash down
private:
};

#endif