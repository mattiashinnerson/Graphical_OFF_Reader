OBJS   = guicallback.o guicontrol.o walking_in_air.o shadertools.o OFFReader.o MatrixCalc.o bezierCalc.o keyBoardNMouse.o convertionFuncs.o illumination.o openNRead.o
TARGET = walking_in_air

CXX = g++

DBFLAGS  = -O0 -g3 -ggdb3 -fno-inline
#DBFLAGS = -O2
WFLAGS   = -Wall -ansi -g
GLFLAGS  = `pkg-config --cflags gtk+-2.0`
LGLFLAGS = `pkg-config --libs gtk+-2.0` -lGL -lGLEW -lGLU -lglut

CXXFLAGS = $(STDFLAGS) $(WFLAGS) $(DFLAGS) $(GLFLAGS)
LDFLAGS  =  -export-dynamic -lm -lXext -lX11 $(LGLFLAGS)


all: $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)

.SUFFIXES: .cc
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) 
