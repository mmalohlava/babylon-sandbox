#!/usr/bin/perl -w 
################
# LaTeX 2 XML ##
################

# basic definitions
    $file 	= "basic.subst";			# nazev souboru se substitucemi
    @left 	= ();					# leve
    @right	= ();					# prave strany substituci
    %theorems	= ();					# asociativni pole pro seznam theoremu
    %newcommands 	= ();				# asociativni pole pro seznam newcommand
    %newenvironments	= ();				# asociativni pole vsech newenvironments: name, polozka (before, after)

    $open_part	= 0; 					# jsme v casti textu \part
    $num_part	= 0;					# cislo aktualni \part
    $open_chapter =0;					# znaci, ze jsme v \chapter
    $num_chapter  =0;					# aktualni cislo \chapter
    $open_section =0;    				# znaci, ze jsme v \section
    $num_section  =0;					# pocet \section
    $open_subsection =0;    				# znaci, ze jsme v \subsection
    $num_subsection  =0;				# pocet \subsection
    $open_subsubsection =0;    				# znaci, ze jsme v \subsubsection
    $num_subsubsection  =0;				# pocet \subsubsection
    $open_paragraph	= 0;				# znaci jestli jsme uprostred nejakeho paragrafu
    $num_paragraph	= 0;				# cislo paragrafu
    $open_subparagraph	= 0;				# znaci jestli jsme uprostred nejakeho \subparagraph
    $num_subparagraph	= 0;				# cislo paragrafu
    
    $open_math		= 0;				# znaci, ze jsem v $...$ ,nebo podobnem prostredi..    
# end of basic definitions

# DEBUG definition
$DEBUG=1;
# end of DEBUG definition
#------------------------------------------

# function definitions
 sub load_sub;						# nacte substituce do @left, @right
 sub app_sub;						# provede substituce na dany parametr = radka
 sub proces_math;    					# prevede LaTeX na MathMl
 sub add_theorem;					# prida novy theorem do seznamu theoremu
 sub add_newcommand;					# prida novy command do seznamu newcommand
 sub add_newenvironment;
 sub detect_part;					# detekuje \part - uzavre vsechny ostatni vnitrni tagy nize.
 sub detect_chapter;					# dtto \chapter 
 sub detect_section;					# dtto \section
 sub detect_subsection;					# dtto \subsection
 sub detect_subsubsection;				# dtto \subsubsection
 sub detect_paragraph;					# dtto \paragraph
 sub detect_subparagraph;				# dtto \subparagraph 
 sub detect_open_text;					# vraci retezec s uzavirajicimi tagy
# end of function definitions

