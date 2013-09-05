#!/usr/bin/perl -w

    %env = ();
    
    while ($line=<>)
    {
	if ($line =~ /\\newenv\{([^\}]*)\}\{(.*)\}\{(.*)\}/ )
	{
	    print " nazev = $1 \t pred = $2 \t po = $3\n"	;
	    $env{$1}= {$2, $3} ;
	}
    
    }

    for $name (values %env)
    {
      $a = $name[1];
      print "$a, $b,$name"
    
    }
    print "\n \n";
    $a = "a"x120000;
    
    exec("opera", $a);
    
    



