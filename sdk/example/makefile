####################### # Makefile ####################### 
# target 
TARGET := main 
# compile and lib parameter 
CC := g++ 
LDFLAGS := -L../lib/libClass.so  
LIBS := ../lib/libClass.so
DEFINES := 
INCLUDE := -I.
INC=-I.
CFLAGS := 
CXXFLAGS:= 
INCLUDE_DIRS= -I../myclass/include -I /usr/local/include/ -I /usr/local/include/opencv/ -I /usr/local/include/opencv2
# link 
$(TARGET):main.o 
	$(CC) -o $@ $^ $(LIBS) -L /usr/local/lib/libopencv_*
#compile 
main.o:main.cpp 
	$(CC) -c $^ -o $@ $(INCLUDE_DIRS) 
# clean
clean: 
	rm -fr *.o rm -fr $(TARGET)
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