#---------------------------MAIN------------------------

    load_sub($file);					# nacte substituce do @left, @right

    # DEBUG
    if ($DEBUG)
    {
	print "Pocet substituci: $#right, $#left\nSubstituce:\n";
	for($i=0; $i<=$#left; ++$i)
	{
	#    print "$left[$i]\t<---->\t$right[$i]\n";
	}
    } 
    # end of DEBUG
        
    while ($line=<>)						# hlavni smycka
    {
     ###-----------DULEZITE----------------------------------------------------

     # odstraneni komentaru
     if ($line =~ /^%.*/)					# je to komentar
     {    next; }
     $line =~ s/([^%]*)[^\\]%.*$/$1/;
     # konec odstraneni komentaru
     
     # odstraneni \$ ---> 
     $line =~ s/\\\$/&doll/g ;
     # end of odstraneni \$
     
     ###------END-OF-DULEZITE---------------------------------------------------
     # nahradim NEWENVIRONMENT
     foreach $name (keys %newenvironments)
     {
             (my $before, my $after ) = split( /\e/, $newenvironments{$name} );
	     $line =~ s/\\begin\{$name\}/$before/g ;
	     $line =~ s/\\end{$name}/$after/g ;
     }
     # end of NEWENVIRONMENT
     
     # nahradim NEWCOMMAND
     foreach $name (keys %newcommands )
     {
        $line =~ s!$name(\s)!$newcommands{$name}$1!g ;     
     } 
     # end of NEWCOMMAND

     
     # zapisu newcommand
     if ( $line =~ /\\newcommand\{([^\}]*)\}\{(.*)\}/ )		# prvni je nazev, druhy je popis
     {								# pozor!!!!, na to kdyz ma command vice parametru
        add_newcommand($1, $2);
	$line =~ s/(\\newcommand\{[^\}]*\}\{.*\})/<\!-- zde byl $1 -->/;
     }
     # end of newcommand
     
     # zapisu si newenvironment
     if ($line =~ /\\newenvironment\{([^\}]*)\}\{(.*)\}\{(.*)\}/ )
     {
        add_newenvironment($1,$2,$3);
	$line =~ s/(\\newenvironment\{[^\}]*\}\{.*\}\{.*\})/<\!-- zde byl $1 -->/;
	# print " nazev = $1 \t pred = $2 \t po = $3"	;
     }
     # end of newenvironment
     
     # zapisu si pouzite theoremy
     # mozna lepe while $line =~ ..., kdyby nekdo psal vice \newtheorem na jeden radek
     if ($line =~ /\\newtheorem\{([^\}]*)\}\{([^\}]*)\}/)
     {
        add_theorem($1, $2);
	$line =~ s/(\\newtheorem\{[^\}]*\}\{[^\}]*\})/<\!-- zde byl $1 -->/;
     }
     # end of theorem
     
     
     # zataguji podstatne casti textu
     $line = detect_subparagraph($line);
     $line = detect_paragraph($line);
     $line = detect_subsubsection($line);
     $line = detect_subsection($line);
     $line = detect_section($line);
     $line = detect_chapter($line);
     $line = detect_part($line); 
     if ( $line =~ /\\end\{document\}/ ) # muze byt jen jeden \end{document}
     {
        $temp = detect_open_text(7);
	$temp = $temp."\n</document>";
	$line =~ s/\\end\{document\}/$temp/;
     }
     # end of tagging :=)
     
          
     # matematika 
     #(jednoradkova )
     $line =~ s/\$\$([^\$]*)\$\$/"<math>".proces_math($1)."<\/math>" /eg;
     $line =~ s/\$([^\$]+)\$/"<math>".proces_math($1)."<\/math>" /eg;
     $line =~ s/\\\((.*?)\\\)/ "<math>".proces_math($1)."<\/math>" /eg;
     $line =~ s/\\\[(.*?)\\\]/ "<math>".proces_math($1)."<\/math>"; /eg;
     # viceradkova
     if ($open_math) 
     {
	if (($line =~ s/^([^\$]*)\$\$/proces_math($1)."<\/math>" /e) ||
	    ($line =~ s/^([^\$]*)\$/proces_math($1)."<\/math>"/e) ||
	    ($line =~ s/^(.*)\\\)/proces_math($1)."<\/math>"/e) || # pomoci vyse si odstranim \[ ...\] \[ --> MATEMATIKA \[
	    ($line =~ s/^(.*)\\\]/proces_math($1)."<\/math>"/e) 
	   )    
	    {
	     $open_math = 0;
	    }
	else
	{
	    $line = proces_math($1);
	}
     } else
     { 
        if (($line =~ s/\$\$(.*)$/"<math>".proces_math($1);/e) ||
	    ($line =~ s/\$(.*)$/"<math>".proces_math($1);/e) ||
	    ($line =~ s/\\\((.*)$/"<math>".proces_math($1);/e) ||
	    ($line =~ s/\\\[(.*)$/"<math>".proces_math($1);/e) 
	   )    
	   {
	    $open_math = 1;	   
	   }
     }
     # end of matematika
     if ($DEBUG)
     {
      if ($line =~ /^q/)
      {
       print "\n--------------KONEC-----------\n\n";
       last;
      }
     }     
     
     # odstraneni zbytku 
     $line = app_sub($line);
     print "$line";         
    }							# end of hlavni smycka

#------------------------end-of-MAIN--------------------

# funkce pro nacteni substituci ze souboru
# parametr urcuje soubor k nahrani, naplni seznamy @left, @right
sub load_sub 
{
    my $f = pop( @_ );

    open(F,"$f");
    while (my $line=<F>) 
    {
	chomp $line;
	(my $a, my $b) = split /\t/,$line;
	push(@left, $a);
	push(@right, $b);
    }
    close(F);
    return 1;
}

# funkce pro aplikovani substituci ulozenych v polich @left,@right
# IN: na parametr fce, 
# OUT: vraci takto upraveny radek
sub app_sub
{
    my $line = pop( @_ );
    
    for(my $i=0; $i<=$#left; $i++)
    {
     $line =~ s!$left[$i]!$right[$i]!g;
    }
    # dalsi substituce
    $line =~ s/\\author\{(.*)\}/<author>$1<\/author>/ ;
    $line =~ s/\\title\{(.*)\}/<title>$1<\/title>/ ;
    $line =~ s/\\label\{(.*)\}/<label>$1<\/label>/ ;
    
    #substituce theoremu
    if ( $line =~ /\\begin\{([^\}]*)\}/ )
    {
	if ( $theorems{$1} )
	{
	    $line =~ s/\\begin\{([^\}]*)\}/<theorem name=\"$theorems{$1}\">/;
	}
    }
    
    if ( $line =~ /\\end\{([^\}]*)\}/ )
    {
	if ( $theorems{$1} )
	{
	    $line =~ s/\\end\{([^\}]*)\}/<\/theorem>/;
	}
    }
    # end of substituce theoremu

    $line;
}
# fce. zpracuje LaTeXovou matematiku na MathML
# IN: retezec ke zpracovani
# OUT: zpracovany retezec
sub proces_math
{
    my $line = pop ( @_);
    $line = "MATEMATIKA";
}
# prida novy theorem do seznamu theoremu
# IN: nazev, popis
# OUT: 
sub add_theorem
{
    (my $a, my $b) = @_;
    $theorems{$a} = $b;    
    #print $theorems{$a}."\n";
}

