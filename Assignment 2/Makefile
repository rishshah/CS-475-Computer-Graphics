CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

FRAMEWORK_SRC= ./framework/gl_framework.cpp
FRAMEWORK_INC= ./framework/gl_framework.hpp

GLOBAL_INC= ./global.hpp

SHADER_SRC= ./shader_utils/shader_util.cpp
SHADER_INC= ./shader_utils/shader_util.hpp

VERTEX_SRC= ./model/vertex.cpp
VERTEX_INC= ./model/vertex.hpp

CLIPPING_SRC= ./model/clipping.cpp
CLIPPING_INC= ./model/clipping.hpp

MODEL_SRC= ./model/model.cpp
MODEL_INC= ./model/model.hpp

# AXES_SRC= ./model/axes.cpp
# AXES_INC= ./model/axes.hpp


SCENE_SRC= ./model/scene.cpp
SCENE_INC= ./model/scene.hpp

CALLBACKS_SRC= ./callbacks/callbacks.cpp
CALLBACKS_INC= ./callbacks/callbacks.hpp

BIN=executable
SRCS=./main.cpp $(FRAMEWORK_SRC) $(SHADER_SRC) $(VERTEX_SRC) $(CLIPPING_SRC) $(MODEL_SRC) $(SCENE_SRC) $(CALLBACKS_SRC) 
INCLUDES= ./main.hpp $(FRAMEWORK_INC) $(GLOBAL_INC) $(SHADER_INC) $(VERTEX_INC) $(CLIPPING_INC) $(MODEL_INC) $(SCENE_INC) $(CALLBACKS_INC)

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ -std=c++11 $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

report:  
	doxygen config_file

clean:
	rm -f *~ *.o $(BIN)
	rm -rf html/
