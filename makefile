CXX = g++
INC = -I/usr/include/ -I/usr/local/include
LIBS = -lSDL2 -lSDL2main -lGL -lglut -lGLEW -lSDL2_image
FLG = -std=gnu++11 -g -D TRUTLE_COMPILE

SRCDIR = src/
OBJDIR = obj/
BUILDDIR = build/
INSTALLDIR = /usr/
LIBINSTALLDIR = $(INSTALLDIR)lib
INCINSTALLDIR = $(INSTALLDIR)include/trutle

LIBTARGET = $(BUILDDIR)libtrutle.a

SRC = $(shell find src -name '*.cpp' -print)
OBJ = $(subst .cpp,.o,$(SRC))
HEADERS = $(shell find -name '*.h' -print | egrep "^./src")

all: $(OBJ)
	@echo "LINK $(LIBTARGET)"
	@mkdir -p $(BUILDDIR)include 
	@ar rvs $(LIBTARGET) $(OBJ) > /dev/null
	@bash ./cpyheaders.sh

%.o: %.cpp
	@echo "COMPILE $<"
	@$(CXX) $(FLG) -o $@ -c $< $(INC) $(LIBS)

install: $(LIBTARGET)
	@echo "COPYING LIB"
	@mkdir -p $(LIBINSTALLDIR)
	@cp -f $(LIBTARGET) $(LIBINSTALLDIR)
	
	@echo "COPYING HEADERS"
	@rm -rf $(INCINSTALLDIR)
	@mkdir -p $(INCINSTALLDIR)
	@cp -rf $(BUILDDIR)include/* $(INCINSTALLDIR)

clean:
	@rm -rf $(OBJ) $(BUILDDIR)*
