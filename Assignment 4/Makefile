CC=g++ -std=c++11 -g

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
	rm -f ./animation/frames/out*.tga
%.o : %.cpp %.hpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAGS) $(LIBS)

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS) $(LIBS)


video:
	ffmpeg -r 60 -start_number 0 -i ./animation/frames/out%d.tga -b:v 16384k  -vcodec libx264 -r 60 ./animation/video/temp.avi
	ffmpeg -i ./animation/video/temp.avi -i ./animation/video/animation_audio.mp3  -c:v copy -c:a aac -strict experimental animation.avi

report:  
	doxygen config_file

clean:
	rm -f $(OBJS) $(BIN)
	rm -rf html/
	rm -f ./animation/frames/out*.tga
	rm -f ./animation/video/temp.avi
	rm -f ./animation.avi
