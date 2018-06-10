TEMPLATE	  = app
CONFIG	 	 += warn_on
CONFIG       += qt
CONFIG       += windows
CONFIG       += c++11

QT += widgets

# CONFIG       -= debug  # RELEASE ist aktiv
CONFIG       -= release  # DEBUG ist aktiv

INCLUDEPATH +=  ../../sstMath01Lib/Header
INCLUDEPATH +=  ../../sstLibreCAD2Lib/Header
INCLUDEPATH +=  ../../dxflib/Header
INCLUDEPATH +=  ../../sst_str01_lib/Header
INCLUDEPATH +=  ../../sst_misc01_lib/Header
INCLUDEPATH +=  ../../sst_rec04_lib/Header
INCLUDEPATH +=  ../../sstQt01Lib/Header
INCLUDEPATH +=  ../../sstQtDxf01Lib/Header
INCLUDEPATH +=  ../../sst_dxf03_lib/Header
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

HEADERS    +=  sst_generate_qttab_lib.h

SOURCES    += \
    sst_generate_qttab_lib1.cpp \
    sst_generate_qttab_lib2.cpp

TARGET	  	= sst_generate_qttab_lib

# copy to deployment directory
# DESTDIR     = ../../../../../local_deploy
