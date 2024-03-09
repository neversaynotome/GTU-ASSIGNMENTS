:- dynamic(student/3).
:- dynamic(class/3).
:- dynamic(course/4).
:- dynamic(instructor/3).
:- style_check(-singleton).

%student(id, [taken courses], Handicapped).
student(s1, [course1], no).
student(s2, [course2], yes).
student(s3, [course2, course3], no).
student(s4, [course3, course2], yes).
student(s5, [course4, course5], no).
student(s6, [course5, course4], yes).
student(s7, [course3, course5], no).
student(s8, [course3, course4], no).

%instructor(id, [given courses], [preferences]).
instructor(i1, [course1], [projector]).
instructor(i2, [course2], [projector, smart_board]).
instructor(i3, [course3, course5], [projector, smart_board]).
instructor(i4, [course4], [smart_board]).

%course(id, capacity, instructorID, [requirements]).
course(course1, 10, i1, [yes]).
course(course2, 7, i2, [yes, projector]).
course(course3, 10, i3, [projector]).
course(course4, 13, i4, [smart_board, projector]).
course(course5, 22, i4, [smart_board]).

%class(id, capacity, [equipment]).
class(class1, 20, [smart_board, no]).
class(class2, 20, [projector, yes, no]).
class(class3, 10, [projector, smart_board, yes, no]).
class(class4, 40, [projector, no]).

%occupancy(course, class, start).
occupancy(course1, class1, 10).
occupancy(course1, class1, 11).
occupancy(course2, class4, 10).
occupancy(course2, class4, 11).
occupancy(course2, class4, 12).
occupancy(course3, class3, 12).
occupancy(course3, class3, 13).
occupancy(course3, class3, 14).
occupancy(course4, class2, 11).
occupancy(course4, class2, 12).
occupancy(course4, class2, 13).
occupancy(course5, class1, 10).
occupancy(course5, class5, 14).
occupancy(course5, class5, 15).

%adds new student
addStudent(ID, Courses, Requirements):-
    \+student(ID, _, _), 
    assertz(student(ID, Courses, Requirements)).

%adds new class
addClass(ID, Capacity, Equipments):-
    \+class(ID, _, _), 
    assertz(class(ID, Capacity, Equipments)).

%adds new course
addCourse(ID, Capacity, InstructorID, Requirements):-
    \+course(ID, _, _, _), 
    assertz(course(ID, Capacity, InstructorID, Requirements)).

%looks for eligible room for a specific class.
courseNclass(Course, Class):-
    course(Course, C1, _, Requirements), 
    class(Class, C2, Equipments), 
    C1 =< C2,
    subset(Requirements, Equipments).

%checks if enrollment to a specific class is possible
studentNclass(Student, Class):-    
    student(Student, _, Requirements), 
    class(Class, _, Equipments), 
    is_element(Requirements, Equipments).%check if yes

%is there any conflict
checkConflict(Course1, Course2):-
    occupancy(Course1, C1, T1), 
    occupancy(Course2, C2, T2), 
    not(Course1=Course2), 
    C1=C2, (T1=T2).%classes are same so the types

%looks if element is in array
is_element(E, [E|Rest]).
is_element(E, [I|Rest]):-
	is_element(E, Rest).

%if a specific list is subset of another
subset([], B).
subset([E|Rest], B):-		
	isElement(E, B), 
	subset(Rest, B).

%looks if element is in array
isElement(E, S):-
	is_element(E, S).