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
// sst_generate_csv_lib.cpp    29.06.16  Re.    29.06.16  Re.
//
// program generates i/o (csv) lib code.
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

#include "sst_generate_csv_lib.h"

//=============================================================================
int main(int argc, char *argv [])
{

  sstMisc01AscFilCls sImpFile;
  // sstMisc01AscRowCls sFileRow;
  std::string sFileRow;
  sstMisc01FilNamCls oFilNam;
  std::string sDateStr;  // Generating Date
  std::string sFilStr;
  std::string sErrTxt;
  std::string sSysNam;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefFncCls oVarDefFnc;
  sstRec04Cls  DsVerw(sizeof(oStrType));
  // dREC04RECNUMTYP eTypeNum = 0;
  dREC04RECNUMTYP dRecNo = 0;

//  char cFilNam[MAX_PFAD];     // Filename without ending
//  char cFilNamEnd[MAX_PFAD];  // Filename with ending
//  char cFilEnd[MAX_PFAD];     // Filename ending
  std::string cFilNam;     // Filename without ending
  std::string cFilNamEnd;  // Filename with ending
  std::string cFilEnd;     // Filename ending

  int iStat = 0;
  int iStat1 = 0;
//-----------------------------------------------------------------------------

  if (argc <= 1)
  {
    printf("\n");
    printf("Call sst_generate_csv_lib typelib.def\n");
    printf("\n");
    printf("Programm generates cpp library for csv io from def-file\n");
    return 0;
  }

  // CascObjekt öffnen zum Lesen.
  // strncpy(cFilNamEnd,argv[1],MAX_PFAD);
  cFilNamEnd = argv[1];
  // iStat = casc_fopenRd_c ( 0, &sImpFile, cFilNamEnd);
  iStat = sImpFile.fopenRd( 0, cFilNamEnd.c_str());
  if (iStat < 0)
  {
    printf("Can not open file: %s\n", cFilNamEnd.c_str());
    return -1;
  }

  // Split filenamestring to name and ending.
  // iStat = SST_DatNamEnd ( 0, cFilNamEnd, cFilEnd, cFilNam, MAX_PFAD);
  iStat = oFilNam.SplitExtension( 0, &cFilNamEnd, &cFilEnd, &cFilNam);

  // Set Date of all source and header files
  // iStat = Str1_CopyStr(0, &sDateStr, (char*)"06.07.16");
  sDateStr = "06.07.16";

  // Datensatz-Verwaltung anlegen / öffnen.
  // iStat = DS1_DsOpen ( 0, &DsVerw, sizeof(oStrType), 100,(char*) "Type_Obj_Dss");

  // Eine Zeile aus Ascii-Datei lesen.
  // iStat1 = casc_rd_line_c ( 1, &sImpFile, &sFileRow);
  iStat1 = sImpFile.Rd_StrDS1( 0, &sFileRow);

  while (iStat1 >= 0)
  {

    if (dRecNo >= 3029)
    {
      iStat = 0;
    }
    // Copy string to Str1 structure.
    // iStat = Str1_CopyStr ( 0, &sFilStr, sFileRow.Txt);
    sFilStr = sFileRow;

    // interpret file row as cpp type dataset
    iStat = oVarDefFnc.ReadCSV ( 0, &sFilStr, &sErrTxt, &oStrType);
    assert(iStat==0);

    // Weiteren User-Datensatz in Datenspeicher schreiben.
    // DS1_DsShrNeu ( 0, &DsVerw, &oStrType);
    iStat = DsVerw.WritNew( 0, &oStrType, &dRecNo);

    // Eine Zeile aus Ascii-Datei lesen.
    // iStat1 = casc_rd_line_c ( 1, &sImpFile, &sFileRow);
    iStat1 = sImpFile.Rd_StrDS1( 0, &sFileRow);
  }

  // CascObjekt beenden und zugehörige Datei schließen.
  // iStat = casc_fclose_c ( 0, &sImpFile);
  iStat = sImpFile.fcloseFil(0);

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  // iStat = DS1_DsAnz ( 0, &DsVerw, &eTypeNum);
  // eTypeNum = DsVerw.count();

  // Set Name of system
  // iStat = Str1Cpy( 0, &sSysNam, oStrType.cSysNam);
  sSysNam = oStrType.Get_SysNam();

  //=============================================================================
  // Write Type classes to header and class file
  iStat = sstcsv_FilWrtClsTypOpen ( 0, &DsVerw, sSysNam, sDateStr);

  //=============================================================================
  // Write Function classes to header and class file
  iStat = sstcsv_FilWrtClsFncOpen ( 0, &DsVerw, sSysNam, sDateStr);

  // iStat = DS1_DsEnd ( 0, &DsVerw);

  return 0;
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int sstcsv_FilWrtClsTypOpen (int          iKey,
                             sstRec04Cls *DsVerw,
                             std::string sSysNam,
                             std::string sDateStr)
//-----------------------------------------------------------------------------
{
  std::string sGrpNam;  // Nam of function group, f.e. Typ, Fnc or Dbs
  std::string sHedFilNam;  // Nam of header file
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls sHedFil;
  sstMisc01AscFilCls sCppFil;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefCls oStrTypeAct;  // actual class element
  sstCpp01_Class_Cls oCppTypClass;  // One Type Class with all Elements, functions and function code blocks
  sstCpp01_ClsTyp_Cls oCppClsTyp1;  // for type class
  dREC04RECNUMTYP eTypeNum = 0;
  dREC04RECNUMTYP SatzNr = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Set Date in typ class
  iStat = oCppTypClass.SetDate ( 0, sDateStr);

  // Write Type classes to header and class file

  // iStat = Str1Cpy(0, &sGrpNam,(char*)"Typ");
  sGrpNam = "Typ";

  sHedFilNam = sSysNam;
  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + sGrpNam;
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());
  iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================

  // Starting rows in Header file
  iStat = oCppTypClass.GetDate ( 0, &sDateStr);

  // write headrows in cpp file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

  // Write comment to cpp header file
  iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, &sSysNam);

  // write define open rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sSysNam,
                                    sGrpNam, "");

  //===========================================================================
  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass);

  //===========================================================================

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / öffnen.
  // Open Dss Set 1 for Class Group 2
  // Open Dss Set 2 for Class Group 2
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = DsVerw->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dPos = oStrTypeAct.Get_ObjNam().find(oStrType.Get_ObjNam());
    if (dPos == oStrTypeAct.Get_ObjNam().npos)
    {

      // Write last type class data to class and header file
      iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppTypClass);

      // save class name for member class
      strncpy(oCppTypClass.cSysNam,oStrType.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cGrpNam,sGrpNam.c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cClsNam,oCppTypClass.cSysNam,dSST_STR01_VAR_NAM_LEN);
      strncat(oCppTypClass.cClsNam,oCppTypClass.cGrpNam,dSST_STR01_VAR_NAM_LEN);
      strncat(oCppTypClass.cClsNam,oStrType.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN); // Class name plus group name

      oStrTypeAct = oStrType;

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / öffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);

  }

  // Write last class data to files
  iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

  // Close HedFil object and File inside
  iStat = sCppFil.fcloseFil(0);
  iStat = sHedFil.fcloseFil(0);

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
int sstcsv_FilWrtClsFncOpen (int          iKey,
                             sstRec04Cls *DsVerw,
                             std::string sSysNam,
                             std::string sDateStr)
