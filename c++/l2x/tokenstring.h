/*!
  @file		tokenstring.h
  @brief	implementation of basic string

*/
#ifndef _TOKENSTRING_H
#define _TOKENSTRING_H

class TokenString
{
public:
	TokenString():	_max(255),_len(0)	{ _str = new char[_max]; };
	TokenString(const TokenString &a)	{ _str = new char[a._max]; _max=a._max; _len=a._len; memcpy(_str, a._str, _max); };
	void clean(void)					{ _len = 0; };
	char * get_string(void) const		{ _str[_len]='\0'; return _str; }; //{ if (_len) { _str[_len]='\0'; return _str;} else return NULL; };
	TokenString & operator<<(char c)	{ _add(c); return *this; };
	TokenString & operator<<(const char *s)
										{ while (_len+strlen(s) > _max) _realloc(); _str[_len]='\0'; strcat(_str,s); _len+=strlen(s); return *this;};
	TokenString & operator=(const TokenString &s)
										{ delete [] _str; _max = s._max; _len = s._len; _str = new char[_max]; memcpy(_str,s._str, _max); return *this; };
	bool operator==(const TokenString &s) const
										{ _str[_len]='\0'; if (strcmp(_str, s.get_string()) == 0) return true; else return false; }
	bool operator==(const char *s) const
										{ _str[_len]='\0'; if (strcmp(_str, s) == 0) return true; else return false; }
	char * operator*()					{ if (_len) { _str[_len]='\0'; return _str;} else return NULL; };
	void replace_str(const char *what, const char *by) 
										{ 
											char * _cp_s;	
											TokenString _pom; 
											char *_s;
											int i;
											
											
											if (!what || !by)
												return;
											_s=strstr(_str, what);
											_cp_s = _str;
											while(_s)
											{
												*_s = '\0';
												_pom << _cp_s;
												_pom << by;
												_s[0] = what[0];
												for(i=0, _cp_s = _s; _s[i]!='\0' && _s[i] == what[i]; i++, _cp_s++);
												_s = strstr(_cp_s, what);
											}
											// copy the rest
											_pom << _cp_s;
											*this = _pom;
										}

	~TokenString()						{ if (_str) delete [] _str; };
	int	 toInt(void) const				{
											return atoi(_str);
										}
	void delete_backslash(void)			{	
											if ( _str[0] != '\\' )
												return;
											char *_p = new char[_max];
											strncpy(_p, _str+1, _max -1);
											delete _str;
											_len--;
											_str = _p;
										}
	void print(void)	const			{ _str[_len]='\0'; std::cout<< _str << std::endl; };
private:
	void _realloc(void)					{ char *_p = new char[2*_max]; 
										  memcpy(_p,_str,_max); _max *=2; 
										  delete [] _str; _str = _p; 
										};
	void _add(char c)					{ if (_len+1 == _max) _realloc(); _str[_len++] = c; };
	int		_max;
	int		_len;
	char	*_str;
};

typedef TokenString *PTokenString;

#endif

