// sst_generate_qttab_lib2.cpp    08.02.18 Re.    08.02.18  Re.
//
// program generates Qt Table lib code.
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

#include "sst_generate_fnc_lib.h"

//=============================================================================
sstCppGenFncLibCls::sstCppGenFncLibCls()
{

}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_Constructor(int iKey,
                                            sstCpp01_Class_Cls *oCppFncClass,
                                            dREC04RECNUMTYP    *lSatzNr)
{
  if (iKey != 0) return -1;
  std::string oTmpStr;
  oTmpStr = oCppFncClass->GetSysNam() + "Typ" + oCppFncClass->GetClsNam() + "Cls";
  oCppFncClass->writeBlcRow(0,lSatzNr,"  " + oTmpStr + " oDatRec;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  this->poRecTab = new sstRec04Cls(sizeof(oDatRec));");
  return 0;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_Destructor(int iKey,
                                           sstCpp01_Class_Cls *oCppFncClass,
                                           dREC04RECNUMTYP    *lSatzNr)
{
  if (iKey != 0) return -1;
  oCppFncClass->writeBlcRow(0,lSatzNr,"  delete this->poRecTab;");
  return 0;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_LoadTabFromCsv (int               iKey,
//                                    sstStr01Cls *oFormatInfo,
//                                                sstStr01VarDefCls  oClsMemDef,
                                    sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;
  std::string oTypNamStr;
  oTypNamStr = oCppTypClass->GetSysNam() + oCppTypClass->GetGrpNam() + oCppTypClass->GetClsNam() + "Cls";
  //oTypNamStr = oClsMemDef.Get_SysNam() + "Typ" + oClsMemDef.Get_ObjNam() + "Cls";

  oCppFncClass->writeBlcRow(0,lSatzNr,"  " + oTypNamStr + " oDatRec;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  sstMisc01AscFilCls oCsvFil;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  std::string oFrmtVersStr;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  std::string oCsvRecStr;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  int iStat1 = 0;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  int iRet = 0;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"//------------------------------------------------------------------------------");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if ( iKey != 0) return -1;");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  // Open Csv file");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = oCsvFil.fopenRd(0, (char*) oCsvFilNam.c_str());");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if (iStat < 0) return -2;  // Read open error");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  // Read first/title row");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = oCsvFil.Rd_StrDS1( 0, &oFrmtVersStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if (iStat < 0) return -3;  // file empty or not readable");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  // compare file version of object with file title row");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if ( oDatRec.getStringName().compare(oFrmtVersStr) != 0) return -4;");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  // read second row / first data row");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat1 = oCsvFil.Rd_StrDS1( 0, &oCsvRecStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  while (iStat1 >= 0)");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat = oDatRec.Csv_Read( 0, sErrTxt ,&oCsvRecStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    assert(iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    dREC04RECNUMTYP dRecNo = 0;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat = this->Write( 0, &dRecNo, &oDatRec);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    assert(iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat1 = oCsvFil.Rd_StrDS1( 0, &oCsvRecStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iRet = oCsvFil.fcloseFil(0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  assert (iRet >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_SaveTabToCsv (int               iKey,
//                                    sstStr01Cls *oFormatInfo,
//                                              sstStr01VarDefCls  oClsMemDef,
                                    sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  std::string oTypNamStr;
  oTypNamStr = oCppTypClass->GetSysNam() + oCppTypClass->GetGrpNam() + oCppTypClass->GetClsNam() + "Cls";
  // oTypNamStr = oClsMemDef.Get_SysNam() + "Typ" + oClsMemDef.Get_ObjNam() + "Cls";

  oCppFncClass->writeBlcRow(0,lSatzNr,"  " + oTypNamStr + " oDatRec;  // object data record");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  std::string oFrmtVersStr;");

  oCppFncClass->writeBlcRow(0,lSatzNr,"  sstMisc01AscFilCls oCsvFil;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  int iRet = 0;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"//------------------------------------------------------------------------------");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if ( iKey != 0) return -1;");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = oCsvFil.fopenWr(0, (char*) oCsvFilNam.c_str());");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  if (iStat < 0) return -2;");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  // Write Title Row / Version string to csv file");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  oFrmtVersStr = oDatRec.getStringName();");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  oCsvFil.Wr_String(0,oFrmtVersStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  dREC04RECNUMTYP dRecNums = this->poRecTab->count();");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  for (dREC04RECNUMTYP ll = 1; ll <= dRecNums; ll++)");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat = this->Read( 0, ll, &oDatRec);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    assert(iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    std::string oCsvStr;");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    oDatRec.Csv_Write( 0, &oCsvStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    oCsvFil.Wr_String( 0, oCsvStr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  iRet = oCsvFil.fcloseFil(0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  assert (iRet >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_Count (int               iKey,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  return this->poRecTab->count();");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_Read (int               iKey,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = this->poRecTab->Read( iKey, dRecNo, vRecAdr);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  assert (iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_Write (int               iKey,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  if (*dRecNo == 0)");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat = this->poRecTab->WritNew(iKey,vRecAdr,dRecNo);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    assert(iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  else");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    iStat = this->poRecTab->Writ( iKey, vRecAdr, *dRecNo);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"    assert (iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr,"  }");

  // oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = this->poRecTab->Writ( iKey, vRecAdr, *dRecNo);");
  // oCppFncClass->writeBlcRow(0,lSatzNr,"  assert (iStat >= 0);");
  oCppFncClass->writeBlcRow(0,lSatzNr," ");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_ReadDb (int                  iKey,
                                        sstStr01VarDefCls    oClsMemDef,
                                        sstCpp01_Class_Cls  *oCppFncClass,
                                        dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = -1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_WriteDb (int                  iKey,
                                        sstStr01VarDefCls    oClsMemDef,
                                        sstCpp01_Class_Cls  *oCppFncClass,
                                        dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = -1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_CountDb (int                  iKey,
                                        sstStr01VarDefCls    oClsMemDef,
                                        sstCpp01_Class_Cls  *oCppFncClass,
                                        dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = -1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_DatabaseWrite (int                  iKey,
                                               sstStr01VarDefCls  oClsMemDef,
                                               sstCpp01_Class_Cls  *oCppFncClass,
                                               dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_LoadFromCsvFiles (int                  iKey,
                                                  sstStr01VarDefCls  oClsMemDef,
                                                  sstCpp01_Class_Cls  *oCppFncClass,
                                                  dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = 1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_SaveToCsvFiles (int                  iKey,
                                                sstStr01VarDefCls  oClsMemDef,
                                                sstCpp01_Class_Cls  *oCppFncClass,
                                                dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_LoadAllFromMainFile (int                  iKey,
                                                     sstStr01VarDefCls  oClsMemDef,
                                                     sstCpp01_Class_Cls  *oCppFncClass,
                                                     dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = 1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_SaveAllToMainFile (int                  iKey,
                                                   sstStr01VarDefCls  oClsMemDef,
                                                   sstCpp01_Class_Cls  *oCppFncClass,
                                                   dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  return iStat;
}
//=============================================================================
void sstCppGenFncLibCls::setGrpNam(const std::string &sTmpGrpNam)
{
  this->sGrpNam = sTmpGrpNam;
}
//=============================================================================
std::string sstCppGenFncLibCls::getGrpNam() const
{
  return this->sGrpNam;
}
//=============================================================================
