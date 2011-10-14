%aclark

%the perm is from a book that kbg gave ghall; i understand it!

append([], X, X).
append([X|Xs], Ys, [X|Zs]) :- append(Xs, Ys, Zs).

perm(L, [H|T]) :- append(V, [H|U], L),append(V, U, W),perm(W, T). perm([],[]). 

equal(X) :- X=[A,B,C,D,E,F,G,H,I],
	A+B+C=:=D+E+F, A+B+C=:=G+H+I, A+B+C=:=A+D+G, 
	A+D+G=:=B+E+H, A+D+G=:=C+F+I, A+D+G=:=A+E+I,
	A+E+I=:=G+E+C.

do :- perm([1,2,3,4,5,6,7,8,9],X),equal(X),print(X),nl,fail.   


