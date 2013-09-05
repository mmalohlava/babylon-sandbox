/*!
  @file		parser.cpp
  @brief	implementation of latex parser
  
  This file include implementation of latex parser
*/

#include "parser.h"

/*!
	@brief constructor of class Parser

	@param in input stream (often file or cin)
	@param out output stream
*/
Parser::Parser(std::istream &in, std::ostream &out):	_in(in),
														_out(out),
														_isend(false),
														_skip_whitec(false),
														_log(out),
														_new_commands_list(last_cmd)
{
	_boot_commandlist();
	
	// clear all sections flags
	for(int i=0; i<_OPENED_SECTIONS; i++)
		_open_sections[i] = false;
	// register counter for part, chapter, section, subsection, subsubsection,...
	
	_counters.Register_counter(PART_COUNTER, 0);
	_counters.Register_counter(CHAPTER_COUNTER, 0);
	_counters.Register_counter(SECTION_COUNTER, 0);
	_counters.Register_counter(SUBSECTION_COUNTER, 0);
	_counters.Register_counter(SUBSUBSECTION_COUNTER, 0);
	_counters.Register_counter(PARAGRAPH_COUNTER, 0);
	_counters.Register_counter(SUBPARAGRAPH_COUNTER, 0);
}

/*!
	@brief skip all white character in the stream
*/
void Parser::_skip_whitechars(void)
{
	_readchar();
	while ( !_isend && isspace(_char)  )
	{
		_readchar();
	}
	if (!_isend)
		_in.putback(_char);
}

/*!
	@brief read char from stream
*/
void Parser::_readchar()
{
	_prevchar	= _char;
	_char		= _in.get();
	
	if (_in.eof())
	{
		_isend = true;
	}
}

/*!
	@brief put back char to _in stream
*/
void Parser::_putback()
{
	_in.putback(_char);
	_char = _prevchar;
}
/*!
	@brief return one token from stream
*/
void Parser::_readnexttoken()
{
	_tokenstring.clean();

	if (_skip_whitec)
	{
		_skip_whitechars();
	}

	if (_isend)
	{
		_token = tok_isend;
		return ;
	}
	_readchar();
	if (isspace(_char))
	{
		_tokenstring << _char;
		_token = _char;
		return ;
	} else
	if (ispunct(_char))
	{
		_token = _char;
		_tokenstring << _char;
		return;			
	} else
	{
		while (iscesym(_char) && !_isend)
		{
			/* create string from chars */
			_tokenstring << _char;		
			_readchar();
		}
		if (!_isend) _in.putback(_char);
		_token = tok_word;
	}
	//	_tokenstring.print();
}

/*!
	@brief return one token from stream
*/
Token Parser::GetToken(void) 
{
	
	_readnexttoken();
	
	switch (_token)
	{
	case backslash:
		_getcommand();
		break;
	case cr:
		break;
	case newline:
		_printtoken();		// \n latex bere jako whitespace
		_skip_whitechars(); // vse bile, co je na zacatku noveho radku se ignoruje
		break;
	case space:
	case tab:
			_printtoken();		// vice whitespace se bere jako jedna whitespace
			_skip_whitechars();
			break;
	case tok_word:
			_printtoken();		
		break;
	case percent:
		_skip_comment();
		break;
	case accent1:			// oteviraci uvozovky se delaji pomoci ''
		_readchar();
		if ( _char == accent1)
		{
			_token = quote;
			_tokenstring.clean();
			_tokenstring << '\"';
		} else
		{
			_in.putback(_char);
		}
		_printtoken();
		break;
	case accent2:			// uzaviraci uvozovky se delaji pomoci ``
		_readchar();
		if ( _char == accent2)
		{
			_token = quote;
			_tokenstring.clean();
			_tokenstring << '\"';
		} else
		{
			_in.putback(_char);
		}
		_printtoken();
		break;
	case hyphen:
		_tokenstring.clean();
		_readchar();
		if ( _char == hyphen )
		{
				_readchar();
					if ( _char == hyphen )
					{
						_tokenstring << "&#8212;";
					}
					else
					{
						_in.putback(_char);
						_tokenstring << "&#8211;";
					}
		} else
		{
			_in.putback(_char);
			_tokenstring << "&#173;";
		}
		_printtoken();
		break;
	case tilda:
		_tokenstring.clean();
		_tokenstring << "&nbsp;";
		_printtoken();
		break;
	default:
			_printtoken();
			break;
	}
	return _token;
}

