// sstCpp01LibTest.cpp    15.01.17  Re.    15.01.17  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstCpp01Lib.h>

#include "sstCpp01LibTest.h"

//=============================================================================
int main (int argc, char *argv [])
//-----------------------------------------------------------------------------
{
  int iStat = 0;
//-----------------------------------------------------------------------------

  iStat = Test_VarDefTyp_Functions ( 0);

  return iStat;
}
//=============================================================================
int Test_VarDefTyp_Functions (int iKey)
//-----------------------------------------------------------------------------
{
  // sstCpp01VarDefTypFilCls oVarDefTypFil;
  std::string oHeaderStr;
  sstMisc01AscFilCls oTestFil;

  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  oTestFil.fopenWr(0,"VarDefTyps.csv");
  oTestFil.Wr_String(0,"LibNam;ClsNam;VarNam1;DD;4;2");
  oTestFil.Wr_String(0,"LibNam;ClsNam;VarNam2;DD;4;2");
  oTestFil.Wr_String(0,"LibNam;ClsNam;VarNam3;DD;4;2");
  oTestFil.Wr_String(0,"LibNam;ClsNam;VarNam4;DD;4;2");
  oTestFil.fcloseFil(0);

  // iStat = oVarDefTypFil.GetHeaderStr(0,"VarDefTyps.csv",&oHeaderStr);
  // assert(iStat == 0);
  // assert(oHeaderStr.compare("VarNam1;VarNam2;VarNam3;VarNam4") == 0);


  return iStat;
}
//=============================================================================
