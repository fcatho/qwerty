CXX ?= g++

APP_SRC_PATH = src
BUILD_PATH = obj
SO_PATH=lib
BIN_PATH = bin
SERVER_NAME = marketserver
CLIENT_NAME = marketclient
SO_NAME = liboscomm.so
SRC_EXT = cpp


# code lists #
# Find all source files in the source directory, sorted by most recently modified
SO_SOURCES = $(shell find $(APP_SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
EXC_OBJECTS = $(BUILD_PATH)/$(SERVER_NAME).o $(BUILD_PATH)/$(CLIENT_NAME).o
SO_OBJECTS = $(filter-out $(EXC_OBJECTS),$(SO_SOURCES:$(APP_SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o))

# Set the dependency files that will be used to add header dependencies
SO_DEPS = $(SO_OBJECTS:.o=.d)

# just use main as object, so will cover all our needs
SERVER_SOURCES = $(shell find $(APP_SRC_PATH) -name '$(SERVER_NAME).$(SRC_EXT)' | sort -k 1nr | cut -f2-)
SERVER_OBJECTS = $(SERVER_SOURCES:$(APP_SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
SERVER_DEPS = $(SERVE_OBJECTS:.o=.d)
CLIENT_SOURCES = $(shell find $(APP_SRC_PATH) -name '$(CLIENT_NAME).$(SRC_EXT)' | sort -k 1nr | cut -f2-)
CLIENT_OBJECTS = $(CLIENT_SOURCES:$(APP_SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
CLIENT_DEPS = $(CLIENT_OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g -fPIC
INCLUDES = -I include/ -I /usr/local/include

# Space-separated libraries used by this project
LIB_PATHS = -L $(SO_PATH)
APP_LIBS = -loscomm -lboost_system -lboost_thread -lboost_serialization -lboost_program_options

CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)

.PHONY: release
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(SO_PATH)

.PHONY: clean
clean:
	@$(RM) $(SERVER_NAME)
	@$(RM) $(CLIENT_NAME)
	@$(RM) $(SO_NAME)
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(SO_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(SO_PATH)/$(SO_NAME) $(BIN_PATH)/$(SERVER_NAME) $(BIN_PATH)/$(CLIENT_NAME)

# Creation of the executable
$(BIN_PATH)/$(SERVER_NAME): $(SERVER_OBJECTS)
	$(CXX) $(LIB_PATHS) $^ -o $@ $(APP_LIBS)

$(BIN_PATH)/$(CLIENT_NAME): $(CLIENT_OBJECTS)
	$(CXX) $(LIB_PATHS) $^ -o $@ $(APP_LIBS)

# Creation of the so
.PHONY: lib
lib: dirs $(SO_PATH)/$(SO_NAME)
$(SO_PATH)/$(SO_NAME): $(SO_OBJECTS)
	$(CXX) -shared -Wl,-soname,$(notdir $@) $^ -o $@

# Add dependency files, if they exist
-include $(SO_DEPS)
-include $(SERVER_DEPS)
-include $(CLIENT_DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(APP_SRC_PATH)/%.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@
