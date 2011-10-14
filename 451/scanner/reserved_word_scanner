" Reserved Word Scanner Test "
| scanner string token |

string := '
while x ~= 0 do 
    if y <= 8
	y := y + 1
    fi
od'.

'Simple Scanner test: scanning |' print. string print. '|' printNl.
scanner := string asScanner.  
"(or, equivalently, 'scanner := Scanner new: string')"
[token := scanner nextToken. token ~= -1] 
    whileTrue: [token print. ' ' print].

0 to: 1 do: ['' printNl].

'Reserved Word Scanner test: scanning |' print. string print. '|' printNl.
scanner := ReservedWordScanner new: string.
[token := scanner nextToken. token ~= -1] 
    whileTrue: [token print. ' ' print].

0 to: 1 do: ['' printNl].

'Reserved Word Scanner test2: scanning |' print. string print. '|' printNl.
scanner := ReservedWordScanner new: string.
[token := scanner nextToken. token ~= -1] 
    whileTrue: [(scanner recognize2: scanner lexeme) print. ' ' print].

0 to: 1 do: ['' printNl].

(scanner isint: '123' ) printNl.
(scanner isint: '1a3' ) printNl.

!

