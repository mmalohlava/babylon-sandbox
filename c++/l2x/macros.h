/*!
  @file		macros.h
  @brief	basic macros for text processing
  
*/

#ifndef _MACROS_H
#define _MACROS_H
#include <ctype.h>

#define iscesym(_c)		(isalpha(_c) || isdigit(_c) || ((_c) == '_'))  
#define iswcesym(_c)		(iswalpha(_c) || iswdigit(_c) || ((_c) == '_'))  

#endif