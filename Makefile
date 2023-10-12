CC = g++
DBG = gdb

C_FLAGS = -Wall -std=c++20
C_FLAGS_DBG = -Wall -g -std=c++20
LD_FLAGS = -lGL -lGLEW -lglfw -lm -pthread

SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
HDRS = $(addsuffix .o,$(basename $(SRCS)))

barbaria: $(OBJS) $(HDRS)
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(LD_FLAGS) -c -o $@ $^

debug: $(OBJS) $(HDRS)
	$(CC) $(C_FLAGS_DBG) -o barbaria_dbg $(OBJS)


clean:
	rm $(OBJS)
	rm barbaria