void Parser::_skip_comment()
{
	while (_char!=newline && !_isend)
	{
		_readchar();
	}
	_out << std::endl;
	_skip_whitechars(); // skip all whitechars on new line
}
/*!
	find command in command list and set parameters of parsing 
	Command is a string started with \
*/
void Parser::_getcommand()
{
	int command;

	_readnexttoken();
	_commandlist.FindCommand(_tokenstring.get_string(), &command);

	int _num_of_params = 0; //!!!!!!!!!!!!!!
	TokenString p1,p2;		//!!!!!!!!!!!!!!

	switch (command)
	{
	case doc_class_cmd:			// \documentclass
			_num_of_params = _document_class();
			break;
	case begin_cmd:									// command \begin{}
		{
		TokenString s = _get_begroup();
		if (*s)	// *s <=> s.get_string()
		{	
			_env_stack.Push(s);
			_current_env = s;
			if (_current_env == "document")
			{
				_out << "<" << s.get_string() ;
				if (*_doc_settings.style)
				{
					_out << " style=\"" << *_doc_settings.style << "\" ";
				}
				if (*_doc_settings.settings)
				{
					_out << "settings=\"" << *_doc_settings.settings << "\" ";
				} 
				if (*_doc_settings.date)
				{
					_out << "style=\"" << *_doc_settings.date << "\" ";
				}
				_out << ">";
			}
			else
				_out << "<" << s.get_string() << ">" ;
			
		}
		else
		{
			_log << "Chyba u begin" << std::endl;
		}
		break;
		}
	case end_cmd:									// command \end{}
		{
		TokenString s = _get_begroup();
		if (*s)	// *s <=> s.get_string()
		{	
			if (!_env_stack.empty() && (_env_stack.Pop() == s))
			{
				if (s == "document")
					_close_openedsections(_SEC_PART);

				_out << "</" << s.get_string() << ">" ;
			} else 
			{ 
				_env_stack.Push(s);
				std::cerr << "Chyba: casti \\begin a \\end si neodpovidaji" << std::endl;
			}
		}
		else
		{
			std::cerr << "Chyba u end" << std::endl;
		}
		break;
		}
		break;
	case usepackage_cmd:							// \usepackage{}
		_num_of_params = _get_params(&p1,&p2);
		break;
	case pagestyle_cmd:								// \pagestyle
		_num_of_params = _get_params(&p1,&p2);
		break;
	case thispagestyle_cmd:							// \thispagestyle
		_num_of_params = _get_params(&p1,&p2);
		break;
	case hyphenation_cmd:							// \hyphenation
		_num_of_params = _get_params(&p1,&p2);
		break;
	case mbox_cmd:									// \mbox{}
		_num_of_params = _get_params(&p1,&p2);
		break;
	case today_cmd:
		_num_of_params = _get_params(&p1,&p2);
		// out << "dnesni datum" ;
		break;
	case newtheorem_cmd:							// \newtheorem{}{}[] nebo {}[]{} nebo []{}{} -> nepovinny parametr je citac
		_num_of_params = _get_params(&p1,&p2);
		break;
	case newcommand_cmd:							// \newcommand{prikaz}[parametry]{definice}
		_new_command(0);
		break;
	case renewcommand_cmd:
		_new_command(1);
		break;
	case title_cmd:
			_num_of_params = _get_param_com(&p1);
			if (_num_of_params && *p1)
			{
				p1.replace_str("\\\\", "<br/>" );
				_out << "<title>";
				_out << *p1;		// TODO: substitution of // -> \n in long title
				_out << "</title>";
			}

		break;
	case author_cmd:
			_num_of_params = _get_param_com(&p1);
			if (_num_of_params && *p1)
			{
				p1.replace_str("\\\\", "<br/>" );
				_out << "<author>";
				_out << *p1;		// TODO: substitution of // -> \n in long title
				_out << "</author>";
			}

		break;
	case lparenthesis:
		{
			TokenString s;
			s << "math";
			_env_stack.Push(s);			
			_out << "<math>" ;
		}
		break;
	case rparenthesis:
		{
			
			if (_env_stack.empty() || !(_env_stack.Pop() == "math"))
			{
				_log << "Chyba! - prekryta environment" << std::endl;
				break;
			}
			_out << "</math>" ;
		}
		break;
	case lbracket:
		{
			TokenString s;
			s << "math";
			_env_stack.Push(s);			
			_out << "<br/><math>" ;
		}
		break;
	case rbracket:
		{
			
			if (_env_stack.empty() || !(_env_stack.Pop() == "math"))
			{
				_log << "Chyba! - prekryta environment" << std::endl;
				break;
			}
			_out << "</math><br/>" ;
		}
		break;
	// /------------------------------\
	// | commands of text structuring |----------------------------\
	// \------------------------------/                            |
	case part_cmd:
		_close_openedsections(_SEC_PART);
		_counters[PART_COUNTER]++;	
		_open_sections[_SEC_PART] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<part title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[PART_COUNTER];
		_out << "\">";
		break;
	case chapter_cmd:
		_close_openedsections(_SEC_CHAPTER);
		_counters[CHAPTER_COUNTER]++;
		_open_sections[_SEC_CHAPTER] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<chapter title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[CHAPTER_COUNTER];
		_out << "\">";
		break;
	case section_cmd:								// 	\section{name} or \section*{name}
		_close_openedsections(_SEC_SECTION);
		_counters[SECTION_COUNTER]++;
		_open_sections[_SEC_SECTION] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<section title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[SECTION_COUNTER];
		_out << "\">";
		break;
	case subsection_cmd:							
		_close_openedsections(_SEC_SUBSECTION);
		_counters[SUBSECTION_COUNTER]++;
		_open_sections[_SEC_SUBSECTION] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<subsection title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[SUBSECTION_COUNTER];
		_out << "\">";
		break;
	case subsubsection_cmd:
		_close_openedsections(_SEC_SUBSUBSECTION);
		_counters[SUBSUBSECTION_COUNTER]++;
		_open_sections[_SEC_SUBSUBSECTION] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<subsubsection title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[SUBSUBSECTION_COUNTER];
		_out << "\">";
		break;
	case paragraph_cmd:
		_close_openedsections(_SEC_PARAGRAPH);
		_counters[PARAGRAPH_COUNTER]++;
		_open_sections[_SEC_PARAGRAPH] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<paragraph title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[PARAGRAPH_COUNTER];
		_out << "\">";
		break;
	case subparagraph_cmd:
		_close_openedsections(_SEC_SUBPARAGRAPH);
		_counters[SUBPARAGRAPH_COUNTER]++;
		_open_sections[_SEC_SUBPARAGRAPH] = true;
		_num_of_params = _get_params(&p1,&p2);
		_out << "<subparagraph title=\"" << p1.get_string() << "\"";
		_out << " num=\"" << _counters[SUBPARAGRAPH_COUNTER];
		_out << "\">";
		break;
	// /-----------------------------\
	// | simple TEXT output commands | -----------\
	// \-----------------------------/             |
	case backslash:
	case newline_cmd:
		_num_of_params = _get_params(&p1,&p2);
		_out << "<br />";
		break;
	case ldots_cmd:
		_num_of_params = _get_params(&p1,&p2);
		_out << "..." ;
	case latex_cmd:
	case latexe_cmd:
	case tex_cmd:	// \TeX
		_num_of_params = _get_params(&p1,&p2);
		_out << "<tex />" ;
		break;
	case tilda:					/* -----\							*/
	case hash:					//		|
	case dollar:				//		|
	case percent:				//		|-----special characters
	case amp:					// -----/
		_num_of_params = _get_params(&p1,&p2);
		_printtoken();
		break;
	default:		
		if ( command >= last_cmd && _new_commands_list[command])
		{
			_process_new_command( _new_commands_list[command]->s, _new_commands_list[command]->params);
		} else
		{
			// non-recognized command => log it 
			_out << "[?"<<_tokenstring.get_string()<<"?]";
			_num_of_params = _get_params(&p1,&p2);
		}
		break;
	}
}

