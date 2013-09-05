/*!
  @file		hash.h
  @brief	hashtable class definition
*/


#ifndef _HASH_H
#define _HASH_H

#include <string.h>
#include <memory.h>

typedef char *pchar;
typedef struct _hash_item
{
	char *s;
	int value;
	_hash_item * next;
} hash_item, *phash_item;

class HashTable
{
public:
	HashTable(): _prime(6397),_size(8000)		{ _table = new hash_item[_size]; _clear_all(); };
	~HashTable();
	int Add( char *s, int value );
	bool Find( const char *s );
	phash_item Find_item(const char *s);

private:
	int				_prime;
	int				_size;
	phash_item		_table;
	int				_hash_code(const char * s);
	void			_clear_all()				{ memset( _table, 0, _size*sizeof(hash_item)); };
	void			_delete_items(phash_item p);
};

#endif 