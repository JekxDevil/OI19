CXXFLAGS = -Wall -Wno-unknown-pragmas -ggdb3 -DDEBUG

all: gorp

OBJECTS = gorp.o

gorp: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS)

veryclean: clean
	rm -f gorp

env:
	make -version | head -1