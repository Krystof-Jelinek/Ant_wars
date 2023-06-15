all: CTile.o main.o CMap.o CNest.o CAnt.o CExplodingAnt.o CFlyingAnt.o CCoordinates.o CRoad.o CGame.o CInterface.o
	g++ -Wall -pedantic -g main.o CTile.o CNest.o CMap.o CAnt.o CExplodingAnt.o CFlyingAnt.o CCoordinates.o CRoad.o CGame.o CInterface.o -o a.out

main.o: main.cpp
	g++ -Wall -pedantic -g -c main.cpp

CTile.o: CTile.cpp CTile.h
	g++ -Wall -pedantic -g -c CTile.cpp

CMap.o: CMap.cpp CMap.h
	g++ -Wall -pedantic -g -c CMap.cpp	

CNest.o: CNest.cpp CNest.h
	g++ -Wall -pedantic -g -c CNest.cpp	

CAnt.o: CAnt.cpp CAnt.h
	g++ -Wall -pedantic -g -c CAnt.cpp	

CExplodingAnt.o: CExplodingAnt.cpp CExplodingAnt.h
	g++ -Wall -pedantic -g -c CExplodingAnt.cpp

CFlyingAnt.o: CFlyingAnt.cpp CFlyingAnt.h
	g++ -Wall -pedantic -g -c CFlyingAnt.cpp			

CCoordinates.o: CCoordinates.cpp CCoordinates.h
	g++ -Wall -pedantic -g -c CCoordinates.cpp

CRoad.o: CRoad.cpp CRoad.h
	g++ -Wall -pedantic -g -c CRoad.cpp

CGame.o: CGame.cpp CGame.h
	g++ -Wall -pedantic -g -c CGame.cpp

CInterface.o: CInterface.cpp CInterface.h
	g++ -Wall -pedantic -g -c CInterface.cpp

clear:
	rm *.o