CXX ?= g++

# path #
APP_SRC_PATH = src
UNIT_TEST_PATH = test
BUILD_PATH = obj
BIN_PATH = bin

# executable # 
BIN_NAME = hammingstr
UNIT_TEST_NAME = unit_test

# so name
LIB_NAME = libdistance

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
APP_SOURCES = $(shell find $(APP_SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
APP_OBJECTS = $(APP_SOURCES:$(APP_SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
APP_DEPS = $(APP_OBJECTS:.o=.d)

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
UNIT_TEST_SOURCES = $(shell find $(UNIT_TEST_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
UNIT_TEST_OBJECTS = $(UNIT_TEST_SOURCES:$(UNIT_TEST_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
UNIT_TEST_APP_OBJECTS=$(filter-out $(BUILD_PATH)/main.o,$(APP_OBJECTS))
UNIT_TEST_DEPS = $(UNIT_TEST_OBJECTS:.o=.d) $(UNIT_TEST_APP_OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g -fPIC
INCLUDES = -I include/ -I /usr/local/include -I ../googletest/googletest/include -I test/
# Space-separated pkg-config libraries used by this project
LIB_PATHS = -L. -L ../googletest/googlemock/ -L ../googletest/googlemock/gtest
LIBS = -lgtest -lgmock -lgmock_main

CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)

.PHONY: release
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@$(RM) $(BIN_NAME)
	@$(RM) $(UNIT_TEST_NAME)
	@$(RM) $(LIB_NAME)
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME) $(BIN_PATH)/$(LIB_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(APP_OBJECTS)
	$(CXX) $(LIB_PATHS) $(LIBS) $^ -o $@

# Creation of the executable
$(BIN_PATH)/$(LIB_NAME): $(APP_OBJECTS)
	$(CXX) -shared -Wl,-soname,$(notdir $@) $^ -o $@

# Creation of the executable
.PHONY: test
test: dirs $(BIN_PATH)/$(UNIT_TEST_NAME)

$(BIN_PATH)/$(UNIT_TEST_NAME): $(UNIT_TEST_APP_OBJECTS) $(UNIT_TEST_OBJECTS)
	$(CXX) $(LIB_PATHS) $(LIBS) $^ -o $@

# Add dependency files, if they exist
-include $(APP_DEPS)
-include $(UNIT_TEST_DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(APP_SRC_PATH)/%.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

## Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(UNIT_TEST_PATH)/%.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@