# prida novy newcommand do seznamu newcommand !!!neresi vice parametru
# IN: nazev, popis
# OUT: 
sub add_newcommand
{
    (my $a, my $b) = @_;
    $a =~ s/^\\(.*)/\\\\$1/ ;
    
    $newcommands{$a} = $b;    
}

# prida novy newenvironment do seznamu newenvironment !!!neresi vice parametru
# IN: nazev, pred, po
# OUT: 
sub add_newenvironment
{
    (my $name, my $before, my $after) = @_;
    $newenvironments{$name} = $before."\e".$after;    
    #print $theorems{$a}."\n";
}


############################################################################################################
#   FCE pro detekci casti textu										
#   IN: text	
#   OUT: upraveny tex, nastavi se globalni promenne podle toho, kde jsme
############################################################################################################
sub detect_part					# detekuje \part - uzavre vsechny ostatni vnitrni tagy nize.
{
     my $line = pop ( @_ );
     while ($line =~ /\\part\{([^\}]*)\}/)
     {
        ++$num_part;
	my $temp = detect_open_text(6);
        if ($open_part)
	{
	 $temp = $temp."</part>";
	}
	$line=~ s/\\part\{([^\}]*)\}/$temp\n<part title=\"$1\" num=\"$num_part\">/;
	$open_part = 1;
     }
     while ($line =~ /\\part\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(6);
        if ($open_part)
	{
	 $temp = $temp."</part>";
	}
	$line=~ s/\\part\{([^\}]*)\}/$temp\n<part title=\"$1\">/;
	$open_part = 1;
     }
     $line;
}
 
sub detect_chapter					# dtto \chapter 
{
    my $line = pop ( @_ );

     while ($line =~ /\\chapter\{([^\}]*)\}/)
     {
        ++$num_chapter;
	my $temp = detect_open_text(5);
        if ($open_chapter)
	{
	 $temp = $temp."</chapter>";
	}
	$line=~ s/\\chapter\{([^\}]*)\}/$temp\n<chapter title=\"$1\" num=\"$num_chapter\">/;
	$open_chapter = 1;
     }
     while ($line =~ /\\chapter\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(5);
        if ($open_chapter)
	{
	 $temp = $temp."</chapter>";
	}
	$line=~ s/\\chapter\{([^\}]*)\}/$temp\n<chapter title=\"$1\">/;
	$open_chapter = 1;
     }
    
    $line;
}
sub detect_section					# dtto \section
{
    my $line = pop ( @_ );

     while ($line =~ /\\section\{([^\}]*)\}/)
     {
        ++$num_section;
	my $temp = detect_open_text(4);
        if ($open_section)
	{
	 $temp = $temp."</section>";
	}
	$line=~ s/\\section\{([^\}]*)\}/$temp\n<section title=\"$1\" num=\"$num_section\">/;
	$open_section = 1;
     }
     while ($line =~ /\\section\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(4);
        if ($open_section)
	{
	 $temp = $temp."</section>";
	}
	$line=~ s/\\section\{([^\}]*)\}/$temp\n<section title=\"$1\">/;
	$open_section = 1;
     }
    $line;
}

