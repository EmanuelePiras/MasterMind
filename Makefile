CC      := gcc
CCFLAGS := -Wall -Wextra -Werror

TARGET:= mastermind
MAINS  := $(addsuffix .o, $(TARGET) )
SRCS   := $(wildcard *.c)
OBJ    := $(SRCS:%.c=%.o)
DEPS   := $(wildcard *.h)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

# all prerequisites ($<)
$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

# a list of what is in OBJ and not in MAINS
$(TARGET): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $^ $(CCFLAGS)
