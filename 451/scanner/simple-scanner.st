" simple-scanner.st "

Object subclass: #Scanner
       instanceVariableNames: 'string stringIndex lexeme'
       classVariableNames: ''
       poolDictionaries: ''
       category: nil !

" additional methods for other objects used to support scanning"

!Character methodsFor: 'scanning'!

isWhite
    self = Character space ifTrue: [^true].
    self = Character tab   ifTrue: [^true].
    self = Character nl    ifTrue: [^true].
    ^false
!!


!String methodsFor: 'Scanner creation'!

asScanner
    ^Scanner new: self
!!


!String methodsFor: 'scanning'!


skipWhite: startFrom
    [(startFrom <= (self size)) and: [((self at: startFrom) isWhite)]] 
	whileTrue: [ startFrom := startFrom + 1].
    ^startFrom
!

skipNonWhite: startFrom
    [(startFrom > (self size)) or: [(self at: startFrom) isWhite]] 
	whileFalse: [startFrom := startFrom + 1].
    ^startFrom
!

subString: start stopAt: stop
    | len tmp |

    len := stop - start.
    tmp := String new: len.
    1 to: len do: 
	[:i | tmp at: i put: (self at: start + i - 1)].
    ^tmp
!!

" Scanner Class "


!Scanner class  methodsFor: 'instance creation'!

new: string
    ^super new initialize: string
!!


!Scanner methodsFor: 'accessing'!

initialize: str
	string := str.
	stringIndex := 1.
	lexeme := ''.
!

lexeme
	^lexeme
!!


!Scanner methodsFor: 'scanning'!

nextToken
    | end |

    stringIndex := string skipWhite: stringIndex.
    stringIndex >= (string size)
	ifTrue: [ ^-1 ].

    end := string skipNonWhite: stringIndex.
    lexeme := string subString: stringIndex stopAt: end.
    stringIndex := end.
    ^self recognize: lexeme
!

recognize: str
    str = ':=' ifTrue: [ ^#AssignToken ].
    str = '~=' ifTrue: [ ^#NotEqualToken ].
    str = '='  ifTrue: [ ^#EqualToken ].
    str = '<=' ifTrue: [ ^#LessThenOrEqual ].
    str = '+'  ifTrue: [ ^#PlusToken ].
    str = '('  ifTrue: [ ^#LParenToken ].
    str = ')'  ifTrue: [ ^#RParenToken ].
    ^#IdentifierToken
!!
