CXX ?= g++

# path #
SRC_PATH = src
BUILD_PATH = obj
BIN_PATH = bin

# executable # 
BIN_NAME = waes

# so name
LIB_NAME = libwaes

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g -fPIC
INCLUDES = -I include/ -I /usr/local/include
# Space-separated pkg-config libraries used by this project
LIB_PATHS = -L.
LIBS = 

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
#	@echo "Creating directories"

.PHONY: clean
clean:
	@$(RM) $(BIN_NAME)
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)
#	@echo "Deleting $(BIN_NAME) symlink"
#	@echo "Deleting directories"

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME) $(BIN_PATH)/$(LIB_NAME)
#	@echo "Making symlink: $(BIN_NAME) -> $<"
#	@$(RM) $(BIN_NAME)
#	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	$(CXX) $(LIB_PATHS) $(LIBS) $^ -o $@

# Creation of the executable
$(BIN_PATH)/$(LIB_NAME): $(OBJECTS)
	$(CXX) -shared -Wl,-soname,$(notdir $@) $^ -o $@

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
#	@echo "Compiling: $< -> $@"