/*!
	@brief try to find begin/end parameter
	@return parameter of \begin or \end
*/
TokenString	Parser::_get_begroup(void)
{
	_skip_whitechars();
	_readchar();
	if (_char != lbrace )
		return TokenString();
	_skip_whitechars();
	_readnexttoken();
	TokenString pom(_tokenstring);
	_skip_whitechars();
	_readnexttoken();
	if (_token != rbrace)
	{
		//std::cerr << "Chybny parametr u end/begin" << std::endl;
		return TokenString();
	}
	return pom;
}

/*!
	@brief try to recognize parameters in command \command{p1}[p2]
	@param p1 will be filled with compulsory parameters (params. in {})
	@param p2 will be filled with non-compulsory parameters (params in [])
	@return number of parameters 0=none, 1=only comp, 2=only non-comp, 4=comp+non-comp
*/
int Parser::_get_params(TokenString *p1, TokenString *p2)
{
	int save_c;
	int ret = 1;
	bool there_was_space = false;

	_skip_whitechars();
	_readchar();
	if (_char != lbrace && _char != lbracket )
	{
		_in.putback(_char);
		return 0;
	}
	save_c = _char;
	_skip_whitechars();
	if (save_c == lbrace)
	{
		p1->clean();
		_readchar();
		while (_char != rbrace && !_isend)
		{
				*p1 << _char;
				_readchar();
		}
		if (isspace(_char))
		{
			_skip_whitechars();
			there_was_space = true;
		}
		_readchar();
		if (_char == lbracket)
		{
			p2->clean();
			_readchar();
			while (_char != rbracket && !_isend)
			{
				*p2 << _char;
				_readchar();
			}
			_in.putback(_char);
			ret=4;
		} else { if (there_was_space) { _in.putback(' '); }; _in.putback(_char);}
	} else 
	{
		p2->clean();
		_readchar();
		while (_char != rbracket && !_isend)
		{
				*p2 << _char;
				_readchar();
		}
		ret=2;
		if (isspace(_char))
		{
			_skip_whitechars();
			there_was_space = true;
		}
		_readchar();
		if (_char == lbrace)
		{
			p1->clean();
			_readchar();
			while (_char != rbrace && !_isend)
			{
				*p1 << _char;
				_readchar();
			}
			//_in.putback(_char);
			ret=4;
		} else { if (there_was_space) { _in.putback(' '); } ; _in.putback(_char);}
	}
	return ret;
}
/*!
	@brief close all opened sections of text like \section , \chapter ,...
	@param actual_section close all section great or equal to actual_section in _open_sections array
*/
void Parser::_close_openedsections(int actual_section)
{
	for(int i=_OPENED_SECTIONS-1; i>=actual_section; i--)
	{
		if (_open_sections[i])
		{
		switch (i)
		{
			case _SEC_PART:
				_out << "</part>";
				break;
			case _SEC_CHAPTER:
				if (i>actual_section) 
					_counters[CHAPTER_COUNTER] = 0;
				_out << "</chapter>";
				break;
			case _SEC_SECTION:
				if (i>actual_section) 
					_counters[SECTION_COUNTER] = 0;
				_out << "</section>";
				break;
			case _SEC_SUBSECTION:
				if (i>actual_section) 
					_counters[SUBSECTION_COUNTER] = 0;
				_out << "</subsection>";
				break;
			case _SEC_SUBSUBSECTION:
				if (i>actual_section) 
					_counters[SUBSUBSECTION_COUNTER] = 0;
				_out << "</subsubsection>";
				break;
			case _SEC_PARAGRAPH:
				if (i>actual_section) 
					_counters[PARAGRAPH_COUNTER] = 0;
				_out << "</paragraph>";
				break;
			case _SEC_SUBPARAGRAPH:
				if (i>actual_section) 
					_counters[SUBPARAGRAPH_COUNTER] = 0;
				_out << "</subparagraph>";
				break;
		}
		_open_sections[i] = false;		// clear open_section flag
		
		}
	}
}

