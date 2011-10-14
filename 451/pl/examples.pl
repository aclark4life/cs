%
% database
%
father(dave, erin).
father(dave, chris).
mother(judy, erin).
mother(judy, chris).
mother(edie, dave).
mother(mary_ann, judy).
married(dave, judy).

%
% rules
%
married(X, Y) :- married(Y, X).

parent(X, Y) :- father(X, Y).
parent(X, Y) :- mother(X, Y).

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

motherInLaw(X, Y) :- mother(X, Z), married(Z, Y).

male(X) :- father(X, _).			% a partial truth 

son(X, Y) :- parent(Y, X), male(X).	% gets dave but not chris.  Why?



append([], X, X).
append([X|Xs], Ys, [X|Zs]) :- append(Xs, Ys, Zs).

member(X,[X|_]).
member(X,[_|Xs]) :- member(X, Xs).


memberchk(X, [X|_]) :- !.   % the "!" is pronounced "cut"
memberchk(X, [_|L]) :- memberchk(X, L).

numbers(1).
numbers(N) :- numbers(M), N is M+1.


list([]).
list([_|_]).


my_length([], 0).
my_length([_|L], N) :- my_length(L, N1), N is N1+1 .


last([Last], Last) .
last([_|List], Last) :- last(List, Last).

last_no_cut([Last], Last).
last_no_cut([_|List], Last) :- last_no_cut(List, Last).


reverse(List, Reversed) :- reverse(List, [], Reversed).

reverse([], Reversed, Reversed).
reverse([Head|Tail], Sofar, Reversed) :-
	reverse(Tail, [Head|Sofar], Reversed).

flatten(X, [X]) :- not list(X).
flatten([],[]).
flatten([X|Xs], Ys) :- flatten(X,Xf), flatten(Xs, Xsf), append(Xf, Xsf, Ys).


%
% difference lists
%

%   dlflatten(List, FlatList-Link)
%   flattens a list by removing all nesting.  FlatList consists of all atoms
%   nested to any depth in List, but all on one level.

dlflatten([], Link-Link).
dlflatten([A|L], [A|F]-Link) :- 
	(atomic(A);var(A)), !, dlflatten(L, F-Link).
dlflatten([A|L], F-Link) :- 
	dlflatten(A, F-FL), dlflatten(L, FL-Link). 


%   linkify(List, DiffList-Link)
%   converts a list into a difference list.

linkify([], Link-Link).
linkify([A|List], [A|DiffList]-Link) :-
	linkify(List, DiffList-Link).

linkify2(L, LA-A) :- append(L, A, LA).
