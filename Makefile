CXX=clang++
LDFLAGS=-L/opt/homebrew/opt/openssl@3/lib -lcrypto -lssl
CPPFLAGS=-I./lib -I/opt/homebrew/opt/openssl@3/include

.PHONY: clean

bin/cpp_movie: ./main.cpp ./lib/httplib.h
	mkdir -p bin
	$(CXX) -std=c++17 -o bin/cpp_movie main.cpp $(CPPFLAGS) $(LDFLAGS) 

lib/httplib.h:
	wget -P ./lib https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

clean:
	rm -rf bin