 "aclark"
 Scanner subclass: #ReservedWordScanner
	instanceVariableNames: ''
       	classVariableNames: ''
      	poolDictionaries: ''
    	category: nil !

!ReservedWordScanner methodsFor: 'scanning'!

 recognize: str 
     	str = 'if' ifTrue: [ ^#if ].
	str = 'else' ifTrue: [ ^#else ].
     	str = 'fi' ifTrue: [ ^#fi ].
  	str = 'while' ifTrue: [ ^#while ].
    	str = 'do' ifTrue: [ ^#do ].
	str = 'od' ifTrue: [ ^#od ].
	^super recognize: str
!
!