/*!
	@brief try to get one parameter in {} 
	@param p string to obtain parameter
	@return true if string is returned else false
*/
bool Parser::_get_param_com(TokenString *p)
{
	bool whitechar = false;
	char wchar;
	_readchar();
	if (isspace(_char))
	{
		whitechar =  true;
		if (_char==cr)
			_char=newline;
		wchar	  =  _char;
	}
	else
		_putback();
	_skip_whitechars();
	_readchar();
	if (_char != lbrace )
	{
		_in.putback(_char);
		if (whitechar) 
			_in.putback(wchar);
		return false;
	}
	_readchar();
	while (_char != rbrace && !_isend)
	{
		*p << _char;
		_readchar();
	}
	if (_char != rbrace)
		return false;
	else
		return true;
}


/*!
	@brief try to get one parameter in []
	@param p string to obtain parameter
	@return true if string is returned else false
*/
bool Parser::_get_param_ncom(TokenString *p)
{
	bool whitechar = false;
	char wchar;
	_readchar();
	if (isspace(_char))
	{
		whitechar =  true;
		if (_char==cr)
			_char=newline;
		wchar	  =  _char;
	}
	else
		_putback();
	_skip_whitechars();
	_readchar();
	if (_char != lbracket )
	{
		_in.putback(_char);
		if (whitechar) 
			_in.putback(wchar);
		return false;
	}
	_readchar();
	while (_char != rbracket && !_isend)
	{
		*p << _char;
		_readchar();
	}
	if (_char != rbracket)
		return false;
	else
		return true;
}

