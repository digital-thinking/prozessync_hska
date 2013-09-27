CXXFLAGS =	 -g -Wall -fmessage-length=0

OBJS =		Car.o

LIBS =

TARGET =	Car

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

CarFactory:	$(TARGET)



clean:
	rm -f $(OBJS) $(TARGET)
