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


RENDER_SRC= ./inspection/render.cpp ./modelling/render.cpp
RENDER_INC= ./inspection/render.hpp ./modelling/render.hpp

CALLBACKS_SRC= ./callbacks/callbacks.cpp ./callbacks/inspection_callbacks.cpp ./callbacks/modelling_callbacks.cpp
CALLBACKS_INC= ./callbacks/callbacks.hpp ./callbacks/inspection_callbacks.hpp ./callbacks/modelling_callbacks.hpp

BIN=executable
SRCS=./main.cpp $(FRAMEWORK_SRC) $(SHADER_SRC) $(MODEL_SRC) $(CALLBACKS_SRC) $(RENDER_SRC)
INCLUDES= ./main.hpp $(FRAMEWORK_INC) $(SHADER_INC) $(MODEL_INC) $(CALLBACKS_INC) $(RENDER_INC)

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
