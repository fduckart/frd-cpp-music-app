# Build Music Collection System application.

# Set the compiler
CC = /usr/bin/g++

# Compiler flags
CFLAGS = -g -Wall -c

# Linker flags 
LDFLAGS = -o

PROG0 = music
PROG1 = testrepository
PROG2 = testartist 
PROG3 = testcommand
PROG4 = testgenre
PROG5 = testtrack
PROG6 = testrecord 

ALL_PROGRAMS = $(PROG0) $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5) $(PROG6)

# Source files.
PROG00_OBJS = music.o
PROG01_OBJS = repository.o
PROG02_OBJS = artist.o
PROG03_OBJS = record.o
PROG04_OBJS = track.o
PROG05_OBJS = testrepository.o
PROG06_OBJS = testartist.o
PROG07_OBJS = command.o
PROG08_OBJS = testcommand.o
PROG09_OBJS = genre.o
PROG10_OBJS = testgenre.o
PROG12_OBJS = testtrack.o
PROG13_OBJS = testrecord.o

# Header files.
SOURCE_HDRS = artist.h \
              command.h \
	      genre.h \
	      music.h \
	      record.h \
	      repository.h \
	      track.h \
	      genre.h


# FIRST RULE: Build everything
all:		$(ALL_PROGRAMS)

# Rule to build 'music' program.  This is the main application.
$(PROG0):	$(PROG00_OBJS) $(PROG01_OBJS) $(PROG02_OBJS) \
                $(PROG03_OBJS) $(PROG04_OBJS) $(PROG07_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testrepository' program.
$(PROG1):	$(PROG01_OBJS) $(PROG02_OBJS) $(PROG03_OBJS) \
                $(PROG04_OBJS) $(PROG05_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testartist' program.
$(PROG2):	$(PROG01_OBJS) $(PROG02_OBJS) $(PROG03_OBJS) \
                $(PROG04_OBJS) $(PROG06_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testcommand' program.
$(PROG3):	$(PROG07_OBJS) $(PROG08_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testgenre' program.
$(PROG4):	$(PROG09_OBJS) $(PROG10_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testtrack' program.
$(PROG5):	$(PROG04_OBJS) $(PROG12_OBJS)
		$(CC) $(LDFLAGS) $@ $^

# Rule to build 'testrecord' program.
$(PROG6):	$(PROG02_OBJS) $(PROG03_OBJS) $(PROG04_OBJS) $(PROG13_OBJS)
		$(CC) $(LDFLAGS) $@ $^


# This rule defines how to build any .o file
# from its corresponding .cpp file
%.o:		%.cpp $(SOURCE_HDRS)
		$(CC) $(CFLAGS) $<


# Clean up - note, no dependency,
# if this rule is called always do it
clean:
		rm -f *.o ~* $(ALL_PROGRAMS)

