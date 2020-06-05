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
// sstCpp01Lib.cpp    15.08.16  Re.    15.08.16  Re.
//
// generate cpp class and header files
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>

#include "sstCpp01Lib.h"
#include "sstCpp01LibInt.h"

//=============================================================================
sstCpp01_ClsTyp_Cls::sstCpp01_ClsTyp_Cls()
{
 this->eClsVisiTyp = myClsUnknown;
}
//=============================================================================
sstCpp01_ClsFnc_Cls::sstCpp01_ClsFnc_Cls()
{
  memset(this->cClsNam,0,sizeof(this->cClsNam));
  memset(this->cFncNam,0,sizeof(this->cFncNam));
  memset(this->cRetNam,0,sizeof(this->cRetNam));
  memset(this->cFncPar,0,sizeof(this->cFncPar));
  memset(this->cFncCom,0,sizeof(this->cFncCom));
  this->bIsConstFunc = false;
  lBlcStart = 0;                         /**< lBlcStart in Codeblock Table   */
  lBlcRows  = 0;
}
//=============================================================================
bool sstCpp01_ClsFnc_Cls::getIsConstFunc() const
{
    return bIsConstFunc;
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setIsConstFunc(bool value)
{
    bIsConstFunc = value;
}
//=============================================================================
std::string sstCpp01_ClsFnc_Cls::getClsNam()
{
  return this->cClsNam;
}
//=============================================================================
std::string sstCpp01_ClsFnc_Cls::getFncNam()
{
  return this->cFncNam;
}
//=============================================================================
std::string sstCpp01_ClsFnc_Cls::getRetNam()
{
  return this->cRetNam;
}
//=============================================================================
std::string sstCpp01_ClsFnc_Cls::getFncPar()
{
  return this->cFncPar;
}
//=============================================================================
std::string sstCpp01_ClsFnc_Cls::getFncCom()
{
  return this->cFncCom;
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setClsNam(const std::string oClsNamStr)
{
  strncpy( this->cClsNam, oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setFncNam(const std::string oFncNamStr)
{
  strncpy( this->cFncNam, oFncNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setRetNam(const std::string oRetNamStr)
{
  strncpy( this->cRetNam, oRetNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setFncPar(const std::string oFncParStr)
{
  strncpy( this->cFncPar, oFncParStr.c_str(), dCPPFILROWLENGTH);
}
//=============================================================================
void sstCpp01_ClsFnc_Cls::setFncCom(const std::string oFncComStr)
{
  strncpy( this->cFncCom, oFncComStr.c_str(), dCPPFILROWLENGTH);
}
//=============================================================================
sstCpp01_Class_Cls::sstCpp01_Class_Cls()
{
    this->ClsBlcDsVerw = NULL;
    this->ClsFncDsVerw = NULL;
  this->ClsTypDsVerw = NULL;
  memset(this->cClsNam,0,sizeof(this->cClsNam));
  memset(this->cSysNam,0,sizeof(this->cSysNam));
  memset(this->cGrpNam,0,sizeof(this->cGrpNam));
  this->sDateStr.clear();
  this->sExtBaseCls.clear();
}
//=============================================================================
int sstCpp01_Class_Cls::SetDate(int iKey, std::string sLocDateStr)
{
  // int iStat = 0;
  if ( iKey != 0) return -1;
  this->sDateStr = sLocDateStr;
  return 0;
}
//=============================================================================
int sstCpp01_Class_Cls::GetDate(int iKey, std::string *sLocDateStr)
{
  // int iStat = 0;
  if ( iKey != 0) return -1;
  *sLocDateStr = this->sDateStr;
  return 0;
}
//==============================================================================
int sstCpp01_Class_Cls::SetClsNam(int iKey, std::string oClsNam)
{
  if ( iKey != 0) return -1;
  strncpy(this->cClsNam,oClsNam.c_str(),dSST_STR01_VAR_NAM_LEN);
  return 0;
}
//==============================================================================
int sstCpp01_Class_Cls::SetSysNam(int iKey, std::string oSysNam)
{
  if ( iKey != 0) return -1;
  strncpy(this->cSysNam,oSysNam.c_str(),dSST_STR01_VAR_NAM_LEN);
  return 0;
}
//==============================================================================
int sstCpp01_Class_Cls::SetGrpNam(int iKey, std::string oGrpNam)
{
  if ( iKey != 0) return -1;
  strncpy(this->cGrpNam,oGrpNam.c_str(),dSST_STR01_VAR_NAM_LEN);
  return 0;
}
//==============================================================================
std::string sstCpp01_Class_Cls::GetSysNam()
{
  return this->cSysNam;
}
//==============================================================================
std::string sstCpp01_Class_Cls::GetGrpNam()
{
  return this->cGrpNam;
}
//==============================================================================
std::string sstCpp01_Class_Cls::GetClsNam()
{
  return this->cClsNam;
}
//==============================================================================
std::string sstCpp01_Class_Cls::GetLibClsNam()
{
  std::string oFullClsNam;
  std::string oSysNam;
  std::string oGrpNam;
  std::string oClsNam;
  oSysNam = this->cSysNam;
  oGrpNam = this->cGrpNam;
  oClsNam = this->cClsNam;
  oFullClsNam = oSysNam + oGrpNam + oClsNam + "Cls";
  return oFullClsNam;
}
//==============================================================================
int sstCpp01_Class_Cls::HeadWrtTypDefInfo(int                 iKey,
                                          sstMisc01AscFilCls *sHedFil)
{
  sstCpp01_ClsTyp_Cls oVarDefRec;
  sstStr01VarDefFncCls oVarDefCsv;
  std::string oCsvStr;
  std::string oErrStr;

  if ( iKey != 0) return -1;

  if (this->ClsTypDsVerw->count() <= 0) return -2;

  sHedFil->Wr_String(0,"* Used Type Definitions");
  for (dREC04RECNUMTYP ii=1;ii <= this->ClsTypDsVerw->count();ii++)
  {
    this->ClsTypDsVerw->Read( 0, ii, &oVarDefRec);
    oVarDefCsv.WriteCSV(0,oVarDefRec.sClsMem,&oErrStr,&oCsvStr);
    sHedFil->Wr_String(0,"* " + oCsvStr);
  }
  sHedFil->Wr_String(0,"*");

  return 0;
}
//=============================================================================
unsigned int sstCpp01_Class_Cls::getNumberOfMember()
{
  dREC04RECNUMTYP dNumTypRecsAct = this->ClsTypDsVerw->count();
  return (unsigned int) dNumTypRecsAct;
}
//=============================================================================
std::string sstCpp01_Class_Cls::getMemberNameStr()
{
  return "getMemberNameStr";
}
//=============================================================================
std::string sstCpp01_Class_Cls::getMemberTypeStr()
{
  return "getMemberTypeStr";
}
//=============================================================================
std::string sstCpp01_Class_Cls::getExtBaseCls() const
{
  return sExtBaseCls;
}
//=============================================================================
void sstCpp01_Class_Cls::setExtBaseCls(const std::string &value)
{
  sExtBaseCls = value;
}
//=============================================================================
int sstCpp01_Class_Cls::writeBlcRow(int iKey, dREC04RECNUMTYP *lSatzNr, const std::string sRowStr)
{
  if ( iKey != 0) return -1;
  int iStat = 0;
  sstCpp01_FilRowCls sBlcRow;

  sBlcRow.setRow(sRowStr);
  iStat = this->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  return iStat;
}
//=============================================================================
void sstCpp01_Class_Cls::setQtMocMacroStr(const std::string &value)
{
    oQtMocMacroStr = value;
}
//=============================================================================
std::string sstCpp01_Class_Cls::getQtMocMacroStr() const
{
  return oQtMocMacroStr;
}
//=============================================================================
sstCpp01_FilRowCls::sstCpp01_FilRowCls()
{
  memset(this->cCharRow,0,dCPPFILROWLENGTH);
}
//=============================================================================
void sstCpp01_FilRowCls::setRow(std::string oTmpStr)
{
  strncpy(this->cCharRow, oTmpStr.c_str(), dCPPFILROWLENGTH);
}
//=============================================================================
std::string sstCpp01_FilRowCls::getRow()
{
  return this->cCharRow;
}
//=============================================================================
int sstCpp01_Fil_wrt_head (int             iKey,
                         sstMisc01AscFilCls *sExpFile,
                         std::string           *cFilDat)
//-----------------------------------------------------------------------------
{
  // std::string sFilRow;
  std::string sFilRow;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Write following line in header/class file:

  // Blanko.h   29.04.10  Re.   29.04.10  Re.

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "//  ";
  sFilRow = sFilRow + sExpFile->GetFileName();
  sFilRow = sFilRow + "   ";
  sFilRow = sFilRow + *cFilDat;
  sFilRow = sFilRow + "  Re.   ";
  sFilRow = sFilRow + *cFilDat;
  sFilRow = sFilRow + "  Re.";
  iStat = sExpFile->Wr_StrDS1(0, &sFilRow);

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
int sstCpp01_Hed_WrtCom (int                 iKey,
                         sstMisc01AscFilCls *poExpFile,
                         const std::string   oSysNam,
                         const std::string   oGrpNam)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  if (oSysNam.length() == 0) return -2;
  if (oGrpNam.length() == 0) return -3;


  // Write empty row to Asc-File.
  iStat = poExpFile->wr_txt( 0, (char*)"//");

  // Write Casc-Line-Object to Casc-File.
  sFilRow.clear();
  sFilRow = "//  Definitions of class \"";
  sFilRow = sFilRow + oSysNam + oGrpNam;
  sFilRow = sFilRow + "\"";
  iStat = poExpFile->Wr_StrDS1( 0, &sFilRow);

  // Write comment row to Asc-File.
  iStat = poExpFile->wr_txt( 0, (char*)"//");

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
int sstCpp01_Cls_WrtInc (int                  iKey,
                         sstMisc01AscFilCls  *sExpFile,
                         sstCpp01_Class_Cls  *oCppClass,
                         std::string    oAddFilNamList)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  std::string sFncGrpNam;
  std::string cLocObjNam;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;
  if(oCppClass->GetSysNam().length() == 0) return -2;
  if(oCppClass->GetGrpNam().length() == 0) return -3;

//  //
//  // A lot of Function-Examples
//  //
//  // 16.04.10: a change-description

//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <string.h>
//  #include <assert.h>

//  #include <KERN.H>
//  #include <mathem.h>
//  #include <str_lib.h>
//  #include <sstlib.h>

//  #include "BLANKO.H"

  // Save function group name ( dxf_fnc, dxf_typ)from filename
  sFncGrpNam = sExpFile->GetFileName();

  size_t lPos =  sFncGrpNam.find(".cpp");
  // if(pStr != NULL)
  if(lPos != sFncGrpNam.npos)
  {
    // In String durch Adresse und Lдnge bezeichneten Substring austauschen.
    sFncGrpNam.erase(lPos,lPos+4);
  }

  sFncGrpNam = oCppClass->cSysNam + oCppClass->GetGrpNam();

  // Write comment row to Asc-File.
  iStat = sExpFile->wr_txt(0,(char*) "//");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "//  Functions for Class \"";
  sFilRow = sFilRow + sFncGrpNam;
  sFilRow = sFilRow +"\"";
  iStat = sExpFile->Wr_StrDS1(0, &sFilRow);

  iStat = sExpFile->wr_txt(0, (char*)"//");
  iStat = sExpFile->wr_txt(0, (char*)" ");
  iStat = sExpFile->wr_txt(0, (char*)"#include <stdio.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <stdlib.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <string.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <assert.h>");
  iStat = sExpFile->wr_txt(0, (char*)" ");
  iStat = sExpFile->wr_txt(0, (char*)"#include <string>");
  iStat = sExpFile->wr_txt(0, (char*)" ");
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstStr01Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstMath01Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstMisc01Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstRec04Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)" ");

  if (oAddFilNamList.length() > 0)
  {  // Add more Include-Files

    sstStr01Cls oStrCnvt;
    std::string oLocFilNam;
    int iStat1 = 0;

    iStat1 = oStrCnvt.CsvString2_Str ( 0, &oAddFilNamList, &oLocFilNam);

    while (iStat1 >= 0)
    {
      // Write Casc-Line-Object to Casc-File.
      sFilRow = "#include <";
      sFilRow = sFilRow + oLocFilNam;
      sFilRow = sFilRow + ">";
      iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

      iStat1 = oStrCnvt.CsvString2_Str ( 0, &oAddFilNamList, &oLocFilNam);
    }
    iStat = sExpFile->wr_txt(0, (char*)" ");

  }

  // write class include
  // typ include or typ/fnc include
  // cLocObjNam = sFncGrpNam + "Lib";
  cLocObjNam = sFncGrpNam + oCppClass->GetGrpNam() + "Lib";

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "#include \"";
  sFilRow = sFilRow + cLocObjNam;
  sFilRow = sFilRow + ".h\"";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

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
int sstCpp01_Hed_wrt_def_open (int             iKey,
                             sstMisc01AscFilCls *sExpFile,
                             std::string           cLibNam,
                             std::string           cSysNam,
                             std::string           cGrpNam,
                             std::string           cObjNam)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  std::string sTxt;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Str1_CopyStr( 0, &sTxt, sExpFile->Nam);
  sTxt = sExpFile->GetFileName();

  size_t dPos = sTxt.find(".h");
  if(dPos != sTxt.npos)
  {
    // In String durch Adresse und Lдnge bezeichneten Substring austauschen.
    sTxt.erase(dPos,2);
  }

//#ifndef   _BLANKO_HEADER
//#define   _BLANKO_HEADER

  // Write empty row to Asc-File.
  iStat = sExpFile->wr_txt(0, (char*)"  ");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "#ifndef   _";
  sFilRow = sFilRow + cLibNam;  // SST
  sFilRow = sFilRow + "_";
  sFilRow = sFilRow + cSysNam;  // DXF, CSV ...
  sFilRow = sFilRow + "_";
  sFilRow = sFilRow + cGrpNam;  // TYP or FNC or ...

  if(cObjNam.length() >  0)
  {
    sFilRow = sFilRow + "_";
    sFilRow = sFilRow + cObjNam;  // CLASS NAME
  }
  sFilRow = sFilRow + "_HEADER";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "#define   _";
  sFilRow = sFilRow + cLibNam;  // SST
  sFilRow = sFilRow + "_";
  sFilRow = sFilRow + cSysNam;  // DXF, CSV ...
  sFilRow = sFilRow + "_";
  sFilRow = sFilRow + cGrpNam;  // TYP or FNC or ...
  if( cObjNam.length() > 0)
  {
    sFilRow = sFilRow + "_";
    sFilRow = sFilRow + cObjNam;  // CLASS NAME
  }
  sFilRow = sFilRow + "_HEADER";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // Write empty row to Asc-File.
  iStat = sExpFile->wr_txt(0, (char*)"  ");

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
int sstCpp01_Hed_wrt_def_close (int             iKey,
                              sstMisc01AscFilCls *sExpFile)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

// #endif
//
//// ------------------------------------------------------------------- Ende ----

  // Write empty row to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)" ");

  // Write rows to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)"#endif");
  iStat = sExpFile->wr_txt( 0, (char*)"//");
  iStat = sExpFile->wr_txt( 0, (char*)"// --------------------------------------------------------------- File End ----");

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
int sstCpp01_Hed_wrt_class_info (int                  iKey,
                                 sstMisc01AscFilCls  *sExpFile,
                                 std::string         *cGrpNam,
                                 sstCpp01_Class_Cls  *poCppClass,
                                 std::string         *cClsDat)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  dREC04RECNUMTYP  AnzDs=0;
  sstCpp01_ClsTyp_Cls oTypDef;
  std::string cObjNam;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // get class information or class name
  AnzDs = poCppClass->ClsTypDsVerw->count();

  if (AnzDs <= 1)
  {
    cObjNam = poCppClass->GetClsNam();
  }
  else
  {
    // Record 1 is constructor
    // Record 2 is first class element
    iStat = poCppClass->ClsTypDsVerw->Read( 0, 2, &oTypDef);
    cObjNam = oTypDef.sClsMem.Get_ObjInfo();
  }

//  //==============================================================================
//  /**
//  * @brief Definition Klasse X
//  *
//  * More Comment
//  *
//  * Changed: 19.02.10  Re.
//  *
//  * @ingroup examples
//  *
//  * @author Re.
//  *
//  * @date 19.02.10
//  */
//  // ----------------------------------------------------------------------------


  // Write empty row to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)" ");

  // Write rows to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)"//==============================================================================");
  iStat = sExpFile->wr_txt( 0, (char*)"/**");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* @brief "  + poCppClass->GetGrpNam() + " Class ";
  sFilRow = sFilRow + poCppClass->GetSysNam() + poCppClass->GetGrpNam() + cObjNam + "Cls";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"*");
  iStat = sExpFile->wr_txt( 0, (char*)"* More Comment");
  iStat = sExpFile->wr_txt( 0, (char*)"*");

  poCppClass->HeadWrtTypDefInfo( 0, sExpFile);

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* Changed: ";
  sFilRow = sFilRow + *cClsDat;
  sFilRow = sFilRow + "  Re.";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // iStat = casc_wr_txt ( 0, sExpFile, (char*)"*");
  iStat = sExpFile->wr_txt( 0, (char*)"*");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* @ingroup ";
  sFilRow = sFilRow + *cGrpNam +"Lib";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"*");
  iStat = sExpFile->wr_txt( 0, (char*)"* @author Re.");
  iStat = sExpFile->wr_txt( 0, (char*)"*");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* @date ";
  sFilRow = sFilRow + *cClsDat;
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"*/");
  iStat = sExpFile->wr_txt( 0, (char*)"// ----------------------------------------------------------------------------");

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
int sstCpp01_Hed_wrt_inc(int                  iKey,
                         sstMisc01AscFilCls  *oHedFil,
                         std::string          oAddFilNamList)
{
  if ( iKey != 0) return -1;

  std::string sFilRow;
  int iStat = 0;

  iStat = oHedFil->wr_txt(0, (char*)" ");
  iStat = oHedFil->wr_txt(0, (char*)"#include <stdio.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <stdlib.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <string.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <assert.h>");
  iStat = oHedFil->wr_txt(0, (char*)" ");
  iStat = oHedFil->wr_txt(0, (char*)"#include <string>");
  iStat = oHedFil->wr_txt(0, (char*)" ");
  iStat = oHedFil->wr_txt(0, (char*)"#include <sstStr01Lib.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <sstMath01Lib.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <sstMisc01Lib.h>");
  iStat = oHedFil->wr_txt(0, (char*)"#include <sstRec04Lib.h>");
  iStat = oHedFil->wr_txt(0, (char*)" ");

  if (oAddFilNamList.length() > 0)
  {  // Add more Include-Files

    sstStr01Cls oStrCnvt;
    std::string oLocFilNam;
    int iStat1 = 0;

    iStat1 = oStrCnvt.CsvString2_Str ( 0, &oAddFilNamList, &oLocFilNam);

    while (iStat1 >= 0)
    {
      // Write Casc-Line-Object to Casc-File.
      sFilRow = "#include <";
      sFilRow = sFilRow + oLocFilNam;
      sFilRow = sFilRow + ">";
      iStat = oHedFil->Wr_StrDS1( 0, &sFilRow);

      iStat1 = oStrCnvt.CsvString2_Str ( 0, &oAddFilNamList, &oLocFilNam);
    }
    iStat = oHedFil->wr_txt(0, (char*)" ");

  }
  return iStat;
}
//=============================================================================
int sstCpp01_Hed_wrt_defgroup (int                 iKey,
                               sstMisc01AscFilCls *sExpFile,
                               std::string         cGrpNam)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  /**
   * @defgroup sstRecord04Lib sstRecord04Lib: cpp sst record library (Version 4)
   *
   * cpp sst record library <BR>
   *
   */

  iStat = sExpFile->Wr_String( 0,"/**");
  iStat = sExpFile->Wr_String( 0," * @defgroup "+ cGrpNam + "Lib "+ cGrpNam + "Lib");
  iStat = sExpFile->Wr_String( 0," *");
  iStat = sExpFile->Wr_String( 0," * Description: "+ cGrpNam + "Lib");
  iStat = sExpFile->Wr_String( 0," *");
  iStat = sExpFile->Wr_String( 0," */");

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
int sstCpp01_Hed_wrt_class (int               iKey,
                          sstMisc01AscFilCls   *sExpFile,
                          sstCpp01_Class_Cls *oCppCls)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  dREC04RECNUMTYP lClsTypNum = 0;
  dREC04RECNUMTYP  lFuncNum = 0;

  sstCpp01_ClsTyp_Cls oCppClsTyp;
  sstCpp01_ClsFnc_Cls oCppClsFnc;

  std::string cTypeChar;
  std::string sZeile;

  sstStr01Cls oStrCnvt;
  int iLocIntWidth = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;

  //  class X
  //  {
  //    public:   // Public functions
  //       X();  // Constructor
  //      ~X();  // Destructor
  //    private:  // Private functions
  //    int Dum;        /**< Dummy */
  //  };


  // Write Casc-Line-Object to Casc-File.
  sFilRow = "class ";
  sFilRow = sFilRow + oCppCls->GetLibClsNam();

// Insert Base Class
  if(iKey == 1)
  {
    if (oCppCls->getExtBaseCls().length() > 0)
    { // inherits extern base class
      sFilRow = sFilRow + " : public ";
      sFilRow = sFilRow + oCppCls->getExtBaseCls();
    }
    else
    {
      // inherits generated base class
      sFilRow = sFilRow + " : public ";
      sFilRow = sFilRow + oCppCls->cSysNam;
      sFilRow = sFilRow + oCppCls->cGrpNam;
      sFilRow = sFilRow + "BaseCls";
    }

  }
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"{");

  // Write Qt Moc Macro Str to Class header
  if (oCppCls->getQtMocMacroStr().length() > 0)
  {
    sExpFile->Wr_String(0,"  " + oCppCls->getQtMocMacroStr());
  }

  // Get number of stored class functions ( include constructor)
  lFuncNum = oCppCls->ClsFncDsVerw->count();

  // Get number of stored class members
  lClsTypNum = oCppCls->ClsTypDsVerw->count();

  //=== PUBLIC ================================================================

  iStat = sExpFile->wr_txt( 0, (char*)"  public:  // Public functions");

  // write all class functions to header file
  for (dREC04RECNUMTYP ii = 1; ii <= lFuncNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oCppCls->ClsFncDsVerw->Read( 0, ii, &oCppClsFnc);

    if (oCppClsFnc.eClsVisiTyp != myClsPublic) break;

    //==============================================================================
    /**
    * @brief // Set system name to class object <BR>
    * iStat = oCppClass.SetSysNam( iKey, &oSysNam);
    *
    * @param iKey    [in] For the moment 0
    * @param oSysNam [in] Set system name
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------

    std::string oTmpStr = oCppClsFnc.getFncCom() + " " + oCppClsFnc.getFncNam();
    std::string oParPairStr;  // Parameter String
    std::string oParStr;  // Parameter String
    sExpFile->Wr_String(0,"    //==============================================================================");
    sExpFile->Wr_String(0,"    /**");
    sExpFile->Wr_String(0,"    * @brief // " + oTmpStr + " <BR>");

    oTmpStr = oCppClsFnc.cFncPar;
    if (oTmpStr.length() > 0)
    {
      sstStr01Cls oCnvtParStr1;
      oCnvtParStr1.SetSeparator(0,(char*) ",");
      int iStat1 = 0;
      iStat1 = oCnvtParStr1.CsvString2_Str( 0, &oTmpStr, &oParPairStr);
      while (iStat1 == 0)
      {
        sstStr01Cls oCnvtParStr2;
        oCnvtParStr2.SetSeparator(0,(char*) " ");
        oCnvtParStr2.SetNoInfoChar( 0,(char*) "\0");
        iStat = oCnvtParStr2.CsvString2_Str(0,&oParPairStr,&oParStr);
        iStat = oCnvtParStr2.CsvString2_Str(0,&oParPairStr,&oParStr);
        sExpFile->Wr_String(0,"    * @param "+ oParStr);
        iStat1 = oCnvtParStr1.CsvString2_Str( 0, &oTmpStr, &oParPairStr);
      }
    }

    sExpFile->Wr_String(0,"    */");
    sExpFile->Wr_String(0,"    // -----------------------------------------------------------------------------");

    // Fill Return Type
    sstStr01VarTypeCls oVarType;
    oVarType.Enm2FullStr( 0, oCppClsFnc.eCppType, &cTypeChar);

    // Insert custom return type name
    if (oCppClsFnc.eCppType == sstStr01Custom)
    {
      cTypeChar = oCppClsFnc.cRetNam;
    }

    sFilRow = "    ";
    sFilRow = sFilRow + cTypeChar;
    if (cTypeChar.length() > 0) sFilRow = sFilRow + " ";

    sFilRow = sFilRow + oCppClsFnc.cFncNam;  // Name of Function
    sFilRow = sFilRow + "(";
    sFilRow = sFilRow + oCppClsFnc.cFncPar;  // List of parameters
    sFilRow = sFilRow + ")";

    if (oCppClsFnc.getIsConstFunc())
    {
      sFilRow = sFilRow + " const";
    }
    sFilRow = sFilRow + ";";

    // Write comment information, if possible
    if (strlen(oCppClsFnc.cFncCom) > 0)  // Comment
    {
      sFilRow = sFilRow + "// ";
      sFilRow = sFilRow + oCppClsFnc.cFncCom;
    }
    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);
  }

  //---------------------------------------------------------------------------
  // write all type definitions to header file
  for (dREC04RECNUMTYP ii=1; ii <= lClsTypNum; ii++)
  {
    // Datensatz an absoluter Position lesen.
    iStat = oCppCls->ClsTypDsVerw->Read( 0, ii, &oCppClsTyp);

    if (oCppClsTyp.eClsVisiTyp != myClsPublic) break;

    sstStr01VarTypeCls oVarType;
    oVarType.Enm2FullStr( 0, oCppClsTyp.sClsMem.Get_Type(), &cTypeChar);


    // Write Casc-Line-Object to Casc-File.
    sFilRow = "    ";
    sFilRow = sFilRow + cTypeChar;
    sFilRow = sFilRow + " ";
    sFilRow = sFilRow + oCppClsTyp.sClsMem.Get_EleNam();

    iLocIntWidth = oCppClsTyp.sClsMem.Get_Width() + 1;

    if (oCppClsTyp.sClsMem.Get_Type() == sstStr01Char)
    {
      sFilRow = sFilRow + "[";

      sZeile.clear();

      // Int2 in einen String konvertieren und in Zeilenbereich kopieren.
      iStat = oStrCnvt.Csv_Int2_2String( 0, iLocIntWidth, &sZeile);

      sFilRow = sFilRow + sZeile;
      sFilRow = sFilRow + "]";
    }

    if (oCppClsTyp.sClsMem.Get_Type() == sstStr01Date)
    {
      sFilRow = sFilRow + "[";

      sZeile.clear();

      // Int2 in einen String konvertieren und in Zeilenbereich kopieren.
      iStat = oStrCnvt.Csv_Int2_2String( 0, iLocIntWidth, &sZeile);

      sFilRow = sFilRow + sZeile;
      sFilRow = sFilRow + "]";
    }

    sFilRow = sFilRow + ";";

    // append doxygen description
    if(oCppClsTyp.sClsMem.Get_EleInfo().length() > 0)
    {
      sFilRow = sFilRow + "  /**< ";
      sFilRow = sFilRow + oCppClsTyp.sClsMem.Get_EleInfo();
      sFilRow = sFilRow + " */";
    }

    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  }

  //=== PROTECTED =============================================================
  //=== PRIVATE =============================================================

  iStat = sExpFile->wr_txt( 0, (char*)"  private:");

  // write all class functions to header file
  for (dREC04RECNUMTYP ii = 1; ii <= lFuncNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oCppCls->ClsFncDsVerw->Read( 0, ii, &oCppClsFnc);

    if (oCppClsFnc.eClsVisiTyp != myClsPrivate) break;

    sstStr01VarTypeCls oVarType;
    iStat = oVarType.Enm2Str( 0, oCppClsFnc.eCppType, &cTypeChar);

    sFilRow = "    ";
    sFilRow = sFilRow + cTypeChar;
    if (cTypeChar.length() > 0) sFilRow = sFilRow + " ";
    sFilRow = sFilRow + oCppClsFnc.cFncNam;
    sFilRow = sFilRow + "(";
    sFilRow = sFilRow + oCppClsFnc.cFncPar;
    sFilRow = sFilRow + ");  // ";
    sFilRow = sFilRow + oCppClsFnc.cFncCom;
    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);
  }

  // write all type definitions to header file
  for (dREC04RECNUMTYP ii=1; ii <= lClsTypNum; ii++)
  {
    // Datensatz an absoluter Position lesen.
    iStat = oCppCls->ClsTypDsVerw->Read( 0, ii, &oCppClsTyp);

    if (oCppClsTyp.eClsVisiTyp != myClsPrivate) break;

    // write one type row to class definition in header file
    iStat = sstCpp01_Hed_ClsWrTypRow ( 0, &oCppClsTyp, sExpFile);

  }

//=============================================================================

  iStat = sExpFile->wr_txt( 0, (char*)"};");

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
int sstCpp01_WrtCls (int                 iKey,
                       sstMisc01AscFilCls    *sExpFile,
                       sstRec04Cls       *sBlcDsVerw,
                       sstCpp01_ClsFnc_Cls *oCppClsFnc)
//-----------------------------------------------------------------------------
{
  std::string cTypeChar;      // int long char float double bool
  std::string cTypeType;                     // i l c f d b
  std::string sFilRow;
  sstCpp01_FilRowCls sBlcTxt;  // one row inside function block
  std::string sBlcRow;
  std::string cRetVar;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Write empty row
  // iStat = sExpFile->wr_txt( 0, (char*)" ");

  // Write Line row
  iStat = sExpFile->wr_txt( 0, (char*)"//==============================================================================");

  // Write comment row
  sFilRow = "// ";
  sFilRow = sFilRow + oCppClsFnc->cFncCom;
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // Convert return type to char
  sstStr01VarTypeCls oVarType;
  iStat = oVarType.Enm2FullStr( 0, oCppClsFnc->eCppType, &cTypeChar);
  iStat = oVarType.Enm2ShortStr( 0, oCppClsFnc->eCppType, &cTypeType);

  // if return custom type, insert name
  if (oCppClsFnc->eCppType == sstStr01Custom)
  {
    cTypeChar = oCppClsFnc->cRetNam;
  }

  // Write Casc-Line-Object to Casc-File.
  sFilRow = cTypeChar;
  if (cTypeChar.length() > 0) sFilRow = sFilRow + " ";
  sFilRow = sFilRow + oCppClsFnc->cClsNam;
  sFilRow = sFilRow + "::";
  sFilRow = sFilRow + oCppClsFnc->cFncNam;
  sFilRow = sFilRow + "(";
  sFilRow = sFilRow + oCppClsFnc->cFncPar;
  sFilRow = sFilRow + ")";

  // is const function ?
  if (oCppClsFnc->getIsConstFunc())
  {
      sFilRow = sFilRow + " const";
  }
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // iStat = casc_wr_txt ( 0, sExpFile, (char*)"{");
  iStat = sExpFile->wr_txt( 0, (char*)"{");

  // if type is not void, write define var row ( int iStat ...)
  if (cTypeType.length() > 0)
  {
    cRetVar = cTypeType;
    cRetVar = cRetVar + "Stat";  // iStat, lStat ...

    sFilRow = "  ";
    sFilRow = sFilRow + cTypeChar;
    sFilRow = sFilRow + " ";
    sFilRow = sFilRow + cRetVar;

    switch (oCppClsFnc->eCppType)
    {
    case sstStr01UInt:
    case sstStr01ULong:
    case sstStr01Int:
    case sstStr01Long:   sFilRow = sFilRow + " = 0;";break;
    case sstStr01String:   sFilRow = sFilRow + ";";break;
    case sstStr01Char:   sFilRow = sFilRow + " = """";";break;
    case sstStr01Float:
    case sstStr01Double: sFilRow = sFilRow + " = 0.0;";break;
    case sstStr01Bool:   sFilRow = sFilRow + " = false;";break;
      default: break;
    }

    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);
  }

  cRetVar = cTypeType;
  cRetVar = cRetVar + "Stat";  // iStat, lStat ...

  // Die Anzahl der aktuell gespeicherten Datens\E4tze zur\FCckgeben.
  dREC04RECNUMTYP lBlcRowNum = 0;
  lBlcRowNum = sBlcDsVerw->count();

  dREC04RECNUMTYP lBlcStart = oCppClsFnc->lBlcStart;
  dREC04RECNUMTYP lBlcStop = oCppClsFnc->lBlcStart + oCppClsFnc->lBlcRows -1;

  if(lBlcRowNum > 0 && oCppClsFnc->lBlcRows > 0)
  {
    // Datensatz an absoluter Position lesen.
    for (dREC04RECNUMTYP ii = lBlcStart;ii <= lBlcStop; ii++)
    {
      iStat = sBlcDsVerw->Read( 0, ii, &sBlcTxt);
      sBlcRow = sBlcTxt.getRow();
      iStat = sExpFile->Wr_StrDS1( 0, &sBlcRow);

    }

  }
  else
  {
    iStat = sExpFile->wr_txt( 0, (char*)" ");
  }

  // if type is not void, write return row ( return iStat ...)
  if (cTypeType.length() > 0)
  {
    sFilRow = "  return";
    sFilRow = sFilRow + " ";
    sFilRow = sFilRow + cRetVar;
    sFilRow = sFilRow + ";";
    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);
  }

  iStat = sExpFile->wr_txt( 0, (char*)"}");

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
int sstCpp01_wrt2CppHedFil (int               iKey,
                       sstCpp01_Class_Cls *oCppClass)
//-----------------------------------------------------------------------------
{
  sstMisc01AscFilCls sExpFile;
  char cExpFilNam[MAX_PFAD];
  dREC04RECNUMTYP  AnzTypDs = 0;
  sstCpp01_ClsTyp_Cls oCppClsTyp;
  std::string cClassNam;
  std::string cLibNam;
  std::string sDateStr;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;

  // no class name, no action
  AnzTypDs = strlen(oCppClass->cClsNam);
  if (AnzTypDs <= 0) return -2;

  // save class name
  cClassNam = oCppClass->cClsNam;

  // build lib name
  cLibNam = oCppClass->cSysNam;
  cLibNam = cLibNam + "_Lib";

  // get cpp header file name out of classname
  strncpy( cExpFilNam, cLibNam.c_str(), MAX_PFAD);  // Filename is lib name 29.01.13  Re.
  strncat( cExpFilNam, ".h", MAX_PFAD);

  // open CascObject for writing.
  iStat = sExpFile.fopenWr( 0, cExpFilNam);

  iStat = oCppClass->GetDate(0,&sDateStr);

  // write headrows in cpp file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sExpFile, &sDateStr);

  // Write comment to cpp header file
  iStat = sstCpp01_Hed_WrtCom ( 0, &sExpFile, oCppClass->GetSysNam(), oCppClass->GetGrpNam());

  // write define open rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_open ( 0, &sExpFile, (char*)"SST",oCppClass->cSysNam,
                                                               oCppClass->cGrpNam,
                                                               oCppClass->cClsNam);

  // write class info block in cpp header file
  iStat = sstCpp01_Hed_wrt_class_info ( 0, &sExpFile, &cLibNam, oCppClass, &sDateStr);

  // Write one class definition in header file
  iStat = sstCpp01_Hed_wrt_class ( iKey, &sExpFile, oCppClass);

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sExpFile);

  // close CascObject and close underlying file
  iStat = sExpFile.fcloseFil(0);

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
int sstCpp01_wrt2CppHedFil2 (int               iKey,
                        sstMisc01AscFilCls   *sCppHedFil,
                        sstCpp01_Class_Cls *oCppClass)
//-----------------------------------------------------------------------------
{
  dREC04RECNUMTYP  AnzTypDs = 0;
  sstCpp01_ClsTyp_Cls oCppClsTyp;
  std::string cClassNam;
  std::string cLibNam;
  std::string sDateStr;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;

  // no class name, no action
  AnzTypDs = strlen(oCppClass->cClsNam);
  if (AnzTypDs <= 0) return -2;

  // save class name
  cClassNam = oCppClass->cClsNam;

  // build lib name
  cLibNam = oCppClass->cSysNam;
  // cLibNam = cLibNam + "_Lib";

  iStat = oCppClass->GetDate(0,&sDateStr);

  // write class info/doxygen block in cpp header file
  iStat = sstCpp01_Hed_wrt_class_info ( 0, sCppHedFil, &cLibNam, oCppClass, &sDateStr);

  // Write one class definition in header file
  iStat = sstCpp01_Hed_wrt_class ( iKey, sCppHedFil, oCppClass);

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
int sstCpp01_wrt2CppClsFil2 (int               iKey,
                        sstMisc01AscFilCls   *sCppClsFil,
                        sstCpp01_Class_Cls *oCppClass)
//-----------------------------------------------------------------------------
{
  dREC04RECNUMTYP  lFuncNum = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;

  // Get number of functions stored in dss
  lFuncNum = oCppClass->ClsFncDsVerw->count();
  if (lFuncNum <= 0) return -2;

  // if class is without name, error and return
  iStat = strlen(oCppClass->cClsNam);
  if (iStat <= 0) return -3;

  // write all class functions to cpp class file, constructor is first
  for (dREC04RECNUMTYP ii = 1; ii <= lFuncNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oCppClass->ClsFncDsVerw->Read( 0, ii, &oCppClsFnc);

    if (ii == 1 && oCppClass->getExtBaseCls().length() > 0)
    { // if in constructor and extern base class
      strncat(oCppClsFnc.cFncPar,(char*)"):",dCPPFILROWLENGTH);
      strncat(oCppClsFnc.cFncPar,oCppClass->getExtBaseCls().c_str(),dCPPFILROWLENGTH);
      strncat(oCppClsFnc.cFncPar,(char*)"(parent",dCPPFILROWLENGTH);

    }

    // Write one class function to file
    iStat = sstCpp01_WrtCls ( 0, sCppClsFil, oCppClass->ClsBlcDsVerw, &oCppClsFnc);

  }

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
int sstCpp01_CsvLib_CreatePrtStrRd (int               iKey,
                               std::string      cFrontTxt,
                               sstCpp01_Class_Cls *oCppCls,
                               std::string      cEleNam,
                               std::string      cEleNamLen,
                               std::string      *sBlcTxt)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Function builds a row like this:
  // iStat = Str1_AbPos2Str( 0, &TPos, cDelimit, sGDA_Str, sErrTxt, &oClass->Ele");

  *sBlcTxt = cFrontTxt;
  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;

  // cFrontTxt = "    iStat = Str1_AbPos2Int( 0, &TPos, cDelimit, s"

  if (cFrontTxt.find("CsvString2_Char") != cFrontTxt.npos)
  {
    *sBlcTxt = *sBlcTxt + "_Str, o";
  }
  else
  {
    *sBlcTxt = *sBlcTxt + "_Str, &o";
  }

  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;
  *sBlcTxt = *sBlcTxt + oCppCls->cGrpNam;
  *sBlcTxt = *sBlcTxt + oCppCls->cClsNam;
  *sBlcTxt = *sBlcTxt + "->";
  *sBlcTxt = *sBlcTxt + cEleNam;


  if (cEleNamLen.length() > 0)
  {
    *sBlcTxt = *sBlcTxt + ",";
    *sBlcTxt = *sBlcTxt + cEleNamLen;
  }
  *sBlcTxt = *sBlcTxt + ");";

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
int sstCpp01_CsvLib_CreatePrtStrWr (int          iKey,
                               std::string        cFrontTxt,
                               sstCpp01_Class_Cls *oCppCls,
                               sstStr01VarDefCls *oTypDef,
//                               std::string *sVonStr,
//                               std::string *sBisStr,
                               std::string *sBlcTxt)
//-----------------------------------------------------------------------------
{
  std::string sWithStr;
  sstStr01Cls oStrCnvt;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Init Str1 object and convert integer to string
  sWithStr.clear();
  iStat = oStrCnvt.Csv_Int2_2String( 0, oTypDef->Get_Dec(), &sWithStr);

  // Function builds a row like this:
  // iStat = Str1_Int2Zeile ( 0, 1, 3, oGripsTypHeaderinformation->HE2_Tag, sGrips_Str);
  //         cFrontTxt          ^

  *sBlcTxt = cFrontTxt;
  *sBlcTxt = *sBlcTxt + "o";
  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;
  *sBlcTxt = *sBlcTxt + oCppCls->cGrpNam;
  *sBlcTxt = *sBlcTxt + oCppCls->cClsNam;
  *sBlcTxt = *sBlcTxt + "->";
  *sBlcTxt = *sBlcTxt + oTypDef->Get_EleNam();

  *sBlcTxt = *sBlcTxt + ", s";

  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;
  *sBlcTxt = *sBlcTxt + "_Str);";

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
// Complete function description is in headerfile
// Build Source Row like this:
// iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, odxftypTT->TT2, sdxf_Str);
// or
// iStat = Str1_Real2Zeile ( 1, lRdStart, lRdStop, odxftypTT->TT3, 2, sdxf_Str);
//-----------------------------------------------------------------------------
int sstCpp01_CsvLib_CreatePrtStrWrFF (int                 iKey,
                                 std::string         cFrontTxt,
                                 std::string         cGrpNam,
                                 sstStr01VarDefCls  *oTypDef,
                                 std::string        *sBlcTxt)
//-----------------------------------------------------------------------------
{
  std::string sWithStr;
  sstStr01Cls oStrCnvt;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Init Str1 object and convert integer to string
  sWithStr.clear();
  iStat = oStrCnvt.Csv_Int2_2String( 0, oTypDef->Get_Type(), &sWithStr);

  // Function builds a row like this:
  // iStat = Str1_Int2Zeile ( 0, 1, 3, oGripsTypHeaderinformation->HE2_Tag, sGrips_Str);
  //         cFrontTxt                 ^

  // For example
  // " iStat = Str1_Double2Zeile ( 1, lRdStart, lRdStop, o"
  *sBlcTxt = cFrontTxt;

  // For example
  // "dxfTypTT->TT3"
  *sBlcTxt = *sBlcTxt + oTypDef->Get_SysNam();
  *sBlcTxt = *sBlcTxt + cGrpNam;
  *sBlcTxt = *sBlcTxt + oTypDef->Get_ObjNam();
  *sBlcTxt = *sBlcTxt + "->";
  *sBlcTxt = *sBlcTxt + oTypDef->Get_EleNam();

  switch (oTypDef->Get_Type())
  {
  case sstStr01Double:
  {
    *sBlcTxt = *sBlcTxt + ", ";
    *sBlcTxt = *sBlcTxt + sWithStr;
    *sBlcTxt = *sBlcTxt + ", s";
    break;
  }
  case sstStr01Float:
  {
    *sBlcTxt = *sBlcTxt + ", ";
    *sBlcTxt = *sBlcTxt + sWithStr;
    *sBlcTxt = *sBlcTxt + ", s";
    break;
  }
  default:
  {
    *sBlcTxt = *sBlcTxt + ", s";
    break;
  }
  }

  // For example
  // "dxf_Str"
  *sBlcTxt = *sBlcTxt + oTypDef->Get_SysNam();
  *sBlcTxt = *sBlcTxt + "_Str);";

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
int sstCpp01_CsvLib_FillBlc_Read (int               iKey,
                             sstStr01Cls *oFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  std::string sBlcTxt;  // one row inside function block
  sstCpp01_FilRowCls sBlcRow;
  std::string sLocStr;  // one row inside function block
  dREC04RECNUMTYP lClsTypNum = 0;
  sstCpp01_ClsTyp_Cls oClsTyp;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensдtze zurьckgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

  // Fill Function Block

//  StrDS1_stru sErrTxt;
//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

  sBlcTxt =  (char*) "//  Bloc Function1 Start";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcTxt =  (char*) "//  StrDS1_stru sErrTxt;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcTxt =  (char*) "  int iRet  = 0;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "//-----------------------------------------------------------------------------";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  if ( iKey != 0) return -1;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcRow.setRow("  iStat = oCsvRow.SetReadPositon(0,0);");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow(" ");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  // write all type definitions to header file
  for (dREC04RECNUMTYP ii=1; ii <= lClsTypNum; ii++)
  {
    // Datensatz an absoluter Position lesen.
    iStat = oCppTypClass->ClsTypDsVerw->Read( 0, ii, &oClsTyp);

    //  if (iStat >= 0)
        sBlcTxt =  (char*) "  if (iStat >= 0)";
        sBlcRow.setRow(sBlcTxt);
        iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);


    switch(oClsTyp.sClsMem.Get_Type())
    {
    case sstStr01Double:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0,  (char*) "    iStat = oCsvRow.CsvString2_Dbl( 0, s",
                                          oCppTypClass,
                                          oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"",
                                          &sBlcTxt);
      break;
    }
    case sstStr01Float:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Flt( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Int:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Int2( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01UInt:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_UInt2( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Long:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Int4( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01ULong:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_UInt4( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Bool:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Bool( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Date:
    {
      sLocStr.clear();
      iStat = oFormatInfo->Csv_Int2_2String( 0, (oClsTyp.sClsMem.Get_Width()+1), &sLocStr);  // for c string

      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Char( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          sLocStr, &sBlcTxt);

      break;
    }
    case sstStr01Char:
    {
      sLocStr.clear();
      iStat = oFormatInfo->Csv_Int2_2String( 0, (oClsTyp.sClsMem.Get_Width()+1), &sLocStr);  // for c string

      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvRow.CsvString2_Char( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          sLocStr, &sBlcTxt);

      break;
    }
    case sstStr01Unknown:
    {
      sBlcTxt =  (char*) "  iStat = -2;";
      sBlcRow.setRow(sBlcTxt);
      iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Unknown";
      break;
    }
    default:
    {
      sBlcTxt =  (char*) "  iStat = -2;";
      sBlcRow.setRow(sBlcTxt);
      iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Error";
      break;

    }
    }

    sBlcRow.setRow(sBlcTxt);
    iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  }

  // *sErrTxt = oCsvCnvt.GetErrorString();
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  *sErrTxt = oCsvRow.GetErrorString();";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  //  // Fatal Errors goes to an assert
//  if (iRet < 0)
//  {
//    // Expression (iRet >= 0) has to be fullfilled
//    assert(0);
//  }

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;

  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  // Fatal Errors goes to an assert";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  if (iRet < 0)";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  {";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "    // Expression (iRet >= 0) has to be fullfilled";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "    assert(0);";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  }";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  // Small Errors will given back";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  iRet = iStat;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcTxt =  (char*) "//  Bloc Function1 End";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

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
int sstCpp01_CsvLib_FillBlc_Write (int               iKey,
                                   sstStr01Cls *oFormatInfo,
                                   sstCpp01_Class_Cls *oCppTypClass,
                                   sstCpp01_Class_Cls *oCppFncClass,
                                   dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  std::string sBlcTxt;  // one row inside function block
  sstCpp01_FilRowCls sBlcRow;

  std::string sVonStr;  //
  std::string sBisStr;  //
  std::string sDecStr;  //
  dREC04RECNUMTYP lClsTypNum = 0;
  sstCpp01_ClsTyp_Cls oClsTyp;

  int iVon=0;
  int iBis=0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensдtze zurьckgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;
  // Fill Function Block

//  StrDS1_stru sErrTxt;
//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;


  sBlcTxt =  (char*) "//  Bloc Function Write Start";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcTxt =  (char*) "  int iRet  = 0;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  if ( iKey != 0) return -1;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcRow.setRow("  iStat = oCsvRow.SetReadPositon(0,0);");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow(" ");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  iVon = 1;

  // write all type definitions to header file
  for (dREC04RECNUMTYP ii=1; ii <= lClsTypNum; ii++)
  {
    // Datensatz an absoluter Position lesen.
    iStat = oCppTypClass->ClsTypDsVerw->Read( 0, ii, &oClsTyp);

    iBis = iVon + oClsTyp.sClsMem.Get_Width();

    //  if (iStat >= 0)
    sBlcTxt =  (char*) "  if (iStat >= 0)";
    sBlcRow.setRow(sBlcTxt);
    iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

    // Init Str1 object.
    sVonStr.clear();
    sBisStr.clear();

    // Int2 in einen String konvertieren und in Zeilenbereich kopieren.
    iStat = oFormatInfo->Csv_Int2_2String( 0, iVon, &sVonStr);
    iStat = oFormatInfo->Csv_Int2_2String( 0, iBis, &sBisStr);

    switch(oClsTyp.sClsMem.Get_Type())
    {
    case sstStr01Double:
    {
      sDecStr.clear();
      iStat = oFormatInfo->Csv_Int2_2String( 0, oClsTyp.sClsMem.Get_Dec(), &sDecStr);

      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Dbl_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Float:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Real_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Int:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Int2_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01UInt:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_UInt2_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Long:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Int4_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01ULong:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_UInt4_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Bool:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Bool_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);

      break;
    }
    case sstStr01Date:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Char_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);

      break;
    }
    case sstStr01Char:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_Char_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);

      break;
    }
    case sstStr01Unknown:
    {
      sBlcTxt =  (char*) "  iStat = -2;";
      sBlcRow.setRow(sBlcTxt);
      iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Unknown";
      break;
    }
    default:
    {
      sBlcTxt =  (char*) "  iStat = -2;";
      sBlcRow.setRow(sBlcTxt);
      iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Error";
      break;

    }
    }

    sBlcRow.setRow(sBlcTxt);
    iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

    iVon = iBis + 2;  // + one Space
    iBis = iVon + oClsTyp.sClsMem.Get_Dec();

  }

//  // Fatal Errors goes to an assert
//  if (iRet < 0)
//  {
//    // Expression (iRet >= 0) has to be fullfilled
//    assert(0);
//  }

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;

  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  // Fatal Errors goes to an assert";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  if (iRet < 0)";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  {";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "    // Expression (iRet >= 0) has to be fullfilled";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "    assert(0);";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  }";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  // Small Errors will given back";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) "  iRet = iStat;";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcTxt =  (char*) " ";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcTxt =  (char*) "//  Bloc Function Write End";
  sBlcRow.setRow(sBlcTxt);
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

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
int sstCpp01_CsvLib_FillBlc_Number (int               iKey,
//                                    sstStr01Cls *oFormatInfo,
                                    sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  sstCpp01_FilRowCls sBlcRow;

  dREC04RECNUMTYP dNumMember= oCppTypClass->ClsTypDsVerw->count();

  std::string oBlcStr = "  uiStat = ";
  oBlcStr = oBlcStr + std::to_string(dNumMember) + ";";
  sBlcRow.setRow(oBlcStr);
  int iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  return iStat;
}
//=============================================================================
int sstCpp01_CsvLib_FillBlc_StrNam (int               iKey,
//                                    sstStr01Cls *oFormatInfo,
                                    sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  sstCpp01_FilRowCls sBlcRow;
  sstCpp01_ClsTyp_Cls oMemRec;

  dREC04RECNUMTYP dNumMember= oCppTypClass->ClsTypDsVerw->count();

  std::string oBlcStr = "  oStat = \"";

  for (dREC04RECNUMTYP ll=1;ll<=dNumMember;ll++)
  {
    oCppTypClass->ClsTypDsVerw->Read(0,ll,&oMemRec);
    if (ll != dNumMember) oBlcStr =  oBlcStr + oMemRec.sClsMem.Get_EleNam() + ";";
    else oBlcStr =  oBlcStr + oMemRec.sClsMem.Get_EleNam();

  }

  oBlcStr += "\";";

  sBlcRow.setRow(oBlcStr);
  int iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  return iStat;
}
//=============================================================================
int sstCpp01_CsvLib_FillBlc_StrTyp (int               iKey,
//                                    sstStr01Cls *oFormatInfo,
                                    sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass,
                                    dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  sstCpp01_FilRowCls sBlcRow;
    sstCpp01_ClsTyp_Cls oMemRec;

  dREC04RECNUMTYP dNumMember= oCppTypClass->ClsTypDsVerw->count();

  std::string oBlcStr = "  oStat = \"";

  for (dREC04RECNUMTYP ll=1;ll<=dNumMember;ll++)
  {
    oCppTypClass->ClsTypDsVerw->Read(0,ll,&oMemRec);
    if (ll != dNumMember) oBlcStr =  oBlcStr + oMemRec.sClsMem.Get_TypeStr() + ";";
    else oBlcStr =  oBlcStr + oMemRec.sClsMem.Get_TypeStr();
  }
  oBlcStr += "\";";

  sBlcRow.setRow(oBlcStr);
  int iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  return iStat;
}
//=============================================================================
int sstCpp01_Hed_ClsWrTypRow (int                iKey,
                            sstCpp01_ClsTyp_Cls *oCppClsTyp,
                            sstMisc01AscFilCls    *sExpFile)
//-----------------------------------------------------------------------------
{
  std::string cTypeChar;
  std::string sFilRow;
  std::string sZeile;
  sstStr01VarTypeCls oTypEnmCnvt;
  sstStr01Cls oStrCnvt;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = oTypEnmCnvt.Enm2Str( 0, oCppClsTyp->sClsMem.Get_Type(), &cTypeChar);

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "    ";
  sFilRow = sFilRow + cTypeChar;
  sFilRow = sFilRow + " ";
  sFilRow = sFilRow + oCppClsTyp->sClsMem.Get_EleNam();

  if (oCppClsTyp->sClsMem.Get_Type() == sstStr01Char)
  {
    sFilRow = sFilRow + "[";


    // Int2 in einen String konvertieren und in Zeilenbereich kopieren.
    sZeile.clear();
    iStat = oStrCnvt.Csv_Int2_2String( 0, oCppClsTyp->sClsMem.Get_Width(), &sZeile);

    sFilRow = sFilRow + sZeile;
    sFilRow = sFilRow + "]";
  }

  sFilRow = sFilRow + ";";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);


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
int sstCpp01_ClassTab_Open (int iKey, sstCpp01_Class_Cls *oCppClass)
{
  sstCpp01_ClsTyp_Cls oCppClsTyp;  // for type class
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class
  sstCpp01_FilRowCls  sBlcTxt;     // one row inside function block

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Datensatz-Verwaltung anlegen / цffnen.
  oCppClass->ClsTypDsVerw = new sstRec04Cls ( sizeof(oCppClsTyp));
  oCppClass->ClsFncDsVerw = new sstRec04Cls ( sizeof(oCppClsFnc));
  oCppClass->ClsBlcDsVerw = new sstRec04Cls ( sizeof(sBlcTxt));

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
int sstCpp01_ClassTab_Close (int iKey, sstCpp01_Class_Cls *oCppClass)
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Close list of class function definitions
    delete ( oCppClass->ClsFncDsVerw);
    delete ( oCppClass->ClsTypDsVerw);
    delete ( oCppClass->ClsBlcDsVerw);

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
