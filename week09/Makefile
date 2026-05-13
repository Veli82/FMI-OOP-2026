CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic

TASK_BINS := $(patsubst %.cc,%,$(TASK_SRCS))

.PHONY: all clean

all: $(TASK_BINS)

%: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

run-%: task%
	./task$*

clean:
	rm -f $(TASK_BINS)
	rm -rf *.dSYM