/*!
	@brief define new command
	@param i specified how function _new_command work ( 0 - add new command, 1 = redefine existing command)
	@return number of parameters of \newcommand
*/
int Parser::_new_command(char com)	// \newcommand{prikaz}[args]{definition} -> {t1}[t2]{t3}
{
	TokenString t1, t2, t3;
	int params = 0;
	_skip_whitechars();
	if (!_get_param_com(&t1))
		return params;
	params++;
	if (!_get_param_ncom(&t2))
	{
		t2.clean();
		if (!_get_param_com(&t3))
			return params;
		else
		{
			params++;
			if (!_get_param_ncom(&t2))
			{
				t2.clean();
				goto loging;
			}
		}
		
	} else
	{
		params++;
		if (!_get_param_com(&t3))
			return params;
	}

loging:
	int new_cmd_num;
	switch (com)
	{
	case 0: // only add new command = \newcommand
		_log << "<!--New command: " << *t1 << " : "<< t2.get_string() <<" : "<<*t3<< " -->" << std::endl;
		
		if (*t2)
			new_cmd_num = _new_commands_list.Add(t3, t2.toInt() ); // t2 is a number of params;
		else
			new_cmd_num = _new_commands_list.Add(t3, 0 ); // t2 is a number of params;
		// i must delete the first char(='\\') in cmd
		t1.delete_backslash();
		_commandlist.AddCommand(*t1, new_cmd_num);
		break;
	case 1: // redefine existing command
		_log << "<!--Redefine command: " << *t1 << " : "<< t2.get_string() <<" : "<<*t3<< " -->" << std::endl;
		// i must delete the first char(='\\') in cmd
		t1.delete_backslash();
		_commandlist.FindCommand(*t1, &new_cmd_num);
		if (_new_commands_list[new_cmd_num])
		{
			_new_commands_list[new_cmd_num]->s = t3;
			if (*t2)
				_new_commands_list[new_cmd_num]->params = t2.toInt(); // t2 is a number of params;
			else
				 _new_commands_list[new_cmd_num]->params = 0; // t2 is a number of params;
		}
		
		break;
	}
	return params;
}

/*!
	@brief process \documentclass	
	@return number of parameters of \documentclass
	\documentclass[settings]{style}[date of creation]
*/
int Parser::_document_class(void)
{
	int par = 0;
	if (_get_param_ncom(&_doc_settings.settings)) par++;
	if (_get_param_com(&_doc_settings.style))	par++;
	if (_get_param_ncom(&_doc_settings.date))	par++;
	return par;
}

void Parser::_process_new_command(TokenString s, int params)
{
	if (!*s) 
	{
		_log << "Chyba pri _process_new_commnad" << std::endl ;
		return;
	}
	char _ps[10];
	TokenString p1;
	for (int i=1; i<=params; i++)	// nahradim #i(oznacuje pozici i-teho parametru) skutecnymi parametry prikazu
	{
		sprintf(_ps, "#%d", i);
		_get_param_com(&p1);
		if (*p1)
			s.replace_str(_ps, *p1);
	}
	
	// hodim nove definice do vstupniho streamu
	char *_s = *s;
	for(i=strlen(_s)-1; i>=0; i--)
		_in.putback(_s[i]);
}

