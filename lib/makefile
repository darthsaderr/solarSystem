TOP=..
include $(TOP)/graphics.cfg

SOURCES=\
    Utils.cpp \
		vips.cpp \
		sadielib.cpp \
		polyline.cpp \
		mymesh.cpp \
		final.cpp \
		tween.cpp
	#	mesh.cpp 

LIBOBJS=\
    $(VPATH)/Utils.o \
		$(VPATH)/vips.o \
		$(VPATH)/sadielib.o \
		$(VPATH)/polyline.o \
		$(VPATH)/mymesh.o \
		$(VPATH)/final.o \
		$(VPATH)/tween.o
#		$(VPATH)/mesh.o 

LIBDEP = $(LIBOBJS:.o=.d)
OBJECTS = $(LIBOBJS)

UTILLIB=libGraphicsUtils.a

all: $(UTILLIB)

# $(CXX) -MD creates a .d file and a .o file in the VPATH directory
$(LIBDEP):      $(VPATH)/%.d:   %.cpp
	-mkdir -p $(VPATH)
	$(CXX) -MD $(CXXFLAGS)  -o $(@:.d=.o) $<


$(OBJECTS): $(VPATH)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(UTILLIB): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

clean:
	rm -rf $(UTILLIB) $(VPATH)

include $(OBJECTS:.o=.d)

