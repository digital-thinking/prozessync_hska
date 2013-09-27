CXXFLAGS =	 -g -Wall -fmessage-length=0

OBJS =		Runner.o

LIBS =

TARGET =	Runner

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
