CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pipe -Iheader
INCLUDE = header/include.hpp

libtable.a: cell.o border.o table.o
	ar r $@ $^

table.o: source/table.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

border.o: source/border.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

cell.o: source/cell.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

test: test/main.cpp libtable.a
	$(CXX) $(CXXFLAGS) $< -o test/$@ -L./ -ltable
	./test/$@

clean:
	rm -f *.o *.a test/test
