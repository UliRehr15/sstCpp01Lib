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
                       sstMisc01AscFilCls *sExpFile,
                       std::string               *cObjNam)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;


  // Write empty row to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)"//");

  // Write Casc-Line-Object to Casc-File.
  sFilRow.clear();
  sFilRow = "//  Definitions of class \"";
  sFilRow = sFilRow + *cObjNam;
  sFilRow = sFilRow + "\"";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // Write comment row to Asc-File.
  iStat = sExpFile->wr_txt( 0, (char*)"//");

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
int sstCpp01_Cls_WrtInc (int               iKey,
                       sstMisc01AscFilCls   *sExpFile,
                       sstCpp01_Class_Cls *oCppClass)
//-----------------------------------------------------------------------------
{
  std::string sFilRow;
  std::string sFilRow2;  // for second include
  std::string sFncGrpNam;
  std::string clocObjNam;
  // char *pStr;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey < 0 || iKey > 1) return -1;

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

  // Save function group name ( ptss_fnc, ptss_typ)from filename
  sFncGrpNam = sExpFile->GetFileName();

  size_t lPos =  sFncGrpNam.find(".cpp");
  // if(pStr != NULL)
  if(lPos != sFncGrpNam.npos)
  {
    // In String durch Adresse und Länge bezeichneten Substring austauschen.
    sFncGrpNam.erase(lPos,lPos+4);
  }

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
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstMisc01Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)"#include <sstRec04Lib.h>");
  iStat = sExpFile->wr_txt(0, (char*)" ");

  // write base class include
  // typ bas include or typ/fnc base include
  if (iKey == 1)
  {
    sFilRow = "#include \"";
    sFilRow = sFilRow + sFncGrpNam;
    sFilRow = sFilRow + "_Base.h\"";

    size_t dPos = sFilRow.find("Fnc");
    if(dPos != sFilRow.npos)
    {
      // In String durch Adresse und Länge bezeichneten Substring austauschen.
      sFilRow2 = "#include \"";
      sFilRow2 = sFilRow2 + oCppClass->cSysNam;
      sFilRow2 = sFilRow2 +(char*) "_";
      sFilRow2 = sFilRow2 +oCppClass->cGrpNam;
      sFilRow2 = sFilRow2 +"_Base.h\"";
      iStat = sExpFile->Wr_StrDS1( 0, &sFilRow2);
    }

    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

    iStat = sExpFile->wr_txt( 0, (char*) " ");
  }

  // write class include
  // typ include or typ/fnc include
  clocObjNam = sFncGrpNam;

  size_t dPos = clocObjNam.find("Fnc");
  if(dPos != clocObjNam.npos)
  {
    // In String durch Adresse und Länge bezeichneten Substring austauschen.
    clocObjNam.replace(dPos,dPos+3,"Typ");

    // Write Casc-Line-Object to Casc-File.
    sFilRow = "#include \"";
    sFilRow = sFilRow + oCppClass->cSysNam;
    sFilRow = sFilRow + "_";
    sFilRow = sFilRow + oCppClass->cGrpNam;
    sFilRow = sFilRow + ".h\"";
    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  }

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "#include \"";
  sFilRow = sFilRow + sFncGrpNam;
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
    // In String durch Adresse und Länge bezeichneten Substring austauschen.
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
int sstCpp01_Hed_wrt_class_info (int             iKey,
                               sstMisc01AscFilCls *sExpFile,
                               std::string           *cGrpNam,
                               sstRec04Cls    *poClsTypDsVerw,
                               // char           *cObjNam,
                               std::string           *cClsDat)
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

  // iStat = DS1_DsAnz ( 0, poClsTypDsVerw, &AnzDs);
  AnzDs = poClsTypDsVerw->count();
  if (AnzDs <= 0) return -2;

  // Record 1 is constructor
  // Record 2 is first class element
  iStat = poClsTypDsVerw->Read( 0, 2, &oTypDef);
  cObjNam = oTypDef.sClsMem.Get_ObjInfo();



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
  sFilRow = "* @brief ";
  sFilRow = sFilRow + cObjNam;
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"*");
  iStat = sExpFile->wr_txt( 0, (char*)"* More Comment");
  iStat = sExpFile->wr_txt( 0, (char*)"*");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* Changed: ";
  sFilRow = sFilRow + *cClsDat;
  sFilRow = sFilRow + "  Re.";
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // iStat = casc_wr_txt ( 0, sExpFile, (char*)"*");
  iStat = sExpFile->wr_txt( 0, (char*)"*");

  // Write Casc-Line-Object to Casc-File.
  sFilRow = "* @ingroup ";
  sFilRow = sFilRow + *cGrpNam;
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
  //    public:   // Öffentliche Funktionen
  //       X();  // Konstruktor
  //      ~X();  // Destruktor
  //    private:  // Private Funktionen
  //    int Dum;        /**< Dummy */
  //  };


  // Write Casc-Line-Object to Casc-File.
  sFilRow = "class ";
  sFilRow = sFilRow + oCppCls->cClsNam;
  if(iKey == 1)
  {
    sFilRow = sFilRow + " : public ";
    sFilRow = sFilRow + oCppCls->cSysNam;
    sFilRow = sFilRow + "_";
    sFilRow = sFilRow + oCppCls->cGrpNam;
    sFilRow = sFilRow + "_Base";
  }
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  iStat = sExpFile->wr_txt( 0, (char*)"{");

  // Get number of stored class functions ( include constructor)
  lFuncNum = oCppCls->ClsFncDsVerw->count();

  // Get number of stored class members
  lClsTypNum = oCppCls->ClsTypDsVerw->count();

  //=== PUBLIC ================================================================

  iStat = sExpFile->wr_txt( 0, (char*)"  public:");

  // write all class functions to header file
  for (dREC04RECNUMTYP ii = 1; ii <= lFuncNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oCppCls->ClsFncDsVerw->Read( 0, ii, &oCppClsFnc);

    if (oCppClsFnc.eClsVisiTyp != myClsPublic) break;

    sstStr01VarTypeCls oVarType;
    oVarType.Enm2FullStr( 0, oCppClsFnc.eCppType, &cTypeChar);

    sFilRow = "    ";
    sFilRow = sFilRow + cTypeChar;
    if (cTypeChar.length() > 0) sFilRow = sFilRow + " ";
    sFilRow = sFilRow + oCppClsFnc.cFncNam;
    sFilRow = sFilRow + "(";
    sFilRow = sFilRow + oCppClsFnc.cFncPar;
    sFilRow = sFilRow + "); ";
    sFilRow = sFilRow + oCppClsFnc.cFncCom;
    iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);
  }

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

  // Write emtpy row
  iStat = sExpFile->wr_txt( 0, (char*)" ");

  // Write comment row
  sFilRow = "// ";
  sFilRow = sFilRow + oCppClsFnc->cFncCom;
  iStat = sExpFile->Wr_StrDS1( 0, &sFilRow);

  // Convert return type to char
  sstStr01VarTypeCls oVarType;
  iStat = oVarType.Enm2FullStr( 0, oCppClsFnc->eCppType, &cTypeChar);
  iStat = oVarType.Enm2ShortStr( 0, oCppClsFnc->eCppType, &cTypeType);

  // Write Casc-Line-Object to Casc-File.
  sFilRow = cTypeChar;
  if (cTypeChar.length() > 0) sFilRow = sFilRow + " ";
  sFilRow = sFilRow + oCppClsFnc->cClsNam;
  sFilRow = sFilRow + "::";
  sFilRow = sFilRow + oCppClsFnc->cFncNam;
  sFilRow = sFilRow + "(";
  sFilRow = sFilRow + oCppClsFnc->cFncPar;
  sFilRow = sFilRow + ")";
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
    case sstStr01Int:
    case sstStr01Long:   sFilRow = sFilRow + " = 0;";break;
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

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
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
  iStat = sstCpp01_Hed_WrtCom ( 0, &sExpFile, &cClassNam);

  // write define open rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_open ( 0, &sExpFile, (char*)"SST",oCppClass->cSysNam,
                                                               oCppClass->cGrpNam,
                                                               oCppClass->cClsNam);

  // write class info block in cpp header file
  iStat = sstCpp01_Hed_wrt_class_info ( 0, &sExpFile, &cLibNam, oCppClass->ClsTypDsVerw, &sDateStr);

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
  cLibNam = cLibNam + "_Lib";

  iStat = oCppClass->GetDate(0,&sDateStr);

  // write class info block in cpp header file
  iStat = sstCpp01_Hed_wrt_class_info ( 0, sCppHedFil, &cLibNam, oCppClass->ClsTypDsVerw, &sDateStr);

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
//int sst_wrt2CppClsFil (int               iKey,
//                       sstCpp01_Class_Cls *oCppClass)
////-----------------------------------------------------------------------------
//{
//  sstMisc01AscFilCls sExpFile;
//  char cExpFilNam[MAX_PFAD];
//  dREC04RECNUMTYP  lFuncNum = 0;
//  sstCpp01_ClsTyp_Cls oCppClsTyp;
//  // char cClassNam[dSST_STR01_VAR_NAM_LEN];
//  std::string cClassNam;
//  sstCpp01_ClsFnc_Cls oCppClsFnc;
//  // StrDS1_stru sDateStr;
//  std::string sDateStr;

