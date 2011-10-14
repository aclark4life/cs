#!/usr/local/bin/perl
#############################################################################

This perl script was given to me by Bruce Duncan, who acquired it from an 
unknown source. I have made several modifications as indicated.

This script is called by bootp.html, or rather a web browser that is viewing bootp.html.
When viewed through Netscape, or a similar browser, bootp.html takes user input. Four
variables are inputed from the browser to this shell script. They are:  name, tc, ha, ip. 
These are fields in the bootp table. The variables are then appended to the bootp table in 
accordance with existing style.


$important_vars_in_this_form="name tc ha ip";                   ###  modified by aclark
							   	###  12/96
								###  I changed these variables.
@important_vars = split (/ /,$important_vars_in_this_form);

##############################################################################

#Print this to the browser to let it know what's coming
print "Content-type: text/html\n\n";

#read in the form
read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

#split them up into an array
@pairs = split(/&/, $buffer);

#for each set of name and value pairs
foreach $pair (@pairs)
{    ($name, $value) = split(/=/, $pair);

     # Un-Webify plus signs and %-encoding
     $value =~ tr/+/ /;
     $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;

     #uncomment for debug
     # print "Setting $name to $value<p>";

     # check to see if any of the inportant variables are empty
     if ((length $value)==0) {
         foreach $var (@important_vars) {
             if ($name eq $var) {
        print "<title>Error!</title><h1>Error!</h1><h2>Please fill in the $name field!</h2>\n";
        exit;
    }
         }
     }

    $FORM{$name} = $value;
}


open(IN,"+</usr/users/aclark/bootp/bootptab");      		###  modified by aclark
								###  12/96
								###  This file is the 	
								###  bootp table,
								###  where the entries
								###  are appended.
$line=<IN>;
while((!($line eq "# WebAdditions")) && (!(eof(IN))))
{
	$line=<IN>;
}

print IN "$FORM{'name'}:\t\ttc=$FORM{'tc'}:\tha=$FORM{'ha'}:\tip=$FORM{'ip'}\n";

close IN;

print <<EOM;
	 	
<html> 								###  modified by aclark
<table height=60% width=100%>					###  12/96
<td align=center> <h1>$FORM{'name'}</h1> </td>   		###  This section of HTML
								###  code informs the user
								###  that an entry has been
								###  made.
<tr>
<td align=center> <h1>added!</h1> </td>
</table>
</html>

EOM
exit;

