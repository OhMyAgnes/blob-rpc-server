CC := g++ 
LIBS := 
LDFLAGS := 
DEFINES := 
INCLUDE := -I. 
CFLAGS := CXXFLAGS:= 
# link parameter 
LIB := ../lib/libClass.so 
INCLUDE_DIRS= -I./include -I /usr/local/include/ -I /usr/local/include/opencv/ -I /usr/local/include/opencv2
#link 
$(LIB):myclass.o 
	$(CC) -shared -o  -fPIC -o $@  $^   -L /usr/local/lib/libopencv_*

#compile 
myclass.o:./src/myclass.cpp 
	$(CC) -c  -fPIC  $^  -o $@ $(INCLUDE_DIRS)
# clean 
clean: 
	rm -fr *.o