//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey < 0 || iKey > 1) return -1;

//  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
//  // iStat = DS1_DsAnz ( 0, &oCppClass->ClsFncDsVerw, &lFuncNum);
//  lFuncNum = oCppClass->ClsFncDsVerw->count();

//  if (lFuncNum <= 0) return -2;

//  iStat = strlen(oCppClass->cClsNam);
//  if (iStat <= 0) return -3;

//  // Save Class Name
//  // strcpy(cClassNam,oCppClass->cClsNam);
//  cClassNam = oCppClass->cClsNam;

//  // strcpy(cExpFilNam,oStrTypeAct->cObjNam);
////  strcpy(cExpFilNam,cClassNam);
////  strcat(cExpFilNam,".cpp");
//  strncpy(cExpFilNam,cClassNam.c_str(),MAX_PFAD);
//  strncat(cExpFilNam,".cpp",MAX_PFAD);

//  // CascObjekt öffnen zum Schreiben.
//  // iStat = casc_fopenWr_c ( 0, &sExpFile, cExpFilNam);
//  iStat = sExpFile.fopenWr( 0, cExpFilNam);

//  iStat = oCppClass->GetDate(0,&sDateStr);

//  // write headrows in cpp header file
//  // iStat = sstCpp01_Fil_wrt_head ( 0, &sExpFile, cClassNam, cExpFilNam, (char*) "30.06.12");
//  // iStat = sstCpp01_Fil_wrt_head ( 0, &sExpFile, cClassNam, cExpFilNam, sDateStr.Txt);
//  iStat = sstCpp01_Fil_wrt_head ( 0, &sExpFile, &sDateStr);