/*!
	@brief fill private variable _commandlist
*/
void Parser::_boot_commandlist()
{
	//! basic characters
	_commandlist.AddCommand(" ", space);
	_commandlist.AddCommand("\"", quote);
	_commandlist.AddCommand("#", hash);
	_commandlist.AddCommand("$", dollar);
	_commandlist.AddCommand("%", percent);
	_commandlist.AddCommand("&", amp); 
	_commandlist.AddCommand(",", comma);
	_commandlist.AddCommand(".", dot);
	_commandlist.AddCommand("[", lbracket);
	_commandlist.AddCommand("\\", backslash);
	_commandlist.AddCommand("]", rbracket);
	_commandlist.AddCommand("_", underscore);
	_commandlist.AddCommand("{", lbrace);
	_commandlist.AddCommand("}", rbrace);
	_commandlist.AddCommand("~", tilda);
	_commandlist.AddCommand("(", lparenthesis);
	_commandlist.AddCommand(")", rparenthesis);
	
	_commandlist.AddCommand("documentclass", doc_class_cmd);
	_commandlist.AddCommand("usepackage", usepackage_cmd);
	_commandlist.AddCommand("pagestyle", pagestyle_cmd);
	_commandlist.AddCommand("thispagestyle", thispagestyle_cmd);

	_commandlist.AddCommand("begin", begin_cmd);
	_commandlist.AddCommand("end", end_cmd);
	_commandlist.AddCommand("TeX", tex_cmd);
	_commandlist.AddCommand("LaTeX", latex_cmd);
	_commandlist.AddCommand("LaTeXe", latexe_cmd);
	_commandlist.AddCommand("ldots", ldots_cmd);
	_commandlist.AddCommand("newline", newline_cmd);
	_commandlist.AddCommand("hyphenation",hyphenation_cmd);
	_commandlist.AddCommand("mbox",mbox_cmd);
	_commandlist.AddCommand("today",today_cmd);
	_commandlist.AddCommand("section", section_cmd);
	_commandlist.AddCommand("subsection", subsection_cmd);
	_commandlist.AddCommand("subsubsection", subsubsection_cmd);
	_commandlist.AddCommand("paragraph", paragraph_cmd);
	_commandlist.AddCommand("subparagraph", subparagraph_cmd);
	_commandlist.AddCommand("part", part_cmd);
	_commandlist.AddCommand("chapter", chapter_cmd);
	_commandlist.AddCommand("newtheorem", newtheorem_cmd);
	_commandlist.AddCommand("newcommand", newcommand_cmd);
	_commandlist.AddCommand("renewcommand", renewcommand_cmd);
	_commandlist.AddCommand("title", title_cmd);
	_commandlist.AddCommand("author", author_cmd);

}
/*
 ****************************************************************************
 ************* CLASS      CommandList ***************************************
 ****************************************************************************
 */

/*!
	@brief constructor of commandList class
*/
CommandList::CommandList():_num(0),_max(1024)
{
	_commanditems = new PCommandItem[1024];
}

/*!
	@brief add one command to the list
	@param str_comm string which represents command
	@param comm number which represents command
*/
void CommandList::AddCommand(char *str_comm, int comm)
{
	CommandItem * _pom = new CommandItem;
	_pom->_command = comm;
	_pom->_commandstring = new char[strlen(str_comm)+1];
	strcpy(_pom->_commandstring, str_comm);
	if (_num + 1 == _max )
	{
		CommandItem **_p = new PCommandItem[2*_max];
		memcpy(_p, _commanditems, _max*sizeof(PCommandItem) );
		_max *= 2;
		delete _commanditems;
		_commanditems = _p;
	}
	
	_commanditems[_num++] = _pom;
}

/*!
	@brief find command string in command list
	@param str_comm string which represents command
	@param comm number which represents command
	@return TRUE if string is found else FALSE
*/
bool CommandList::FindCommand(char *str_comm, int *comm)
{
	*comm = err_code;
	for(int i=0; i<_num; i++)
	{
		if (strcmp(str_comm, _commanditems[i]->_commandstring)==0)
		{
			*comm = _commanditems[i]->_command;
			return true;
		}
	}
	return false;
}

/*!
	@brief destructor of CommandList class
*/
CommandList::~CommandList()
{
	for(int i=0; i<_num; i++)
	{
		delete[] (_commanditems[i]->_commandstring);
		delete _commanditems[i];
	}
	delete [] _commanditems;
}