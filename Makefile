# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  LearningOpenGL_config = debug
endif
ifeq ($(config),release)
  LearningOpenGL_config = release
endif

PROJECTS := LearningOpenGL

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

LearningOpenGL:
ifneq (,$(LearningOpenGL_config))
	@echo "==== Building LearningOpenGL ($(LearningOpenGL_config)) ===="
	@${MAKE} --no-print-directory -C . -f LearningOpenGL.make config=$(LearningOpenGL_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f LearningOpenGL.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   LearningOpenGL"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"