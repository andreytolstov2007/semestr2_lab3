main: main.o test_modul.o Complex.o String.o Student.o Teacher.o
	g++ main.o test_modul.o Complex.o String.o Student.o Teacher.o -o a

main.o: main.cpp
	g++ main.cpp -c

test_modul.o: test_modul.cpp
	g++ test_modul.cpp -c

Complex.o: Complex.cpp
	g++ Complex.cpp -c

String.o: String.cpp
	g++ String.cpp -c

Student.o: Student.cpp
	g++ Student.cpp -c

Teacher.o: Teacher.cpp
	g++ Teacher.cpp -c