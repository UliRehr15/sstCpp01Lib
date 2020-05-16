TEMPLATE	= app
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows
CONFIG    += c++11

# CONFIG    -= debug  # ist RELEASE aktiv
CONFIG    -= release  # ist DEBUG aktiv

CONFIG    += staticlib

INCLUDEPATH +=  ../../sst_rec04_lib/Header
INCLUDEPATH +=  ../../sst_misc01_lib/Header
INCLUDEPATH +=  ../../sstMath01Lib/Header
INCLUDEPATH +=  ../../sst_str01_lib/Header
INCLUDEPATH +=  ../Header

debug{
  LIBS        += ../../libs/libsst_cpp01_lib_d.a
  LIBS        += ../../libs/libsst_rec04_lib_d.a
  LIBS        += ../../libs/libsst_misc01_lib_d.a
  LIBS        += ../../libs/libsst_str01_lib_d.a
}
release{

  win32-g++:QMAKE_LFLAGS += -static
  win32-g++:QMAKE_LFLAGS -= -mthreads
  win32-g++:QMAKE_LFLAGS_EXCEPTIONS_ON -= -mthreads
  win32-g++:QMAKE_CXXFLAGS_EXCEPTIONS_ON -= -mthreads

  LIBS        += ../../libs/libsst_cpp01_lib_r.a
  LIBS        += ../../libs/libsst_rec04_lib_r.a
  LIBS        += ../../libs/libsst_misc01_lib_r.a
  LIBS        += ../../libs/libsst_str01_lib_r.a
}

HEADERS   += sst_generate_typ_lib.h

SOURCES		+= sst_generate_typ_lib.cpp \
             sst_generate_typ1.cpp

TARGET = sst_generate_typ_lib

# copy to deployment directory
# DESTDIR     = ../../../../local_deploy




