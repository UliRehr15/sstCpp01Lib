/**********************************************************************
 *
 * sstMiscLib - cpp miscellaneous library for sst
 * Hosted on github
 *
 * Copyright (C) 2015 Uli Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstCpp01VarDefTypFil.cpp    13.01.17  Re.    13.01.17  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <list>
#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstCpp01Lib.h>

#include "sstCpp01LibInt.h"


sstCpp01VarDefTypFilCls::sstCpp01VarDefTypFilCls()
{

}

int sstCpp01VarDefTypFilCls::GetHeaderStr(int iKey, std::string oVarDefTypFilNam, std::string *oHeaderStr)
{
  sstMisc01AscFilCls oAscFil;
  sstStr01VarDefCls oVarDefTypRec;
  sstStr01VarDefFncCls oVarDefTypFnc;
  sstStr01Cls oCsvStrCnvt;
  std::string oVarDefStr;
  std::string oErrStr;

  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Open Asc File for reading
  iStat = oAscFil.fopenRd ( 0, (char*)oVarDefTypFilNam.c_str());
  if (iStat != 0) return -2;

  oHeaderStr->clear();
  oCsvStrCnvt.SetSeparatorTyp(0,0);

  int iStat1 = oAscFil.Rd_StrDS1(0,&oVarDefStr);

  while (iStat1 >= 0)
  {
    iStat = oVarDefTypFnc.ReadCSV(0,&oVarDefStr,&oErrStr,&oVarDefTypRec);
    if (iStat < 0)
    {
      oAscFil.fcloseFil(0);
      return -3;
    }
    oCsvStrCnvt.Csv_Str_2String(0,oVarDefTypRec.Get_EleNam(),oHeaderStr);
    iStat1 = oAscFil.Rd_StrDS1(0,&oVarDefStr);
  }

  oAscFil.fcloseFil(0);

  return iStat;
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int Blanko (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