//  // Write comment and includes to cls file
//  // iStat = sstCpp01_Cls_WrtInc( 1, &sExpFile, cClassNam);
//  iStat = sstCpp01_Cls_WrtInc( iKey, &sExpFile, oCppClass);

//  // write all class functions to cpp files
//  for (dREC04RECNUMTYP ii = 1; ii <= lFuncNum; ii++)
//  {

//    // Datensatz an absoluter Position lesen.
//    // iStat = DS1_DsLesAbs ( 0, &oCppClass->ClsFncDsVerw, &oCppClsFnc, ii);
//    iStat = oCppClass->ClsFncDsVerw->Read( 0, ii, &oCppClsFnc);

//    // Write one class function to file
//    iStat = sstCpp01_WrtCls ( 0, &sExpFile, oCppClass->ClsBlcDsVerw, &oCppClsFnc);

//  }

//  // CascObjekt beenden und zugehörige Datei schließen.
//  // iStat = casc_fclose_c ( 0, &sExpFile);
//  iStat = sExpFile.fcloseFil(0);

//  // Fatal Errors goes to an assert
//  if (iRet < 0)
//  {
//    // Expression (iRet >= 0) has to be fullfilled
//    assert(0);
//  }

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;
//}
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
// iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, optsstypTT->TT2, sptss_Str);
// or
// iStat = Str1_Real2Zeile ( 1, lRdStart, lRdStop, optsstypTT->TT3, 2, sptss_Str);
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
  // "PtssTypTT->TT3"
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
  // "Ptss_Str"
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

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
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
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0,  (char*) "    iStat = oCsvCnvt.CsvString2_Dbl( 0, s",
                                          oCppTypClass,
                                          oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"",
                                          &sBlcTxt);
      break;
    }
    case sstStr01Float:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Flt( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Int:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Int2( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01UInt:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_UInt2( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Long:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Int4( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01ULong:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_UInt4( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Bool:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Bool( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          (char*)"", &sBlcTxt);
      break;
    }
    case sstStr01Date:
    {
      sLocStr.clear();
      iStat = oFormatInfo->Csv_Int2_2String( 0, (oClsTyp.sClsMem.Get_Width()+1), &sLocStr);  // for c string

      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Char( 0, s",
                                          oCppTypClass, oClsTyp.sClsMem.Get_EleNam(),
                                          sLocStr, &sBlcTxt);

      break;
    }
    case sstStr01Char:
    {
      sLocStr.clear();
      iStat = oFormatInfo->Csv_Int2_2String( 0, (oClsTyp.sClsMem.Get_Width()+1), &sLocStr);  // for c string

      iStat = sstCpp01_CsvLib_CreatePrtStrRd ( 0, (char*) "    iStat = oCsvCnvt.CsvString2_Char( 0, s",
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
  sBlcTxt =  (char*) "  *sErrTxt = oCsvCnvt.GetErrorString();";
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

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
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

      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Dbl_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Float:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Real_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Int:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Int2_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01UInt:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_UInt2_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Long:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Int4_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01ULong:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_UInt4_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);
      break;
    }
    case sstStr01Bool:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Bool_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);

      break;
    }
    case sstStr01Date:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Char_2String ( 0, ",
                                          oCppTypClass,
                                          &oClsTyp.sClsMem,
                                          &sBlcTxt);

      break;
    }
    case sstStr01Char:
    {
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvCnvt.Csv_Char_2String ( 0, ",
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
//int sstCpp01_CsvLib_FillBlc_WriteFF (int               iKey,
////                                sstFormatInfoCls *oFormatInfo,
//                                sstStr01Cls *oFormatInfo,
//                                sstCpp01_Class_Cls *oCppTypClass,
//                                sstRec04Cls      *ClsBlcDsVerw,
//                                dREC04RECNUMTYP     *lSatzNr)

////-----------------------------------------------------------------------------
//{
////  StrDS1_stru sBlcTxt;  // one row inside function block
////  StrDS1_stru sVonStr;  //
////  StrDS1_stru sBisStr;  //
////  StrDS1_stru sLenStr;  // length string
//  std::string sBlcTxt;  // one row inside function block
//  std::string sVonStr;  //
//  std::string sBisStr;  //
//  std::string sLenStr;  // length string
//  dREC04RECNUMTYP lClsTypNum = 0;
//  sstCpp01_ClsTyp_Cls oClsTyp;

//  int iVon=0;
//  int iBis=0;

//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
//  // iStat = DS1_DsAnz ( 0, &oCppTypClass->ClsTypDsVerw, &lClsTypNum);
//  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
//  if (lClsTypNum <= 0) return -2;


////  long lRdStart =  0;
////  long lRdStop  = -1;
////  long lVarGap = 0;
////  long lVarLen = 0;
////  StrDS1_stru sZeroStr;



//  // Fill Function Block

////  StrDS1_stru sErrTxt;
////  char cDelimit[2]=" ";
////  long TPos = 4;
////  int iRet  = 0;
////  int iStat = 0;
//////-----------------------------------------------------------------------------
////  if ( iKey != 0) return -1;


//  sBlcTxt =  (char*) "//  Bloc Function Write Start";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);



//  sBlcTxt =  (char*) "  long lRdStart =  0;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  long lRdStop  = -1;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  long lVarGap = 0;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  long lVarLen = 0;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  StrDS1_stru sZeroStr;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  // sBlcTxt =  (char*) "  int iStat = 0;");
//  // iStat = oCppFncClass->ClsBlcDsVerw.WritNew( 0, &sBlcTxt, lSatzNr);

//  sBlcTxt =  (char*) "  int iRet  = 0;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  sBlcTxt =  (char*) "//-----------------------------------------------------------------------------";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  if ( iKey != 0) return -1;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  // iStat = Str1_Init( 0, &sZeroStr);
//  sBlcTxt =  (char*) "  iStat = Str1_Init( 0, &sZeroStr);";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  // iStat = Str1_Init( 0, sPtss_Str);
////  iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "  iStat = Str1_Init( 0, s");
////  iStat = Str1Cat ( 0, &sBlcTxt, oCppTypClass->cSysNam);
////  iStat = Str1Cat ( 0, &sBlcTxt, (char*) "_Str);");
//  sBlcTxt = "  iStat = Str1_Init( 0, s";
//  sBlcTxt = sBlcTxt + oCppTypClass->cSysNam;
//  sBlcTxt = sBlcTxt + "_Str);";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  iVon = 1;
//  // iBis = iVon + oClsTyp.oClsMem.iWidth;

//  // write all type definitions to header file
//  for (dREC04RECNUMTYP ii=1; ii <= lClsTypNum; ii++)
//  {
//    // Datensatz an absoluter Position lesen.
//    // iStat = DS1_DsLesAbs ( 0, &oCppTypClass->ClsTypDsVerw, &oClsTyp, ii);
//    iStat = oCppTypClass->ClsTypDsVerw->Read( 0, ii, &oClsTyp);

//    iBis = iVon + oClsTyp.sClsMem.Get_Width();

//    //  if (iStat >= 0)
//    sBlcTxt =  (char*) "  if (iStat >= 0)";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//    //  {
//    sBlcTxt =  (char*) "  {";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

////    // Kopieren eines Char in einen Zeilenbereich.
////    lVarLen = 2;
////    lVarGap = 1;
////    lRdStart = lRdStop  + lVarGap + 1;
////    lRdStop  = lRdStart + lVarLen - 1;
////    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, oTT.cPar1, &sTestStr);
////    iStat = Str1_Real2Zeile ( 1, lRdStart, lRdStop, oTT.fPar3 ,2, &sTestStr);

////    iStat = Str1_Init ( 0, &sLenStr);
////    iStat = Str1_Int2Zeile ( 0, 1, 3, oClsTyp.sClsMem.iWidth, &sLenStr);
//    sLenStr.clear();
//    iStat = oFormatInfo->Csv_Int2_2String( 0, oClsTyp.sClsMem.Get_Width(), &sLenStr);

////    iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "    lVarLen = ");
////    iStat = Str1Cat ( 0, &sBlcTxt, sLenStr.Txt);
////    iStat = Str1Cat ( 0, &sBlcTxt, (char*)";");
//    sBlcTxt = "    lVarLen = ";
//    sBlcTxt = sBlcTxt + sLenStr;
//    sBlcTxt = sBlcTxt + ";";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//    sBlcTxt =  (char*) "    lVarGap = 1;";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//    sBlcTxt =  (char*) "    lRdStart = lRdStop  + lVarGap + 1;";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//    sBlcTxt =  (char*) "    lRdStop  = lRdStart + lVarLen - 1;";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//    // Init Str1 object.
////    iStat = Str1_Init ( 0, &sVonStr);
////    iStat = Str1_Init ( 0, &sBisStr);
//    sVonStr.clear();
//    sBisStr.clear();

//    // Int2 in einen String konvertieren und in Zeilenbereich kopieren.
////    iStat = Str1_Int2Zeile ( 0, 1, 3, iVon, &sVonStr);
////    iStat = Str1_Int2Zeile ( 0, 1, 3, iBis, &sBisStr);
//    iStat = oFormatInfo->Csv_Int2_2String( 0, iVon, &sVonStr);
//    iStat = oFormatInfo->Csv_Int2_2String( 0, iBis, &sBisStr);

//    switch(oClsTyp.sClsMem.Get_Type())
//    {
//    case sstStr01Double:
//    {
//      // memset(sZeroStr.Txt, 48, lVarLen);
//      // sZeroStr.Txt[lVarLen] = 0;
//      // iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, sPtss_Str);

//      sBlcTxt =  (char*) "    memset(sZeroStr.Txt, 48, lVarLen);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "    sZeroStr.Txt[lVarLen] = 0;";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
////      iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s");
////      iStat = Str1Cat ( 0, &sBlcTxt, oCppTypClass->cSysNam);
////      iStat = Str1Cat ( 0, &sBlcTxt, (char*) "_Str);");
//      sBlcTxt = "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s";
//      sBlcTxt = sBlcTxt + oCppTypClass->cSysNam;
//      sBlcTxt = sBlcTxt + "_Str);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//      // iStat = Str1_Init ( 0, &sDecStr);
//      // iStat = Str1_Int2Zeile ( 0, 1, 3, oClsTyp.sClsMem.iDec, &sDecStr);

//      iStat = sstCpp01_CsvLib_CreatePrtStrWrFF ( 0, (char*) "    iStat = Str1_Dbl2Zeile ( 1, lRdStart, lRdStop, o",
//                                           oCppTypClass->cGrpNam,
//                                           &oClsTyp.sClsMem, // &sVonStr, &sBisStr,
//                                           &sBlcTxt);
//      break;
//    }
//    case sstStr01Float:
//    {
//      // memset(sZeroStr.Txt, 48, lVarLen);
//      // sZeroStr.Txt[lVarLen] = 0;
//      // iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, &sTestStr);

//      sBlcTxt =  (char*) "    memset(sZeroStr.Txt, 48, lVarLen);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "    sZeroStr.Txt[lVarLen] = 0;";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
////      iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s");
////      iStat = Str1Cat ( 0, &sBlcTxt, oCppTypClass->cSysNam);
////      iStat = Str1Cat ( 0, &sBlcTxt, (char*) "_Str);");
//      sBlcTxt = "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s";
//      sBlcTxt = sBlcTxt + oCppTypClass->cSysNam;
//      sBlcTxt = sBlcTxt + "_Str);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//      iStat = sstCpp01_CsvLib_CreatePrtStrWrFF ( 0, (char*) "    iStat = Str1_Real2Zeile ( 1, lRdStart, lRdStop, o",
//                                           oCppTypClass->cGrpNam,
//                                           &oClsTyp.sClsMem, // &sVonStr, &sBisStr,
//                                           &sBlcTxt);
//      break;
//    }
//    case sstStr01Int:
//    {
//      // memset(sZeroStr.Txt, 48, lVarLen);
//      // sZeroStr.Txt[lVarLen] = 0;
//      // iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, &sTestStr);

//      sBlcTxt =  (char*) "    memset(sZeroStr.Txt, 48, lVarLen);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "    sZeroStr.Txt[lVarLen] = 0;";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
////      iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s");
////      iStat = Str1Cat ( 0, &sBlcTxt, oCppTypClass->cSysNam);
////      iStat = Str1Cat ( 0, &sBlcTxt, (char*) "_Str);");
//      sBlcTxt = "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s";
//      sBlcTxt = sBlcTxt + oCppTypClass->cSysNam;
//      sBlcTxt = sBlcTxt + "_Str);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//      iStat = sstCpp01_CsvLib_CreatePrtStrWrFF ( 0, (char*) "    iStat = Str1_Int2Zeile ( 1, lRdStart, lRdStop, o",
//                                           oCppTypClass->cGrpNam,
//                                           &oClsTyp.sClsMem, // &sVonStr, &sBisStr,
//                                           &sBlcTxt);
//      break;
//    }
//    case sstStr01Long:
//    {
//      // memset(sZeroStr.Txt, 48, lVarLen);
//      // sZeroStr.Txt[lVarLen] = 0;
//      // iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, &sTestStr);

//      sBlcTxt =  (char*) "    memset(sZeroStr.Txt, 48, lVarLen);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "    sZeroStr.Txt[lVarLen] = 0;";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
////      iStat = Str1Cpy ( 0, &sBlcTxt, (char*) "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s");
////      iStat = Str1Cat ( 0, &sBlcTxt, oCppTypClass->cSysNam);
////      iStat = Str1Cat ( 0, &sBlcTxt, (char*) "_Str);");
//      sBlcTxt = "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, sZeroStr.Txt, s";
//      sBlcTxt = sBlcTxt + oCppTypClass->cSysNam;
//      sBlcTxt = sBlcTxt + "_Str);";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//      iStat = sstCpp01_CsvLib_CreatePrtStrWrFF ( 0, (char*) "    iStat = Str1_Int4Zeile ( 1, lRdStart, lRdStop, o",
//                                           oCppTypClass->cGrpNam,
//                                           &oClsTyp.sClsMem, // &sVonStr, &sBisStr,
//                                           &sBlcTxt);
//      break;
//    }
//    case sstStr01Char:
//    {
//      iStat = sstCpp01_CsvLib_CreatePrtStrWrFF ( 0, (char*) "    iStat = Str1_Char2Zeile ( 0, lRdStart, lRdStop, o",
//                                           oCppTypClass->cGrpNam,
//                                           &oClsTyp.sClsMem, // &sVonStr, &sBisStr,
//                                           &sBlcTxt);

//      break;
//    }
//    case sstStr01Unknown:
//    {
//      sBlcTxt =  (char*) "  iStat = -2;)";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Unknown";
//      break;
//    }
//    default:
//    {
//      sBlcTxt =  (char*) "  iStat = -2;)";
//      iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//      sBlcTxt =  (char*) "  // iStat = Str1_AbPos2 ... Error";
//      break;

//    }
//    }

//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//    iVon = iBis + 2;  // + one Space
//    iBis = iVon + oClsTyp.sClsMem.Get_Dec();

//    //  }
//    sBlcTxt =  (char*) "  }";
//    iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  }

////  // Fatal Errors goes to an assert
////  if (iRet < 0)
////  {
////    // Expression (iRet >= 0) has to be fullfilled
////    assert(0);
////  }

////  // Small Errors will given back
////  iRet = iStat;

////  return iRet;

//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  // Fatal Errors goes to an assert";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  if (iRet < 0)";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  {";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "    // Expression (iRet >= 0) has to be fullfilled";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "    assert(0);";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  }";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  // Small Errors will given back";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) "  iRet = iStat;";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  sBlcTxt =  (char*) " ";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);
//  // sBlcTxt =  (char*) "  return iRet;");
//  // iStat = oCppFncClass->ClsBlcDsVerw.WritNew( 0, &sBlcTxt, lSatzNr);

//  sBlcTxt =  (char*) "//  Bloc Function Write End";
//  iStat = ClsBlcDsVerw->WritNew( 0, &sBlcTxt, lSatzNr);

//  // Fatal Errors goes to an assert
//  if (iRet < 0)
//  {
//    // Expression (iRet >= 0) has to be fullfilled
//    assert(0);
//  }

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;
//}
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
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for type class
  sstCpp01_FilRowCls  sBlcTxt;   // one row inside function block

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Datensatz-Verwaltung anlegen / öffnen.
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