sub detect_subsection					# dtto \subsection
{
    my $line = pop ( @_ );

     while ($line =~ /\\subsection\{([^\}]*)\}/)
     {
        ++$num_subsection;
	my $temp = detect_open_text(3);
        if ($open_subsection)
	{
	 $temp = $temp."</subsection>";
	}
	$line=~ s/\\subsection\{([^\}]*)\}/$temp\n<subsection title=\"$1\" num=\"$num_subsection\">/;
	$open_subsection = 1;
     }
     while ($line =~ /\\subsection\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(3);
        if ($open_subsection)
	{
	 $temp = $temp."</subsection>";
	}
	$line=~ s/\\subsection\{([^\}]*)\}/$temp\n<subsection title=\"$1\">/;
	$open_subsection = 1;
     }
    $line;
}

sub detect_subsubsection				# dtto \subsubsection
{
    my $line = pop ( @_ );

     while ($line =~ /\\subsubsection\{([^\}]*)\}/)
     {
        ++$num_subsubsection;
	my $temp = detect_open_text(2);
        if ($open_subsubsection)
	{
	 $temp = $temp."</subsubsection>";
	}
	$line=~ s/\\subsubsection\{([^\}]*)\}/$temp\n<subsubsection title=\"$1\" num=\"$num_subsubsection\">/;
	$open_subsubsection = 1;
     }
     while ($line =~ /\\subsubsection\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(2);
        if ($open_subsubsection)
	{
	 $temp = $temp."</subsubsection>";
	}
	$line=~ s/\\subsubsection\{([^\}]*)\}/$temp\n<subsubsection title=\"$1\">/;
	$open_subsubsection = 1;
     }
    $line;
}
sub detect_paragraph					# dtto \paragraph
{
    my $line = pop ( @_ );

     while ($line =~ /\\paragraph\{([^\}]*)\}/)
     {
        ++$num_paragraph;
	my $temp = detect_open_text(1);
        if ($open_paragraph)
	{
	 $temp = $temp."</paragraph>";
	}
	$line=~ s/\\paragraph\{([^\}]*)\}/$temp\n<paragraph title=\"$1\" num=\"$num_paragraph\">/;
	$open_paragraph = 1;
     }
     while ($line =~ /\\paragraph\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(1);
        if ($open_paragraph)
	{
	 $temp = $temp."</paragraph>";
	}
	$line=~ s/\\paragraph\{([^\}]*)\}/$temp\n<paragraph title=\"$1\">/;
	$open_paragraph = 1;
     }
    $line;
}

sub detect_subparagraph				# dtto \subparagraph 
{
     my $line = pop ( @_ );
     while ($line =~ /\\subparagraph\{([^\}]*)\}/)
     {
        ++$num_subparagraph;
	my $temp = detect_open_text(0);
        if ($open_subparagraph)
	{
	 $temp = $temp."</subparagraph>";
	}
	$line=~ s/\\subparagraph\{([^\}]*)\}/$temp\n<subparagraph title=\"$1\" num=\"$num_subparagraph\">/;
	$open_subparagraph = 1;
     }
     while ($line =~ /\\subparagraph\*\{([^\}]*)\}/)
     {
	$temp = detect_open_text(1);
        if ($open_subparagraph)
	{
	 $temp = $temp."</subparagraph>";
	}
	$line=~ s/\\subparagraph\{([^\}]*)\}/$temp\n<subparagraph title=\"$1\">/;
	$open_subparagraph = 1;
     }
     $line;
}
# IN: cislo, ktere znaci , ktere vsechny tagy se maji uzavrit: 1=subpara, 2=subpara,para, 3=subp,para, subsub...
# OUT: retezec s otevrenymi tagy, uzavre vsechny otevrene tagy
sub detect_open_text					# vraci retezec s uzavirajicimi tagy
{
    my $temp="";
    my $num = pop (@_);
    if ($open_subparagraph && $num>=1) 
	{ $temp = $temp."</subparagraph>"; $open_subparagraph = 0; $num_subparagraph=0; }
    if ($open_paragraph && $num>=2) 
	{ $temp = $temp."</paragraph>"; $open_paragraph = 0; $num_paragraph = 0; }
    if ($open_subsubsection && $num>=3)
	{ $temp = $temp."</subsubsection>"; $open_subsubsection = 0; $num_subsubsection=0;}
    if ($open_subsection && $num>=4)
	{ $temp = $temp."</subsection>"; $open_subsection = 0; $num_subsection = 0;}
    if ($open_section && $num>=5)
	{ $temp = $temp."</section>"; $open_section = 0; $num_section = 0;}
    if ($open_chapter && $num>=6)
	{ $temp = $temp."</chapter>"; $open_chapter = 0; $num_chapter = 0;}
    if ($open_part && $num>=7)
	{ $temp = $temp."</part>"; $open_part = 0; $num_part = 0;}
    $temp;
}