CC=g++ -std=c++11

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=executable
SRCS= $(wildcard */*.cpp) $(wildcard *.cpp)
OBJS= $(patsubst %.cpp, %.o, $(SRCS))

all: $(BIN)

%.o : %.cpp %.hpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAGS) $(LIBS)

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS) $(LIBS)

# $(OBJS): $(SRCS) $(INCS)
# 	$(CC) $(CPPFLAGS) -c $(SRCS) -o $(OBJS) $(LDFLAGS) $(LIBS)

report:  
	doxygen config_file

clean:
	rm -f $(OBJS) $(BIN)
	rm -rf html/
