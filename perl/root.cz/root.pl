#!/usr/bin/perl -w
@sms_mails	= ("00420721671092\@sms.eurotel.cz");
$max_smslen	=	766;			# SMS length = 150 znaku
#----------------------------------------------------------------------------------------
$zpravy = 0 ;					# znaci, ze jsem v oddilu zprav
$in	= 0;					# znaci, ze jsem uprostred nejake zpravy
$msg	= "";					# text valstni zpravy
$datum 	= "";					# datum zverejneni zpravy
$saved_datum = "nic";
$down_file = "index.html";			# nazev downloadovaneho file
@last_day = (0,0,0);
@last_time = (0,0);
#----------------------------------------------------------------------------------------

$start_of_msg = "CLASS=\"ro-mb\"";		# zacatek sekce se zpravami
@msg_array = ();				# pole novych zprav
$last_msg = "last.msg";				# file s datem posledni zpravy
$file_msg = "msgs.msg";				# zaznam vsech zprav

#-----------------------------------------------------------------------------
sub is_new;
sub download;
sub send_mails;	
#-----------------------------------------------------------------------------

download();				# downloading www.root.cz

# zjistim si aktualni rok :-)
@a    = gmtime(time);
$year = $a[5];
$year += 1900;


# zjistim si datum posledni odeslane zpravy
if (open FILE,  $last_msg )
{
 @file=<FILE>;
 foreach $line (@file)
 {
    if ( $line=~/^DATE:(.*)/ )
    {
	@last_day = split (/\./, $1);
	#print @last_day;
    }
    
    if ( $line=~/^TIME:(.*)/ )
    {
	@last_time = split (/:/, $1);
	#print @last_time;
    }
 } 
 close FILE ;
}

open FILE,"$down_file";
@file=<FILE> ;

foreach $line (@file)
{
    if ( $line =~ /$start_of_msg/ ) 
    {
	$zpravy = 1 ;
    } 
    if ($zpravy && $line =~/<\/DIV>/)
    {
     $zpravy = 0;
    }
    
    if ( $zpravy )
    {
	if ($line =~ /^<LI>/)
	{
	    $in = 1;
	    $msg= '';
	}
	
	if ($in)
	{
	    #chop $line;
	    if ($line =~ /<EM>(.*)<\/EM>/)
	    {
		$datum = $1;	# zde si nastavim datum zpravy
	    }
	    $msg = $msg.$line;
	}
	
	if ($line =~ /<\/LI>$/)
	{
	    $in = 0;
	    $msg =~ s/<[^>]*>//g ;		# odtaguju
						# odstranim cestinu
	    $msg =~ tr/áèïéìíòóø¹»úùý¾ÁÈÏÉÌÍÒÓØ©«ÚÙÝ®/acdeeinorstuuyzACDEEINORSTUUYZ/ ;
	    $msg =~ s/\"//g;	    
	    $msg =~ s/\'//g;	    
	    if ( is_new() )
	    {
		if ($saved_datum =~ /nic/ )
		{
		    $saved_datum = $datum;
		}
	        #print "Je novy: $datum";
		push @msg_array, $msg;		# zde si ulozim vsechny novejsi zpravy, nez $last_date.
	    }
	}
    }
}
close FILE;

if (@msg_array)
{
 my $d='';
 my $t='';
 if ($saved_datum =~/([^\.]*\.[^\.]*\.) ([^:]*:.*)/)
 {
    $d=$1; $t=$2;
 }
 
 $d.=" ".$year;
 open FILE, ">$last_msg";
 print FILE "DATE: $d\nTIME: $t\n";
 close FILE;
 
 open FILE, ">>$file_msg";
 #`echo "@msg_array" | mail mmalohlava\@seznam.cz`;
 #`echo "@msg_array" | mail "00420721671092\@sms.eurotel.cz"`;
 #`smssend eurotel2 721 671092 sms "@msg_array" >log`;
 while( $msg = pop(@msg_array) )
 {
    print FILE "$msg\n";
    send_mails($msg);
 }
 close FILE;
}

sub is_new
{
    if ($datum =~ /([^\.]*)\. ([^\.]*)\. ([^:]*):(\d*)/ )
    {
	$day 	= $1;
	$month 	= $2;
	$hour	= $3;
	$minute = $4;
	#print $day.".".$month."-".$hour.":".$minute."\n";
    }
    else
    {
	return 0;
    }
    
    if ($last_day[2]>$year)
    {
    	return 0;
    } else 
    {
	if ($last_day[2]<$year) 
	{ return 1; } 
	else
	{
    	    if ($last_day[1]>$month)
    	    { return 0; }
	    else 
	    { 
	     if ($last_day[1]<$month) { return 1; } 
	     else
    	    {
    		if ($last_day[0]>$day)
    		{   return 0; }
    		else 
		{ if ($last_day[0]<$day) { return 1; } 
		else
    		{
    		    if ($last_time[0]>$hour)
    		    {  	return 0; }
    		    else 
		    {
			if ($last_time[0]<$hour) { return 1; } 
			else
    			{
    			    if ($last_time[1]>$minute)    { 	 return 0; }
    			    else 
			    { 
				if ($last_time[1]<$minute) { return 1; }
				else
				{
				    return 0;
				}
   }
  }
 }
 }
 }
 }
 }
 }
}
}

sub download
{
    my $a = `wget -q http://www.root.cz -O $down_file`
}

sub send_mails
{
    my $mesg = shift(@_);
    my $len  = length($mesg);
    my $poc  = 0;
    foreach $sms_addres (@sms_mails)
    {
	print "MAIL: $sms_addres\n";
	while($poc<$len)    
	{
	    my $sms = substr($mesg, $poc, $max_smslen);
	    print "$sms\n-----------\n";	    
#	    `echo "$sms" | mail "$sms_addres"`;
	    `smssend eurotel2 721 671092 sms "$sms" >log`;
	    $poc += $max_smslen;
	}
	print "________________________\n";
    
    }
}