CXXFLAGS =	 -g -Wall -fmessage-length=0

OBJS =		Monitor.o

LIBS =

TARGET =	Monitor

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

Monitor:	$(TARGET)



clean:
	rm -f $(OBJS) $(TARGET)
