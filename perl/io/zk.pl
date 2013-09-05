#!/usr/bin/perl 

open SUB,'sub';
@sub=<SUB>;
foreach $radek (@sub)
{
 chop($radek);
 @pom = split(/\t/,$radek);
 push (@sub1,@pom[0]);
 push (@sub2,@pom[1]);
}

#print "Vysledek:\n@sub1";

$n=@sub1;
while($radek=<>)
{
 for($i=0;$i<$n;$i++)
 {
# 	print "@sub1[$i] .... @sub2[$i]\n";
	$radek =~ s/@sub1[$i]/@sub2[$i]/ge;
 }
 print $radek;
}
