/*!
  @file		l2xvar.h
  @brief	variables for latex parser
  
*/

#ifndef _L2XVAR_H
#define _L2XVAR_H

enum command_types
{
	// characters
	tab		  = '\t',
	newline   = '\n',
	cr		  = 13,
	space	  = ' ',
	
	quote	  = '\"',
	hash      = '#',
	dollar	  = '$',
	percent   = '%',
	amp		  = '&',
	accent1	  = '\'',
	lparenthesis	=	'(', // 40
	rparenthesis	=	')', // 41
	comma	  = ',',
	hyphen    = '-', // 45

	dot		  = '.',
	lbracket  = '[',
	backslash = '\\', // 92
	rbracket  = ']', // 93
	underscore= '_', // 95
	accent2   = '`', // 96
	lbrace    = '{', //123
	rbrace    = '}',
	tilda	  = '~', //127
	
	// commands
	doc_class_cmd,
	usepackage_cmd,
	pagestyle_cmd,
	thispagestyle_cmd,
	begin_cmd,
	end_cmd,
	tex_cmd,
	latex_cmd,
	latexe_cmd,	
	ldots_cmd,
	newline_cmd,
	hyphenation_cmd,
	mbox_cmd,
	today_cmd,
	section_cmd,
	subsection_cmd,
	subsubsection_cmd,
	paragraph_cmd,
	subparagraph_cmd,
	part_cmd,
	chapter_cmd,
	newtheorem_cmd,
	newcommand_cmd,
	renewcommand_cmd,	
	title_cmd,
	author_cmd,

	// error command !
	err_code,

	// last command
	last_cmd
};

#endif