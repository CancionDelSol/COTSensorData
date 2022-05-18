CXX := g++
CXXFLAGS=-Wall
FILE_LIST := src/helloworld.cpp
OBJ_FILES := src/build/helloworld.o

createDirs:
	@mkdir src/build
	@mkdir ../Delivery/RPi/

main: $(FILE_LIST) createDirs
	$(CXX) $(CXXFLAGS) -c $(FILE_LIST) -o $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o ../Delivery/RPi/helloworld

clean:
	rm -f helloworld $(OBJ_FILES)
	rm -rf src/build
	rm -rf ../Delivery/RPi/