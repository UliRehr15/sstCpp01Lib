/**********************************************************************
 *
 * sstCpp01Lib - library for generating cpp code from Type.def file.
 * Hosted on github
 *
 * Copyright (C) 2016 Hans Ulrich Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstCpp01TypDefTab.cpp    23.03.18  Re.    23.03.18  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstMath01Lib.h>
#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstCpp01Lib.h>

//==============================================================================
sstCppTypDefTabCls::sstCppTypDefTabCls(sstMisc01PrtFilCls *poTmpPrt)
{
  sstStr01VarDefCls oStrType;
  DsVerw = new sstRec04Cls(sizeof(oStrType));
  this->poPrt = poTmpPrt;
}
//==============================================================================
sstCppTypDefTabCls::~sstCppTypDefTabCls()
{
  delete DsVerw;
}
//==============================================================================
int sstCppTypDefTabCls::LoadTypDefFromFile (int iKey, const std::string sTypDefFilNam)
{
  sstMisc01AscFilCls sImpFile;
  std::string sFileRow;
  sstMisc01FilNamCls oFilNam;
  std::string sDateStr;  // Generating Date
  std::string sFilStr;
  std::string sErrTxt;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefFncCls oVarDefFnc;
  dREC04RECNUMTYP dRecNo = 0;

  std::string cFilNam;     // Filename without ending
  std::string cFilNamEnd;  // Filename with ending
  std::string cFilEnd;     // Filename ending

  int iRet = 0;
  int iStat1 = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Open Casc Object for reading
  cFilNamEnd = sTypDefFilNam;
  iStat = sImpFile.fopenRd( 0, cFilNamEnd.c_str());
  if (iStat < 0)
  {
    printf("Can not open file: %s\n", cFilNamEnd.c_str());
    // poPrt->SST_PrtZu(0);
    return -1;
  }

  // Split filenamestring to name and ending.
  iStat = oFilNam.SplitExtension( 0, &cFilNamEnd, &cFilEnd, &cFilNam);

  // Set Date of all source and header files
  sDateStr = "06.07.16";

  // Eine Zeile aus Ascii-Datei lesen.
  iStat1 = sImpFile.Rd_StrDS1( 0, &sFileRow);

  while (iStat1 >= 0)
  {

    if (dRecNo >= 3029)
    {
      iStat = 0;
    }
    // Copy string to Str1 structure.
    sFilStr = sFileRow;

    // interpret file row as cpp type dataset
    iStat = oVarDefFnc.ReadCSV ( 0, &sFilStr, &sErrTxt, &oStrType);
    if (iStat < 0)
    {
      poPrt->SST_PrtWrtInt4( 1,dRecNo+1,(char*)"Row Number: ");
      poPrt->SST_PrtWrtChar(1, (char*)sErrTxt.c_str(),(char*) "Could not interpret: ");
      // poPrt->SST_PrtZu(0);
      return -1;
    }
    // assert(iStat==0);

    // Weiteren User-Datensatz in Datenspeicher schreiben.
    iStat = DsVerw->WritNew( 0, &oStrType, &dRecNo);

    sFileRow.clear();

    // Eine Zeile aus Ascii-Datei lesen.
    iStat1 = sImpFile.Rd_StrDS1( 0, &sFileRow);
  }

  // CascObjekt beenden und zugehörige Datei schließen.
  iStat = sImpFile.fcloseFil(0);

  // Get Systemname from last record of TypeDef File.
  this->sSysNam = oStrType.Get_SysNam();

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//==============================================================================
std::string sstCppTypDefTabCls::getSysNam() const
{
  return this->sSysNam;
}
//==============================================================================
dREC04RECNUMTYP sstCppTypDefTabCls::count()
{
  return this->DsVerw->count();
}
//==============================================================================
int sstCppTypDefTabCls::Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr)
{
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->DsVerw->Read( iKey, dRecNo, vRecAdr);

  return iStat;
}
//==============================================================================
