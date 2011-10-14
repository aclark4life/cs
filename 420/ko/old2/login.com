$!
$! This command procedure is a framework for building an individual
$! login command procedure. It is executed every time that you log
$! into your account.
$!
$  IF F$MODE() .NES. "INTERACTIVE" THEN GOTO ENDINTER
$!
$! Put commands that you want executed only on an interactive login
$! between this comment and the "ENDINTER:" symbol.
$!
$!set prompt = "D10:[STD.ACLARK]> "
cd sys$login

$ENDINTER:
$  IF F$MODE() .NES. "BATCH" THEN GOTO ENDBATCH
$!
$! Put commands you want executed only in batch mode between this comment
$! and the "ENDBATCH:" symbol.
$!
$
$ENDBATCH:
$!
$! Put commands that you want executed in any mode of login below.
$!
$!
late == "logout"
ls == "dir"


