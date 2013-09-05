/*!
  @file		hash.cpp
  @brief	hashtable class implementation
*/

#include "hash.h"

/*!
	@brief function solve hash of string

	@param s string, it must be ended by \0
	@return hash code of string s
*/
int HashTable::_hash_code(const char *s)
{
  int j = 1;
  unsigned int h = (unsigned char) (s[0]);
  for(;;) 
  {
    unsigned char c = s[j];
    if(c==0)  return h;
    h = (h+h+c) % _prime;
    j++;
  }
}

/*!
	@brief add new value to hashtable

	@param s string, it must be ended by \0
	@return position in hash table
*/
int HashTable::Add(char *s, int value)
{
	phash_item _pom;
	int _h = _hash_code(s);
	if (!_table[_h].s)					
	{
		_table[_h].s = new char[strlen(s)+1]; 
		strcpy(_table[_h].s, s);
		_table[_h].value = value;
	} else
	{
		_pom = &_table[_h];
		while(_pom->next)
			_pom = _pom->next;
		_pom->next = new hash_item;
		_pom->next->next = NULL;
		_pom->next->s	= new char[strlen(s)+1]; 
		strcpy(_pom->next->s, s);
		_pom->next->value = value;
	}
	return _h;
}

/*!
	@brief find position of string in hashtable

	@param s string, it must be ended by \0
	@return position in hash table
*/
bool HashTable:: Find( const char *s)
{
	int _h = _hash_code(s);
	phash_item _pom;
	_pom = & _table[_h];
	while(_pom)
	{
		if (strcmp(_pom->s,s) == 0)
			return true;
		_pom = _pom->next;
	}
	return false;
}

/*!
	@brief destructor of HashTable class

*/
HashTable::~HashTable()
{
	
	for(int i=0; i<_size; i++)
	{
		_delete_items(_table[i].next);

		if (_table[i].s)
			delete [] _table[i].s;
	}
	delete [] _table;
}

/*!
	@brief delete items of chain in hashtable

	@param p start of chain to delete

*/
void HashTable::_delete_items(phash_item p)
{	
	if (p)
	{
		if (p->next)
			_delete_items(p->next);
		if (p->s) 
			delete [] p->s;
		delete p;
	}
}

/*!
	@brief find item which contain s and return pointer to it

	@param s string, it must be ended by \0
	@return pointer to item or NULL

*/
phash_item HashTable::Find_item(const char *s)
{
	int _h = _hash_code(s);
	phash_item _pom;
	_pom = & _table[_h];
	while(_pom)
	{
		if (strcmp(_pom->s,s) == 0)
			return _pom;
		_pom = _pom->next;
	}
	return NULL;
}

