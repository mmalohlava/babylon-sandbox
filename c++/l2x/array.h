/*!
  @file		array.h
  @brief	array class definition
*/

#ifndef _ARRAY_H
#define _ARRAY_H
#include "tokenstring.h"
#include "l2xvar.h"

typedef struct _A_ITEM
{
	TokenString	s;
	int			params;
} A_ITEM, *PA_ITEM;

class Array
{
public:
	Array(): _size(0),_max(512),_shift(0)
										{ _array = new PA_ITEM[_max]; };
	Array(int shift): _size(0),_max(512),_shift(shift)
										{ _array = new PA_ITEM[_max]; };
	Array(int max, int shift): _size(0),_max(max),_shift(shift)
										{ _array = new PA_ITEM[_max]; };
	int Add(TokenString const & s, int params)
										{
											if (_size == _max )	
												_realloc();
											_array[_size] = new A_ITEM;
											_array[_size]->s = s;
											_array[_size]->params = params;
											_size++;
											return ( (_size-1) + _shift );	// return index to array
										};
										PA_ITEM	operator[](int const c)
										{
											if  ( (c-_shift)>=0 && (c-_shift)<_size )
												return _array[c-_shift];
											else
												return (PA_ITEM)0;

										}
	~Array()							{
											for(int i=0; i<_size; i++)
												delete _array[i];
											delete [] _array;
										};
private:
	PA_ITEM *_array;					/*!< store string in array	*/
	int	_size;							/*!< size of array			*/
	int _max;							/*!< max size of array		*/
	int _shift;							/*!< shift of indexes in array */
	void _realloc(void)					
										{ 
										  PA_ITEM *_p = new PA_ITEM[2*_max]; 
										  memcpy(_p,_array,_max*sizeof(PA_ITEM)); 
										  _max *=2; 
										  delete [] _array; _array = _p; 
										};
};


#endif
