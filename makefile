Main.exe		: 	Main.o  transform.o DStarLite.o LPAstar.o gridworld.o graphics.o 
	g++ -o Main.exe Main.o transform.o DStarLite.o LPAstar.o gridworld.o graphics.o -l gdi32 
			
Main.o		:	Main.cpp graphics.h transform.h DStarLite.h LPAstar.h gridworld.h globalvariables.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  Main.cpp
	
transform.o		:	 transform.cpp transform.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  transform.cpp	
	
DStarLite.o	:	 DStarLite.cpp DStarLite.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  DStarLite.cpp

LPAstar.o	:	 LPAstar.cpp LPAstar.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  LPAstar.cpp

gridworld.o	:	 gridworld.cpp gridworld.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  gridworld.cpp

graphics.o		:	 graphics.cpp graphics.h
	g++ -g -c -std=c++11   -fpermissive -fconserve-space -Wno-write-strings  graphics.cpp
	
clean:
	del *.o
	del *.exe
