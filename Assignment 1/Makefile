CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

FRAMEWORK_SRC= ./framework/gl_framework.cpp
FRAMEWORK_INC= ./framework/gl_framework.hpp

SHADER_SRC= ./shader_utils/shader_util.cpp
SHADER_INC= ./shader_utils/shader_util.hpp

MODEL_SRC= ./model/model.cpp
MODEL_INC= ./model/model.hpp

CALLBACKS_SRC= ./inspection/callbacks.cpp ./modelling/callbacks.cpp
CALLBACKS_INC= ./inspection/callbacks.hpp ./modelling/callbacks.hpp

BIN=./bin/preview
SRCS=./inspection/inspect.cpp $(FRAMEWORK_SRC) $(SHADER_SRC) $(MODEL_SRC) $(CALLBACKS_SRC)
INCLUDES= ./inspection/inspect.hpp 	$(FRAMEWORK_INC) $(SHADER_INC) $(MODEL_INC) $(CALLBACKS_INC) 

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
