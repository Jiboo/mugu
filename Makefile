# Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
# http://creativecommons.org/licenses/by/3.0/

CXX=g++-svn
CXXFLAGS=-I/usr/local/include -D_GLIBCXX_USE_SCHED_YIELD -D_GLIBCXX_USE_NANOSLEEP
LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib
DEBUG=yes

##################################################################################################

ifeq ($(DEBUG), yes)
	CXXFLAGS += -g -Wall -Wextra -pedantic
	#CXXFLAGS += -D_GLIBCXX_PROFILE
	#CXXFLAGS += -pg
	HIDE=
else
	CXXFLAGS += -O4 -DNDEBUG
	HIDE=@
endif

INC=$(wildcard inc/mugu/*.hpp)

SRC_LIB=$(wildcard src/*.cpp)
OBJ=$(patsubst src/%.cpp,obj/%.o, $(SRC_LIB))

SRC_TST=$(wildcard tst/*.cpp)
TST=$(patsubst tst/%.cpp,tst/%.out, $(SRC_TST))

all: lib/libmugu.a
	@ echo Done.

clean:
	$(HIDE) rm -f obj/*
	$(HIDE) rm -f lib/*
	$(HIDE) rm -f tst/*.out
	$(HIDE) rm -rf doc/*
	@ echo Cleaned.

obj/%.o: src/%.cpp $(INC)
	$(HIDE) $(CXX) $(CXXFLAGS) -std=c++0x -Iinc -c $< -o $@
	@ echo Compiled $@
	
lib/libmugu.a: $(OBJ)
	$(HIDE) ar rcs $@ $^
	@ echo Linked lib/libmugu.a

tst/%.out: tst/%.cpp $(INC) lib/libmugu.a
	$(HIDE) $(CXX) $(CXXFLAGS) $(LDFLAGS) -std=c++0x -Iinc -Llib $< -o $@ -lcairo -lxcb -lxcb-atom -lmugu
	@ echo Compiled $@

fixes:
	$(HIDE) find inc src -exec grep -H 'cout' {} \;
	$(HIDE) find inc src -exec grep -H 'iostream' {} \;
	$(HIDE) find inc src -exec grep -H 'FIXME' {} \;
	$(HIDE) find inc src -exec grep -H 'TODO' {} \;
	$(HIDE) find inc src -exec grep -H 'WTF' {} \;

tests: lib/libmugu.a $(TST)

docs:
	doxygen Doxyfile

