include ${MOAB_DIR}/lib/moab.make

MOAB_CXXFLAGS =  -Wall -pipe -pedantic -Wno-long-long
MOAB_CFLAGS = -Wall -pipe -pedantic -Wno-long-long
CXXFLAGS += ${MOAB_CXXFLAGS} -g 
CC = g++
LD_FLAGS = -g
CPPFLAGS += ${MOAB_INCLUDES} -g
CFLAGS   += ${MOAB_CFLAGS} -g
# add -g -pg to both CXX and LD flags to profile

all: moab_example 

#moab_example.o: moab_example.hpp
#	$(CC) $(CXXFLAGS) ${MOAB_INCLUDES} -c moab_example.hpp

moab_example: moab_example.o 
	$(CC) $(LD_FLAGS) -o moab_example moab_example.o  \
	 ${MOAB_LIBS_LINK}
