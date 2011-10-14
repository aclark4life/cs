" Simple Scanner Test "
| scanner string token |

string := '+ if := ab'.
'' printNl. 'Simple Scanner test: scanning |' print. string print. '|' printNl.

string class printNl.

scanner := string asScanner.  
"(or, equivalently, 'scanner := Scanner new: string')"

'' printNl.
[token := scanner nextToken. token ~= -1] 
    whileTrue: [token print. ' ' print].

0 to: 1 do: ['' printNl].
!
