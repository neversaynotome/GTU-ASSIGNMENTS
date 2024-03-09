% knowledge base
:- style_check(-singleton).
connection(canakkale, erzincan, 6).
connection(erzincan, antalya, 3).
connection(antalya, izmir, 2).
connection(izmir, istanbul, 2).
connection(antalya, diyarbakir, 4).
connection(diyarbakir, ankara, 8).
connection(izmir, ankara, 6).
connection(ankara, istanbul, 1).
connection(istanbul, rize, 4).
connection(ankara, rize, 5).
connection(ankara, van, 4).
connection(van, gaziantep, 3).
connection(van, istanbul, 8).%first extra
connection(antalya, istanbul, 6).%second extra

connection(erzincan, canakkale, 6).
connection(antalya, erzincan, 3).
connection(izmir, antalya, 2).
connection(istanbul, izmir, 2).
connection(diyarbakir, antalya, 4).
connection(ankara, diyarbakir, 8).
connection(ankara, izmir, 6).
connection(istanbul, ankara, 1).
connection(rize, istanbul, 4).
connection(rize, ankara, 5).
connection(van, ankara, 4).
connection(gaziantep, van, 3).
connection(istanbul, van, 8).
connection(istanbul, antalya, 6).

%------ RULES -------
% Symmetry
validate(X, Y, Z) :- connection(X, Y, Z).

route(X, Y, Weight):-
        check(X, Y, [Y|Rest], Weight).

check(X, Y, Routes, Weight) :- 
        search(X, Y, [X], Routes, Weight).

search(X, Y, P, [Y|P], Weight) :- 
        validate(X, Y, Weight).

search(X, Y, Routes, A, Weight) :-
    validate(X, Z, Weight1), 
    not(Z == X), not(Z == Y), 
    not(isElement(Z, Routes)),
    search(Z, Y, [Z|Routes], A, Weight2), 
    Weight is Weight1+Weight2.

%To check whether an element is isElement array
isElement(E, [E|Rest]).
isElement(E, [I|Rest]):- isElement(E, Rest).