CC := g++
LDFLAGS :=
TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))
.PHONY:all
all:$(TARGETS)

.SECONDEXPANSION:

$(TARGETS):$$($$@_OBJ)
	$(CC) $@.cpp $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@


.PHONY:clean
clean:
	rm -rf *.dSYM
	rm -rf $(TARGETS) $(foreach targ,$(TARGETS),$(targ).bin)