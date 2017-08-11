TEMPLATE	= lib
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows
CONFIG += c++11


# CONFIG    -= debug  # ist RELEASE aktiv
CONFIG    -= release  # ist DEBUG aktiv

CONFIG    += staticlib

INCLUDEPATH += ./Header
INCLUDEPATH += ../sst_str01_lib/Header
INCLUDEPATH += ../sst_misc01_lib/Header
INCLUDEPATH += ../sst_rec04_lib/Header

HEADERS		+=  ./Header/sstCpp01Lib.h
HEADERS		+= sstCpp01LibInt.h


SOURCES		+= sstCpp01Lib.cpp

OTHER_FILES += README.md

debug{
  TARGET		= sst_cpp01_lib_d
}
release{
  TARGET		= sst_cpp01_lib_r
}


DESTDIR     = ../libs

DISTFILES += \
    dxftype.def

