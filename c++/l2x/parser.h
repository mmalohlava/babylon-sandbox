/*!
  @file		parser.h
  @brief	latex parser header file
  
  This file include classes for latex parser
*/
#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <string.h>

#include "token.h"
#include "macros.h"
#include "l2xvar.h"
#include "tokenstring.h"
#include "stack.h"
#include "counter.h"
#include "array.h"

typedef struct _DOCUMENT_SETTINGS
{
	TokenString	settings;
	TokenString style;
	TokenString date;

} DOCUMENT_SETTINGS;

typedef struct _CommandItem
{
	char * _commandstring;
	int	   _command;
} CommandItem, *PCommandItem;

/*!
	@class CommandList
	@brief this class store command-strings list

	This class stores string of command, now it is very simple, in the future it will become hashtable

*/
class CommandList
{
public:
	CommandList();
	~CommandList();
	void AddCommand(char *str_comm, int comm);
	bool FindCommand(char *str_comm, int *comm);
private:
	CommandItem		**_commanditems;
	int				_num;
	int				_max;
};


/*!
	@class Parser
	@brief latex parser base class
	
*/
class Parser
{
public:
	explicit Parser(std::istream &in, std::ostream &out);
	Token	 GetToken(void)	;
	bool	 IsEnd(void) const					{ return _isend; } ;
private:
	void				_printtoken()			{ _out << _tokenstring.get_string(); } ;
	void				_boot_commandlist();
	void				_readchar();				/*!< read char from _in stream */
	void				_putback();					/*!< put back char to _in stream */
	void				_readnexttoken();
	void				_skip_whitechars(void);
	void				_skip_comment(void);
	void				_getcommand(void);			/*!< find a command	*/
	TokenString			_get_begroup(void);
	int					_get_params(TokenString *p1, TokenString *p2);
	void				_close_openedsections(int actual_section);
	bool				_get_param_com(TokenString *p);	/*!< try to get one parameter in {} */
	bool				_get_param_ncom(TokenString *p);/*!< try to get one parameter in [] */
	int					_new_command(char);			/*!< define new command		*/
	int					_document_class(void);		/*!< process \documentclass	*/
	void				_process_new_command(TokenString s, int params); /*!< replace new command by its definition */
	
	std::istream &		_in;						/*!< input stream */
	std::ostream &		_out;						/*!< output stream */
	std::ostream &		_log;						/*!< log output stream */
	
	wint_t				_char;						/*!< character in input stream	*/
	int					_prevchar;					/*!< previous char of _char		*/
	Token				_token;						/*!< code of token  */
	TokenString			_tokenstring;				/*!< a string of token */
	CommandList			_commandlist;				/*!< command list */
	
	bool				_isend;
	bool				_skip_whitec;
	
	Stack<TokenString>  _env_stack;					/*!< stack for enviroments \begin{env} ... \end{env} */
	TokenString			_current_env;				/*!< current environment	*/
/*! @def number of classical section - paragraph, chapter, .... */
#define _OPENED_SECTIONS	7
	bool				_open_sections[_OPENED_SECTIONS]; /*!< array of flags, which specified opened section of text */
	Counter				_counters;					/*!< collection of counters - easy manipulation - new registration, unregistration, ++, --, ... */
	DOCUMENT_SETTINGS	_doc_settings;				/*!< settings of \document_class or \document_style		*/
	Array				_new_commands_list;			/*!< clever array which include newcommand definitions	*/
};

/*!
	@def definitions for indexing in array _open_sections
*/

#define	_SEC_PART				0
#define _SEC_CHAPTER			1
#define	_SEC_SECTION			2
#define _SEC_SUBSECTION			3
#define	_SEC_SUBSUBSECTION		4
#define _SEC_PARAGRAPH			5
#define _SEC_SUBPARAGRAPH		6



#endif
