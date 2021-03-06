TAR = Projet-HTTP-save
IGNORE1 = .vscode
IGNORE2 = Only4G33ks
IGNORE3 = httpparseur
IGNORE4 = .git
IGNORE5 = .gitignore
IGNORE6 = LICENSE
IGNORE7 = profparser
IGNORE8 = script.bs



# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU makevariable containing the path to the current working directory
SOURCEDIR := src
BUILDDIR := obj
# Name of the final executable
TARGET = httpparseur
# Decide whether the commands will be shwon or not
VERBOSE = TRUE
# Create the list of directories
DIRS = main parseur semantique
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
# Generate the GCC includes parameters by adding -I before each source folder
LIBSDIR = librequest-0.5/api  libmagic #add the folder to the .h (api)
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I , $(dir)))
INCLUDES += $(foreach dir, $(LIBSDIR), $(addprefix -I lib/, $(dir)))
LFLAGS = -L lib/librequest-0.5 -L lib/libmagic -Wl,-rpath=lib/librequest-0.5:lib/libmagic -lrequest -lmagic
# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)
# Create a list of *.c sources in DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
# Define objects for all sources
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.c=.o))
# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)
DEPS += main.d
# Name the compiler
CC = gcc -g
# OS specific part
ifeq ($(OS),Windows_NT)
	RM = del /F /Q
	RMDIR = -RMDIR /S /Q
	MKDIR = -mkdir
	ERRIGNORE = 2>NUL || true
	SEP=\\
else
	RM = rm -rf
	RMDIR = rm -rf
	MKDIR = mkdir -p
	ERRIGNORE = 2>/dev/null
	SEP=/
endif
# Remove space after separator
PSEP = $(strip $(SEP))
# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.c
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef

.PHONY: all clean directories tar

all: directories $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking $@
	$(HIDE)$(CC) $(OBJS) $(LFLAGS) -o $(TARGET)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	@echo Cleaning done !

# Make a tar
tar: clean
	dir=$$(basename $$PWD) && echo "compressing $(dir)" && cd .. && \
	tar cvfz "$(TAR).tgz" \
	--transform="s,^$$dir,$(TAR)," \
	--exclude="$(IGNORE1)" --exclude="$(IGNORE2)" --exclude="$(IGNORE3)" --exclude="$(IGNORE4)" --exclude="$(IGNORE5)" --exclude="$(IGNORE6)" --exclude="$(IGNORE7)" --exclude="$(IGNORE8)" "$$dir" --verbose --show-transformed-names