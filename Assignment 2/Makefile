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

VERTEX_SRC= ./classes/vertex.cpp
VERTEX_INC= ./classes/vertex.hpp

CLIPPING_SRC= ./classes/clipping.cpp
CLIPPING_INC= ./classes/clipping.hpp

MODEL_SRC= ./classes/model.cpp
MODEL_INC= ./classes/model.hpp

AXES_SRC= ./classes/axes.cpp
AXES_INC= ./classes/axes.hpp

WCAM_SRC= ./classes/worldCamera.cpp
WCAM_INC= ./classes/worldCamera.hpp

SCENE_SRC= ./classes/scene.cpp
SCENE_INC= ./classes/scene.hpp

CALLBACKS_SRC= ./callbacks/callbacks.cpp
CALLBACKS_INC= ./callbacks/callbacks.hpp

BIN=executable
SRCS=./main.cpp $(FRAMEWORK_SRC) $(SHADER_SRC) $(VERTEX_SRC) $(CLIPPING_SRC) $(MODEL_SRC) $(SCENE_SRC) $(CALLBACKS_SRC) $(AXES_SRC) $(WCAM_SRC)
INCLUDES= ./main.hpp $(FRAMEWORK_INC) $(GLOBAL_INC) $(SHADER_INC) $(VERTEX_INC) $(CLIPPING_INC) $(MODEL_INC) $(SCENE_INC) $(CALLBACKS_INC) $(AXES_INC) $(WCAM_INC)

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ -std=c++11 $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

report:  
	doxygen config_file

clean:
	rm -f *~ *.o $(BIN)
	rm -rf html/
