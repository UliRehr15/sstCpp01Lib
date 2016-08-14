TEMPLATE	= lib
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows

# CONFIG    -= debug  # ist RELEASE aktiv
CONFIG    -= release  # ist DEBUG aktiv

CONFIG    += staticlib

INCLUDEPATH = ./Header

# SOURCES		+= str1_lib1.cpp
HEADERS		+= ./Header/sstTemplateLib.h
HEADERS		+= sstTemplateLibInt.h
SOURCES		+= sstTemplateLib.cpp

OTHER_FILES += readme.txt

debug{
  TARGET		= sstTemplateLib_d
}
release{
  TARGET		= sstTemplateLib_r
}

DESTDIR     = ../libs

