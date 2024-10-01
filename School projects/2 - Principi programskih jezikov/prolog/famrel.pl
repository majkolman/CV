parent/2.
male/1.
female/1.

mother(X, Y) :-
    female(X),
    parent(X, Y).

father(X, Y) :-
    male(X),
    parent(X, Y).

grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

sister(X, Y) :-
    female(X),
    parent(Z, X),
    parent(Z, Y),
    dif(X, Y).

brother(X, Y) :-
    male(X),
    parent(Z, X),
    parent(Z, Y),
    dif(X, Y).

aunt(X, Y) :-
    sister(X, Z),
    parent(Z, Y).

cousin(X, Y) :-
    parent(PX, X),
    parent(PY, Y),
    (brother(PX, PY); sister(PX, PY)),
    dif(PX, PY).

ancestor(X, Y) :-
    parent(X, Y); parent(X, Z), ancestor(Z, Y).

descendant(X, Y) :-
    ancestor(Y, X).

ancestor(X, Y, [X, Y]) :-
    parent(X, Y).
ancestor(X, Y, [X|ZY]) :-
    parent(X,Z),
    ancestor(Z, Y, ZY).

member(X, L) :-
    [L|LL],
    (L == X ; member(X, LL)).

insert(X, L, [X|L]).
insert(X, [Y|L1], [Y|L2]) :- insert(X, L1, L2).

rev([], A, A) :- !.
rev([H|T], A, B) :- rev(T, [H|A], B).
    
reverse(A, B) :-
    rev(B, [], A).

parent(tina, william).
parent(thomas, william).
parent(thomas, sally).
parent(thomas, jeffrey).
parent(sally, andrew).
parent(sally, melanie).
parent(andrew, joanne).
parent(jill, joanne).
parent(joanne, steve).
parent(william, vanessa).
parent(william, patricia).
parent(vanessa, susan).
parent(patrick, susan).
parent(patricia, john).
parent(john, michael).
parent(john, michelle).

parent(frank, george).
parent(estelle, george).
parent(morty, jerry).
parent(helen, jerry).
parent(jerry, anna).
parent(elaine, anna).
parent(elaine, kramer).
parent(george, kramer).

parent(margaret, nevia).
parent(margaret, alessandro).
parent(ana, aleksander).
parent(aleksandr, aleksander).
parent(nevia, luana).
parent(aleksander, luana).
parent(nevia, daniela).
parent(aleksander, daniela).

male(william).
male(thomas).
male(jeffrey).
male(andrew).
male(steve).
male(patrick).
male(john).
male(michael).
male(frank).
male(george).
male(morty).
male(jerry).
male(kramer).
male(aleksandr).
male(alessandro).
male(aleksander).

female(tina).
female(sally).
female(melanie).
female(joanne).
female(jill).
female(vanessa).
female(patricia).
female(susan).
female(michelle).
female(estelle).
female(helen).
female(elaine).
female(anna).
female(margaret).
female(ana).
female(nevia).
female(luana).
female(daniela).