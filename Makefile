TARGET = XLP
 
OBJS = lib/pspaalib.o lib/pspaalibeffects.o lib/pspaalibscemp3.o \
       lib/pspaalibwav.o lib/pspaalibat3.o lib/pspaalibogg.o \
       lib/glib2d.o lib/libtimer.o lib/libccc.o lib/intraFont.o lib/libtext.o \
       aalib.o color.o ctrl.o g2d.o intra.o power.o savedata.o sceIo.o time.o \
       timer.o usb.o utility.o xtream.o main.o

CFLAGS = -O2 -G0 -Wall -I./include -L./lib
 
PSP_FW_VERSION = 600
BUILD_PRX = 1

LIBS = -llua -lpng -ljpeg -lm -lmikmod -lz -lvorbisidec \
       -lpspgum -lpspgu -lpspvram -lpspusb -lpspusbstor -lpsprtc -lpsppower \
       -lpspdebug -lpsputility -lpspmp3 -lpspatrac3  -lpspaudio
 
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = XLP - XtreamLua Player
PSP_EBOOT_ICON = res/icon0.png
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
