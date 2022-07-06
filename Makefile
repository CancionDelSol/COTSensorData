# Set the default goal
.DEFAULT_GOAL := generate

# Source 
SOURCE_DIR := src

# Build
BUILD_DIR := src/build

# Classes
CLASSES_OUTPUT := src/build/classes

# Source files
JAVA_FILES := $(find . -name '*.java')

classpath:
	@mkdir -p $(CLASSES_OUTPUT)

buildpath:
	@mkdir -p $(BUILD_DIR)

javacbuild: classpath buildpath
	@echo "Creating classes"
	@javac -cp "./lib/RXTXcomm-2.2pre2.jar" -sourcepath src -d $(CLASSES_OUTPUT) $(SOURCE_DIR)/**/*.java $(SOURCE_DIR)/*.java

createmanifest: javacbuild
	@echo "Writing manifest"
	@echo "Main-Class: Program\nClass-Path: ./lib/RXTXcomm-2.2pre2.jar">src/myManifest

createjar: createmanifest
	@echo "Creating jar"
	@jar cfm src/build/Telem.jar src/myManifest -C src/build/classes/ .
	@cp src/build/Telem.jar Telem.jar

generate: createjar
	@echo "Complete"

tests: generate
	@clear
	@java -jar Telem.jar -test

startRemote: generate
	@clear
	@java -jar Telem.jar -rem

startLocal: generate
	@clear
	@java -jar Telem.jar -loc

deconfig:
	@rm -rf *.cfg

config:
	@cp data/configFileDefaults/*.cfg ./

clean:
	@echo "Cleaning up..."
	@rm -r src/build/classes
	@rm src/myManifest
	@rm src/build/*.jar
	@rm -r src/build
	@rm ./*.jar