TARGET = XLP
 
OBJS = libs/aalib/pspaalib.o libs/aalib/pspaalibeffects.o libs/aalib/pspaalibscemp3.o libs/aalib/pspaalibwav.o libs/aalib/pspaalibat3.o libs/aalib/pspaalibogg.o \
libs/glib2d.o libs/timer.o libs/libccc.o libs/intraFont.o libs/libtext.o \
aalib.o color.o ctrl.o g2d.o intra.o power.o savedata.o sceIo.o time.o timer.o usb.o utility.o xtream.o main.o
 
INCDIR =
CFLAGS = -O2 -G0 -Wall -DPSPFW3xx
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
 
PSP_FW_VERSION = 600
BUILD_PRX = 1
 
LIBDIR =
LIBS = -llua -llualib -lpng -ljpeg -lz -lpspgum -lm -lmikmod -lpsprtc -lpsppower \
        -lpspgu -lpspdebug -lpsputility \
        -lpspmp3 -lpspatrac3 -lvorbisidec -lpspaudio -lpspvram \
        -lpspusb -lpspusbstor
 
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = XLP - XtreamLua Player
PSP_EBOOT_ICON = release/icon0.png
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

loadlib.S: loadlib/exports.exp
	$(shell psp-config --pspdev-path)/bin/psp-build-exports --build-stubs $<