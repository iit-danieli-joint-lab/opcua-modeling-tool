#wxWidget Debug
#DEBUG_CONSOLE=-DDEBUG_CONSOLE
LOG_FILE=-DLOG_FILE
#TODO: Add dependency to headers, otherwise changing headers will not compile updated objects.

OBJ_DIR=obj

ifdef ComSpec
    include Makefile.win.properties
    EXECUTABLE=eXcelerator.exe

    RM_FOUND=$(shell where rm)

    #If make has not been ran from the command line, rm.exe may be defined(by any toolchain set such as cygwin).
    #if so, we will use unix command for clean. $(info Is rm found? $(RM_FOUND))
    ifeq "$(RM_FOUND)" ""
        CLEAN_TARGET=clean_win
    else
        CLEAN_TARGET=clean_nix
    endif

    RESOURCE=$(OBJ_DIR)/resource.res
else
    include Makefile.linux.properties
    EXECUTABLE=eXcelerator
    CLEAN_TARGET=clean_nix
    CXX=g++

    #In linux, we can get wxWidgets info from wx-config. Windows needs to download a separate executable for this.
    WXCXXFLAGS=$(shell wx-config --cxxflags)
    WXLIBS=$(shell wx-config --libs adv,core,base)
    LD_OTHER_FLAGS=-Wl,-rpath,$(shell wx-config --prefix)/lib

endif

#CXXFLAGS:=-std=c++98 $(DEBUG) $(WXCXXFLAGS) -I./inc -I./inc/synthesis -I./inc/SimpleJSON $(USER_INCLUDES)
CXXFLAGS:=-std=c++98 -Wall -Werror $(DEBUG) $(DEBUG_CONSOLE) $(WXCXXFLAGS) $(LOG_FILE) -I./inc -I./inc/synthesis -I./inc/simpleJSON $(USER_INCLUDES)
LIBS=$(WXLIBS) $(USER_LIBS) 
LDFLAGS=$(DEBUG)

.PHONY : clean clean_win clean_nix

OBJS=$(OBJ_DIR)/wxFrameMain.o $(OBJ_DIR)/wxOPCUAApp.o $(OBJ_DIR)/wxProjectDialog.o\
     $(OBJ_DIR)/wxParameterDialog.o $(OBJ_DIR)/wxFieldDialog.o $(OBJ_DIR)/wxEnumDialog.o\
     $(OBJ_DIR)/wxPanelObjectType.o $(OBJ_DIR)/wxPanelVariableType.o $(OBJ_DIR)/wxPanelVariable.o\
     $(OBJ_DIR)/wxPanelType.o $(OBJ_DIR)/wxPanelNode.o $(OBJ_DIR)/wxPanelReferenceType.o\
     $(OBJ_DIR)/wxPanelInstance.o $(OBJ_DIR)/wxPanelReference.o $(OBJ_DIR)/wxTreeDialog.o\
	 $(OBJ_DIR)/wxPanelStructDataType.o $(OBJ_DIR)/wxPanelEnumDataType.o $(OBJ_DIR)/wxPanelMethod.o\
     $(OBJ_DIR)/opc.o $(OBJ_DIR)/opcutils.o $(OBJ_DIR)/opcitemdata.o $(OBJ_DIR)/modelTree.o\
	 $(OBJ_DIR)/opcelement.o $(OBJ_DIR)/opcglobal.o $(OBJ_DIR)/opcimporter.o $(OBJ_DIR)/xmlreader.o \
	 $(OBJ_DIR)/wxAbout.o $(OBJ_DIR)/wxCompileDialog.o $(OBJ_DIR)/wxConfig.o $(OBJ_DIR)/wxProjectGitDialog.o \
	 $(OBJ_DIR)/wxLogin.o $(OBJ_DIR)/JSONValue.o $(OBJ_DIR)/JSON.o $(RESOURCE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@  $^ $(LIBS) $(LD_OTHER_FLAGS)
$(OBJ_DIR)/%.o: src/%.cpp
	${CXX} $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)/opc.o: src/synthesis/opc.cxx
	${CXX} $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: src/simpleJSON/%.cpp
	${CXX} $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)/resource.res:
	windres.exe $(WXCXXFLAGS) -J rc -O coff -i resource.rc -o $@ $<
clean: $(CLEAN_TARGET)
clean_win:
	del /f $(EXECUTABLE) $(OBJ_DIR)\*.o $(OBJ_DIR)\*~
clean_nix:
	rm -f $(EXECUTABLE) $(OBJ_DIR)/*.o $(OBJ_DIR)/*~
depends: 
