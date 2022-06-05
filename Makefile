CXX=clang++
LDFLAGS=-L/usr/local/opt/openssl@3/lib -lcrypto -lssl
CPPFLAGS=-I./lib -I/usr/local/opt/openssl@3/include

cpp_movie: ./main.cpp ./lib/httplib.h
	$(CXX) -std=c++17 -o cpp_movie main.cpp $(CPPFLAGS) $(LDFLAGS) 

lib/httplib.h:
	wget -P ./lib https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

