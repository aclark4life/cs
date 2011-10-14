#!/usr/local/bin/perl

#############################################################################

#Set the default values
$title_at_the_top_of_mail_message="Feedback Form";
$important_vars_in_this_form="name feedback";
@important_vars = split (/ /,$important_vars_in_this_form);
$subject_of_mail_message="Feedback from the Web";
$recipient_of_mail_message = 'bduncan@lattanze.loyola.edu';

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


&mail_form;

&success_message;

#############################################################################

sub mail_form {
    open (MAIL, "|mailx -s \"$subject_of_mail_message\" $recipient_of_mail_message") || die "Can't open mailx\n";

    print MAIL <<EOM;

                          $title_at_the_top_of_mail_message 
-------------------------------------------------------------------------

Name: $FORM{'name'}
	    
E-Mail: $FORM{'email'}

Comments:
$FORM{'feedback'}

--------------------------------------------------------------------------
                         Additional Information

Last URL:	$ENV{'HTTP_REFERER'}
Browser:	$ENV{'HTTP_USER_AGENT'}
HTTP From:	$ENV{'HTTP_FROM'}
Remote host:	$ENV{'REMOTE_HOST'}
Remote IP address:	$ENV{'REMOTE_ADDR'}

EOM

    close(MAIL);
}

############################################################################

sub success_message {
    print "<title>Thank You!</title><center><h1>Thank You!</h1><hr size=5><h2>Thank you for your submission, $FORM{'name'}.<br>Your mail has been sent!</h2><hr size=5></center>";
    exit;
}






