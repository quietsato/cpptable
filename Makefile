CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pipe -Iheader

table.a: cell.o table.o
	ar ru $@ $^

table.o: source/table.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

cell.o: source/cell.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

test: table.a test/main.cpp
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	./test/$@

clean:
	rm -f *.o *.a test/test