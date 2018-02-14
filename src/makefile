TOP=../..
include $(TOP)/graphics.cfg

FILENAME = solarsys
#TARGET = $(FILENAME)

.PHONY: 

SOURCES = \
$(FILENAME).cpp

# all the .o files need to be listed here.  Leave backslash off last list item
APPOBJS = \
$(VPATH)/$(FILENAME).o 

APPDEP = $(APPOBJS:.o=.d)
OBJECTS = $(APPOBJS)

APP = $(BINDIR)/$(FILENAME)

all: $(APP)

# $(CXX) -MD creates a .d file and a .o file in the VPATH directory
$(APPDEP):      $(VPATH)/%.d:   %.cpp
	-mkdir -p $(VPATH)
	$(CXX) -MD $(CXXFLAGS)  -o $(@:.d=.o) $<

$(OBJECTS): $(VPATH)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(APP):  $(OBJECTS) $(LIBDIR)/libGraphicsUtils.a
	-mkdir -p $(BINDIR)
	-mkdir -p $(LIBDIR)
	make -C $(LIBDIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) -l GraphicsUtils $(GLIBS) 

clean:
	rm -rf *.o *.d $(APP) $(VPATH)

# this generates errors on the first pass, but then these .d files
# get created for the second pass.  

include $(OBJECTS .o=.d) 