//-----------------------------------------------------------------------------
{
  std::string sGrpNam;  // Nam of function group, f.e. Typ, Fnc or Dbs
  std::string sHedFilNam;  // Nam of header file
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls sHedFil;
  sstMisc01AscFilCls sCppFil;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefCls oStrTypeAct;  // with GDA_
  sstCpp01_Class_Cls oCppTypClass;
  sstCpp01_ClsTyp_Cls oCppClsTyp1;  // for type class
  dREC04RECNUMTYP eTypeNum = 0;
  dREC04RECNUMTYP SatzNr = 0;


  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Set Date in typ class
  iStat = oCppTypClass.SetDate ( 0, sDateStr);

  // Reset values
  strncpy(oCppTypClass.cClsNam,"",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,sSysNam.c_str(),dSST_STR01_VAR_NAM_LEN);

  sGrpNam = "FncOpen";

  sHedFilNam = sSysNam;
  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + sGrpNam;
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());
  iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================

  // write headrows in cpp file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

  // Write comment to cpp header file
  iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, &sSysNam);

  // write define open rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sSysNam,
                                    sGrpNam, "");

  //===========================================================================
  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass);

  //===========================================================================
  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / öffnen.
  // Open Dss Set 1 for Class Group 2
  // Open Dss Set 2 for Class Group 2
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = DsVerw->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().find(oStrType.Get_ObjNam());
    if (dStrPos == oStrType.Get_ObjNam().npos)
    {

      // Write last type class data to class and header file
      iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);

      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrType.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrType.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      oStrTypeAct = oStrType;

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / öffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;

    // SatzNr = DS1_DsShrNeu ( 0, &oCppTypClass.ClsTypDsVerw, &oCppClsTyp1);
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);


  }

  // Write last class data to files
  iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

  // Close HedFil object and File inside
  iStat = sHedFil.fcloseFil(0);
  iStat = sCppFil.fcloseFil(0);


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
int sst_WrtClsData_inPipe_toFilesT (int               iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstMisc01AscFilCls   *sClsFil,
                                    sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_ClsFnc_Cls oCppClsFnc1;  // functions for type class

  dREC04RECNUMTYP lSatzNr = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================

  // define new TYPE class set and write: constructor
  oCppClsFnc1.eCppType = sstStr01Unknown;
  oCppClsFnc1.eClsVisiTyp = myClsPublic;

  oCppClsFnc1.lBlcStart=1;
  // Fill inside of typ constructor class function.
  oCppClsFnc1.lBlcRows = lSatzNr - oCppClsFnc1.lBlcStart + 1;

  strcpy(oCppClsFnc1.cClsNam,oCppTypClass->cClsNam);
  strcpy(oCppClsFnc1.cFncNam,oCppTypClass->cClsNam);
  strcpy(oCppClsFnc1.cFncPar,"");
  strcpy(oCppClsFnc1.cFncCom,"// Constructor");
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc1, &lSatzNr);

  //===========================================================================

  // define new TYPE class function: SetTestData
  oCppClsFnc1.eCppType = sstStr01Int;
  oCppClsFnc1.eClsVisiTyp = myClsPublic;

  oCppClsFnc1.lBlcStart = lSatzNr + 1;
  oCppClsFnc1.lBlcRows = lSatzNr - oCppClsFnc1.lBlcStart + 1;

  strcpy(oCppClsFnc1.cClsNam,oCppTypClass->cClsNam);
  strcpy(oCppClsFnc1.cFncNam,(char*)"SetTestData");
  strcpy(oCppClsFnc1.cFncPar,"");
  strcpy(oCppClsFnc1.cFncCom,"/**< Set Test Data */");
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc1, &lSatzNr);

  //===========================================================================

  // write information to cpp header file of member class
  iStat = sstCpp01_wrt2CppHedFil2 ( 1, sHedFil, oCppTypClass);

  // write information to cpp class file of member class
  iStat = sstCpp01_wrt2CppClsFil2 ( 1, sClsFil, oCppTypClass);

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
//-----------------------------------------------------------------------------
int sst_WrtClsData_inPipe_toFilesF (int               iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstMisc01AscFilCls   *sClsFil,
                                    std::string      *sGrpNam,
                                    sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_Class_Cls oCppFncClass;

  sstCpp01_ClsFnc_Cls oCppClsFnc2;  // for func class

  sstStr01Cls oFmtInfoObj; // Infos about input output format

  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

//  lSatzNr = oCppTypClass->ClsFncDsVerw->count();
//  lSatzNr = oCppTypClass->ClsBlcDsVerw->count();

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam->c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppFncClass.cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncat(oCppFncClass.cClsNam,oCppFncClass.cGrpNam, dSST_STR01_VAR_NAM_LEN);
  strncat(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  // define new FUNCTION class set and write: constructor

  // define new class set and write: constructor
  oCppClsFnc2.eCppType = sstStr01Unknown;
  oCppClsFnc2.eClsVisiTyp = myClsPublic;
  oCppClsFnc2.lBlcStart = 0;
  oCppClsFnc2.lBlcRows = 0;
  strncpy(oCppClsFnc2.cClsNam,oCppFncClass.cClsNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc2.cFncNam,oCppFncClass.cClsNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc2.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc2.cFncCom,"// Constructor", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc2, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: READ

  oCppClsFnc2.eCppType = sstStr01Int;
  oCppClsFnc2.eClsVisiTyp = myClsPublic;
  oCppClsFnc2.lBlcStart = 1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_Read ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc2.lBlcRows = lSatzNrBlc;
  strncpy(oCppClsFnc2.cClsNam,oCppFncClass.cClsNam, dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc2.cFncNam,"Csv_Read", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc2.cFncPar,"int iKey, std::string *sErrTxt, std::string *s", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar,"_Str, ", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, " *o", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);

  strncpy(oCppClsFnc2.cFncCom,"// Csv Read Function", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc2, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: WRITE
  oCppClsFnc2.eCppType = sstStr01Int;
  oCppClsFnc2.eClsVisiTyp = myClsPublic;
  oCppClsFnc2.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Write
  iStat = sstCpp01_CsvLib_FillBlc_Write ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc2.lBlcRows = lSatzNrBlc - oCppClsFnc2.lBlcStart +1 ;
  strncpy(oCppClsFnc2.cClsNam,oCppFncClass.cClsNam, dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc2.cFncNam,"Csv_Write", dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc2.cFncPar,"int iKey, ", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, " *o", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar,", std::string *s", dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc2.cFncPar,"_Str", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc2.cFncCom,"// Csv Write Function", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc2, &lSatzNr);

  //-----------------------------------------------------------------------------

  // write information to cpp header file of function class
  iStat = sstCpp01_wrt2CppHedFil2 ( 1, sHedFil, &oCppFncClass);

  // write information to cpp class file of function class
  iStat = sstCpp01_wrt2CppClsFil2 ( 1, sClsFil, &oCppFncClass);

  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncClass);

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
