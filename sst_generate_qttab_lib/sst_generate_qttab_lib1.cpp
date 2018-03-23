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
// sst_generate_qttab_lib1.cpp    06.02.2018  Re.    06.02.2018  Re.
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

#include "sst_generate_qttab_lib.h"

//=============================================================================
int main(int argc, char *argv [])
{

  sstMisc01AscFilCls sImpFile;
  std::string sFileRow;
  sstMisc01FilNamCls oFilNam;
  std::string sDateStr;  // Generating Date
  std::string sFilStr;
  std::string sErrTxt;
  std::string sSysNam;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefFncCls oVarDefFnc;
  sstRec04Cls  DsVerw(sizeof(oStrType));
  dREC04RECNUMTYP dRecNo = 0;

  std::string cFilNam;     // Filename without ending
  std::string cFilNamEnd;  // Filename with ending
  std::string cFilEnd;     // Filename ending
  sstMisc01PrtFilCls oSstPrt;

  int iStat = 0;
  int iStat1 = 0;
//-----------------------------------------------------------------------------

  // Open Protocol with filename
  iStat = oSstPrt.SST_PrtAuf ( 1, (char*) "sst_generate_qttab_lib.prt");

  if (argc <= 1)
  {
    printf("\n");
    printf("Programm generates cpp code library with qt table model objects from def-file\n");
    printf("\n");
    printf("ERROR: Call sst_generate_qttab_lib vartype.def\n");
    printf("\n");

    oSstPrt.SST_PrtZu(1);
    return 0;
  }

  // Open Casc Object for reading
  cFilNamEnd = argv[1];
  iStat = sImpFile.fopenRd( 0, cFilNamEnd.c_str());
  if (iStat < 0)
  {
    printf("Can not open file: %s\n", cFilNamEnd.c_str());
    oSstPrt.SST_PrtZu(0);
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
      oSstPrt.SST_PrtWrtInt4( 1,dRecNo+1,(char*)"Row Number: ");
      oSstPrt.SST_PrtWrtChar(1, (char*)sErrTxt.c_str(),(char*) "Could not interpret: ");
      oSstPrt.SST_PrtZu(0);
      return -1;
    }
    // assert(iStat==0);

    // Weiteren User-Datensatz in Datenspeicher schreiben.
    iStat = DsVerw.WritNew( 0, &oStrType, &dRecNo);

    sFileRow.clear();

    // Eine Zeile aus Ascii-Datei lesen.
    iStat1 = sImpFile.Rd_StrDS1( 0, &sFileRow);
  }

  // CascObjekt beenden und zugehцrige Datei schlieЯen.
  iStat = sImpFile.fcloseFil(0);

  // Set Name of system
  sSysNam = oStrType.Get_SysNam();

  int iKey = 2;

  switch (iKey) {
  case 0:
  { // Write all classes in different code and header files

    //=============================================================================
    // Write Type classes to system header and Typ class file
    iStat = sstcsv_FilWrtClsTypOpen ( 0, &DsVerw, sSysNam, sDateStr);

    //=============================================================================
    // Write Function classes to system header and fnc class file
    iStat = sstcsv_FilWrtClsFncOpen ( 0, &DsVerw, sSysNam, sDateStr);
  }
    break;
  case 1:
  { // Write all defintions in one header file
    // write all classes in separate files
    //=============================================================================
    // Write Type classes to system header and Typ class file
    iStat = sstcsv_FilWrtClsTypOpen2 ( 0, &DsVerw, sSysNam, sDateStr);

    //=============================================================================
    // Write Function classes to system header and fnc class file
    iStat = sstcsv_FilWrtClsFncOpen2 ( 0, &DsVerw, sSysNam, sDateStr);
  }
    break;
  case 2:
  {
    // Write all defintions in one header file
    // Write typ  and fnc code in one class code file
    iStat = sstcsv_FilWrtClsFncOpen3 ( 0, &DsVerw, sSysNam, sDateStr);
  }
    break;
  default:
    break;
  }

  // Close protocol file
  oSstPrt.SST_PrtZu(1);

  return 0;
}
//=============================================================================
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

  // CascObjekt цffnen zum Schreiben.
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
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass, "");

  //===========================================================================

  // Die Anzahl der aktuell gespeicherten Datensдtze zurьckgeben.
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / цffnen.
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
      // iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppTypClass);
      iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &oCppTypClass);

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

      // Datensatz-Verwaltung anlegen / цffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);

  }

  // Write last class data to files
  // iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppTypClass);
  iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &oCppTypClass);

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
int sstcsv_FilWrtClsTypOpen2 (int          iKey,
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
  sstCpp01_Class_Cls oCppTypBaseClass;  // One Type Class with all Elements, functions and function code blocks
  sstCpp01_ClsTyp_Cls oCppClsTyp1;  // for type class, extended var type
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

  // Write Type classes to header and class file

  // iStat = Str1Cpy(0, &sGrpNam,(char*)"Typ");
  sGrpNam = "Typ";
  sHedFilNam = sSysNam;
//  sHedFilNam = sHedFilNam + "_";
//  sHedFilNam = sHedFilNam + sGrpNam;
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt цffnen zum Schreiben.
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());
  // iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

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

  // iStat = sstCpp01_Hed_wrt_defgroup(0,&sHedFil, &sGrpNam);
  iStat = sstCpp01_Hed_wrt_defgroup(0,&sHedFil, oCppTypClass.GetSysNam());

  //===========================================================================
//  iStat = oCppTypClass.GetDate( 0, &sDateStr);

//  // write headrows in cpp header file
//  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

//  // Write comment and includes to cls file
//  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass);

  //===========================================================================

  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypBaseClass);

  oCppTypBaseClass.SetDate( 0, sDateStr);

  oCppTypBaseClass.SetClsNam(0,"sstDxf01LibTypBase");
  oCppTypBaseClass.SetSysNam(0,"sstDxf01Lib");
  oCppTypBaseClass.SetGrpNam(0,"Typ");

  sstStr01VarDefCls oVarUserDef;
  oVarUserDef.Set_EleNam("sstStr01Cls oCsvCnvt");
  oVarUserDef.Set_EleInfo("oCsvCnvt Info");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppTypBaseClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &SatzNr);

  // Write last type class data to class and header file
  // iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppTypBaseClass);
  iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &oCppTypBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypBaseClass);

  //===========================================================================

  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // Die Anzahl der aktuell gespeicherten Datensдtze zurückgeben.
  eTypeNum = DsVerw->count();

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = DsVerw->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    // size_t dPos = oStrTypeAct.Get_ObjNam().find(oStrType.Get_ObjNam());
    size_t dPos1 = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());
    // size_t dPos2 = oStrTypeAct.Get_ObjNam().npos;
//     if (dPos1 != oStrTypeAct.Get_ObjNam().npos)
    if (dPos1 != 0)
    {

      // Write last type class data to class and header file
      // iStat = sst_WrtClsData_inPipe_toFilesT ( 1, &sHedFil, &sCppFil, &oCppTypClass);
      iStat = sst_WrtClsData_inPipe_toFilesT ( 1, &sHedFil, &oCppTypClass);

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

      // Datensatz-Verwaltung anlegen / цffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);

  }

  // Write last class data to files
  // iStat = sst_WrtClsData_inPipe_toFilesT ( 1, &sHedFil, &sCppFil, &oCppTypClass);
  iStat = sst_WrtClsData_inPipe_toFilesT ( 1, &sHedFil, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // write define end rows in cpp header file
  // iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

  // Close HedFil object and File inside
  // iStat = sCppFil.fcloseFil(0);
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

  // sGrpNam = "FncOpen";
  sGrpNam = "Fnc";

  sHedFilNam = sSysNam;
  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + sGrpNam;
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt цffnen zum Schreiben.
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
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass, "");

  //===========================================================================
  // Die Anzahl der aktuell gespeicherten Datensдtze zurьckgeben.
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / цffnen.
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
      // iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);
      iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sGrpNam, &oCppTypClass);

      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrType.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrType.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      oStrTypeAct = oStrType;

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / цffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;

    // SatzNr = DS1_DsShrNeu ( 0, &oCppTypClass.ClsTypDsVerw, &oCppClsTyp1);
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);


  }

  // Write last class data to files
  // iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);
  iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sGrpNam, &oCppTypClass);

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
int sstcsv_FilWrtClsFncOpen2 (int          iKey,
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
  sstCpp01_Class_Cls oCppFncBaseClass;
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

  // sGrpNam = "FncOpen";
  sGrpNam = "Fnc";

  sHedFilNam = sSysNam;
//  sHedFilNam = sHedFilNam + "_";
//  sHedFilNam = sHedFilNam + sGrpNam;
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sHedFil.fopenAppend( 0, sHedFilNam.c_str());
  // iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================

  // write headrows in cpp file
  // iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

  // Write comment to cpp header file
  // iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, &sSysNam);

  // write define open rows in cpp header file
  // iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sSysNam,
  //                                   sGrpNam, "");

  //===========================================================================
//  iStat = oCppTypClass.GetDate( 0, &sDateStr);

//  // write headrows in cpp header file
//  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

//  // Write comment and includes to cls file
//  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass);

  //===========================================================================c
  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncBaseClass);

  oCppFncBaseClass.SetDate( 0, sDateStr);

  oCppFncBaseClass.SetClsNam(0,"sstDxf01LibFncBase");
  oCppFncBaseClass.SetSysNam(0,"sstDxf01Lib");
  oCppFncBaseClass.SetGrpNam(0,"Typ");

  sstStr01VarDefCls oVarUserDef;
  oVarUserDef.Set_EleNam("sstStr01Cls oCsvCnvt");
  oVarUserDef.Set_EleInfo("oCsvCnvt Info");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppFncBaseClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &SatzNr);

  // Write last type class data to class and header file
  // iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &sCppFil, &oCppFncBaseClass);
  iStat = sst_WrtClsData_inPipe_toFilesT ( 0, &sHedFil, &oCppFncBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncBaseClass);
  //===========================================================================

  // Die Anzahl der aktuell gespeicherten Datensдtze zurьckgeben.
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / цffnen.
  // Open Dss Set 1 for Class Group 2
  // Open Dss Set 2 for Class Group 2
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = DsVerw->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    // size_t dStrPos = oStrTypeAct.Get_ObjNam().find(oStrType.Get_ObjNam());
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());
    // if (dStrPos == oStrType.Get_ObjNam().npos)
    if (dStrPos != 0)
    {

      // Write last type class data to class and header file
      // iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);
      iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sGrpNam, &oCppTypClass);

      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrType.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrType.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      oStrTypeAct = oStrType;

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / цffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;

    // SatzNr = DS1_DsShrNeu ( 0, &oCppTypClass.ClsTypDsVerw, &oCppClsTyp1);
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);


  }

  // Write last class data to files
  // iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sCppFil, &sGrpNam, &oCppTypClass);
  iStat = sst_WrtClsData_inPipe_toFilesF ( 0, &sHedFil, &sGrpNam, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

  // Close HedFil object and File inside
  iStat = sHedFil.fcloseFil(0);
  // iStat = sCppFil.fcloseFil(0);


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
int sstcsv_FilWrtClsFncOpen3 (int          iKey,
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
  sstCpp01_Class_Cls oCppTypBaseClass;
  sstCpp01_Class_Cls oCppFncBaseClass;
  sstCpp01_ClsTyp_Cls oCppClsTyp1;  // for type class
  dREC04RECNUMTYP eTypeNum = 0;
  dREC04RECNUMTYP SatzNr = 0;
  // std::string oAddIncFilNam = "list;dl_dxf.h;dl_creationadapter.h;rs_vector.h;QtWidgets;sstQt01Lib.h;sstQt01LibInt.h;sstDxf03Lib.h;sstDxf03LibInt.h";
  std::string oAddIncFilNam = "list;dl_dxf.h;dl_creationadapter.h;rs_vector.h;QtWidgets;sstQt01Lib.h;sstDxf03Lib.h";


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

  // sGrpNam = "FncOpen";
  sGrpNam = "TabMdl";

  sHedFilNam = sSysNam;
//  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + "Lib";
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());
  // iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================

   // write headrows in cpp file
   iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

   // Write comment to cpp header file
   iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, &sSysNam);

   // write define open rows in cpp header file
   iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sSysNam,
                                     sGrpNam, "");

   // write doxygen def group to header file
   iStat = sstCpp01_Hed_wrt_defgroup(0,&sHedFil, oCppTypClass.GetSysNam());

  //===========================================================================
  // write type base class.
  sCppFilNam = sSysNam;
  // sCppFilNam = sCppFilNam + "_";
  // sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + "Base";
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = sCppFil.fcloseFil(0);
   iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

  // Write comment and includes to base cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass, "");

  // Open all tables of CppClass
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypBaseClass);

  oCppTypBaseClass.SetDate( 0, sDateStr);

  oCppTypBaseClass.SetClsNam(0,"Base");
  oCppTypBaseClass.SetSysNam( 0, sSysNam);
  oCppTypBaseClass.SetGrpNam(0,"Typ");

  // Write base type class data to class and header file
  iStat = sst_WrtClsData_inPipe_toFilesT2 ( 0, &sHedFil, &sCppFil, "Typ", &oCppTypBaseClass);

  //===========================================================================c
  // Write Fnc base class.
  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncBaseClass);

  oCppFncBaseClass.SetDate( 0, sDateStr);

  oCppFncBaseClass.SetClsNam(0,"Base");
  oCppFncBaseClass.SetSysNam(0,sSysNam);
  oCppFncBaseClass.SetGrpNam(0,"TabMdl");

  sstStr01VarDefCls oVarUserDef;
  oVarUserDef.Set_EleNam("sstStr01Cls oCsvRow");
  oVarUserDef.Set_EleInfo("oCsvCnvt Info");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppFncBaseClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &SatzNr);

  // Write base class data to class and header file
  iStat = sst_WrtClsData_inPipe_toFilesT2 ( 0, &sHedFil, &sCppFil, "QtTab", &oCppFncBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncBaseClass);
  iStat = sCppFil.fcloseFil(0);
  //===========================================================================

  // Return number of TypDef records from file
  eTypeNum = DsVerw->count();

  // Datensatz-Verwaltung anlegen / \D6ffnen.
  // Open Dss Set 1 for Class Group 2
  // Open Dss Set 2 for Class Group 2
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = DsVerw->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    dREC04RECNUMTYP dNumTypRecsAct = oCppTypClass.ClsTypDsVerw->count();

    // if (dStrPos == oStrType.Get_ObjNam().npos)
    if (dStrPos != 0 && dNumTypRecsAct > 1)
    {

       // Class name in table changed: new Class !
       // store class in pipe and start new one, if not empty

//===========================================================================
      sCppFilNam = oStrTypeAct.Get_SysNam();
      sCppFilNam += sGrpNam;
      sCppFilNam = sCppFilNam + oStrTypeAct.Get_ObjNam();
      sCppFilNam = sCppFilNam + ".cpp";

      iStat = sCppFil.fcloseFil(0);
      iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

      iStat = oCppTypClass.GetDate( 0, &sDateStr);
      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      // write headrows in cpp header file
      iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

      // Write comment and includes to cls file
      iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass, oAddIncFilNam);

      // Write last type class data to class and header file
      iStat = sst_WrtClsData_inPipe_toFilesF2 ( 0, &sHedFil, &sCppFil, "TabMdl", &oCppTypClass);

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / \F6ffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);
    }

    oStrTypeAct = oStrType;

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;

    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
  }

  sCppFilNam = oStrTypeAct.Get_SysNam();
  sCppFilNam += sGrpNam;
  sCppFilNam = sCppFilNam + oStrTypeAct.Get_ObjNam();
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = sCppFil.fcloseFil(0);
   iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  iStat = oCppTypClass.GetDate( 0, &sDateStr);
  // save class name for member class
  strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppTypClass, oAddIncFilNam);

  // Write last class data to files
  iStat = sst_WrtClsData_inPipe_toFilesF2 ( 0, &sHedFil, &sCppFil, "TabMdl", &oCppTypClass);

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
//                                    sstMisc01AscFilCls   *sClsFil,
                                    sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_ClsFnc_Cls oCppClsFnc1;  // functions for type class

  dREC04RECNUMTYP lSatzNr = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  // if ( iKey != 0) return -1;
  if ( iKey < 0 || iKey > 1) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls oCppFil;
  std::string sDateStr;

  sCppFilNam = oCppTypClass->GetClsNam();
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = oCppFil.fopenWr( 0, sCppFilNam.c_str());

  iStat = oCppTypClass->GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &oCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &oCppFil, oCppTypClass, "");
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

  if (iKey == 1)
  {

  // Only derived classes, no base classes

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

  }

  //===========================================================================

  // write information to cpp header file of member class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, oCppTypClass);

  // write information to cpp class file of member class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &oCppFil, oCppTypClass);

  iStat = oCppFil.fcloseFil(0);


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
//                                     sstMisc01AscFilCls   *sClsFil,
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


  //===========================================================================

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam->c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppFncClass.cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncat(oCppFncClass.cClsNam,oCppFncClass.cGrpNam, dSST_STR01_VAR_NAM_LEN);
  strncat(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);
  //===========================================================================
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls oCppFil;
  std::string sDateStr;

  sCppFilNam = oCppFncClass.GetClsNam();
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = oCppFil.fopenWr( 0, sCppFilNam.c_str());
  iStat = oCppTypClass->GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &oCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &oCppFil, &oCppFncClass, "");
  //===========================================================================

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
  iStat = sstCpp01_wrt2CppClsFil2 ( 1, &oCppFil, &oCppFncClass);

  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncClass);

  iStat = oCppFil.fcloseFil(0);

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
int sst_WrtClsData_inPipe_toFilesT2 (int               iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstMisc01AscFilCls   *sClsFil,
                                     std::string      sGrpNam,
                                    sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  // sstCpp01_Class_Cls oCppFncClass;
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // functions for type class

  std::string oLocClsNam;   // Local class name
  // std::string oLocFncClsNam;   // Local func class name

  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;


  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  // if ( iKey != 0) return -1;
  if ( iKey < 0 || iKey > 1) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================
//  std::string sCppFilNam;  // Nam of cpp file
//  sstMisc01AscFilCls oCppFil;
//  std::string sDateStr;

//  sCppFilNam = oCppTypClass->GetClsNam();
//  sCppFilNam = sCppFilNam + ".cpp";

//  iStat = oCppFil.fopenWr( 0, sCppFilNam.c_str());

//  iStat = oCppTypClass->GetDate( 0, &sDateStr);

//  // write headrows in cpp header file
//  iStat = sstCpp01_Fil_wrt_head ( 0, &oCppFil, &sDateStr);

//  // Write comment and includes to cls file
//  iStat = sstCpp01_Cls_WrtInc( 1, &oCppFil, oCppTypClass);
//===========================================================================

//  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
//  strncpy(oCppFncClass.cGrpNam,sGrpNam.c_str(), dSST_STR01_VAR_NAM_LEN);
//  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);

  // define new TYPE class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;

  oCppClsFnc.lBlcStart=1;
  // Fill inside of typ constructor class function.
  oCppClsFnc.lBlcRows = lSatzNr - oCppClsFnc.lBlcStart + 1;

  oCppTypClass->SetGrpNam(0, sGrpNam);
  // oLocFncClsNam = oCppFncClass.GetLibClsNam();

  // oLocClsNam = oCppTypClass->GetSysNam()+oCppTypClass->GetGrpNam()+oCppTypClass->GetClsNam();
  oLocClsNam = oCppTypClass->GetLibClsNam();

//  strncpy(oCppClsFnc1.cClsNam,oCppTypClass->cClsNam,dSST_STR01_VAR_NAM_LEN);
//  strncpy(oCppClsFnc1.cFncNam,oCppTypClass->cClsNam,dSST_STR01_VAR_NAM_LEN);  // function name constructor
  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name constructor
  strncpy( oCppClsFnc.cFncPar, "", dCPPFILROWLENGTH);
  strncpy( oCppClsFnc.cFncCom, "Constructor", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //===========================================================================

  if (iKey == 1)
  {

  // Only derived classes, no base classes

  // define new TYPE class function: SetTestData
  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;

  oCppClsFnc.lBlcStart = lSatzNrBlc + 1;
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart + 1;

  strcpy(oCppClsFnc.cClsNam,oCppTypClass->cClsNam);
  strcpy(oCppClsFnc.cFncNam,(char*)"SetTestData");
  strcpy(oCppClsFnc.cFncPar,"");
  strcpy(oCppClsFnc.cFncCom,"/**< Set Test Data */");
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  }

  //===========================================================================

  // define new FUNCTION class set and write: Number
  oCppClsFnc.eCppType = sstStr01UInt; // Return Type
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = sstCpp01_CsvLib_FillBlc_Number ( 0,  oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;
  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getMemberNumber", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"// Get Number of Class member", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: StringName
  oCppClsFnc.eCppType = sstStr01String;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = sstCpp01_CsvLib_FillBlc_StrNam ( 0, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getStringName", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"// Csv Write Function", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: StringType
  oCppClsFnc.eCppType = sstStr01String;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = sstCpp01_CsvLib_FillBlc_StrTyp ( 0, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getStringType", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"// Csv Write Function", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------


  //===========================================================================

  // write information to cpp header file of member class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, oCppTypClass);

  // write information to cpp class file of member class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, sClsFil, oCppTypClass);

  // iStat = oCppFil.fcloseFil(0);


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
int sst_WrtClsData_inPipe_toFilesF2 (int               iKey,
                                     sstMisc01AscFilCls   *sHedFil,
                                     sstMisc01AscFilCls   *sClsFil,
                                     std::string      sGrpNam,
                                     sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_Class_Cls oCppFncClass;

  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class

  sstStr01Cls oFmtInfoObj; // Infos about input output format

  std::string oLocTypClsNam;   // Local type class name
  std::string oLocFncClsNam;   // Local func class name

  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);
  oCppFncClass.setExtBaseCls("sstQt01TabMdlCls");

  //===========================================================================

  oLocTypClsNam = oCppTypClass->GetLibClsNam();
  oLocFncClsNam = oCppFncClass.GetLibClsNam();

  //===========================================================================

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  // Define Database Class Element
  sstStr01VarDefCls oVarUserDef;
  std::string oClsNam = "sstDxf03Fnc" + (std::string) oCppTypClass->cClsNam + "Cls";
  // oVarUserDef.Set_EleNam("sstStr01Cls oDataTable");
  oVarUserDef.Set_EleNam(oClsNam + " oDataTable");
  oVarUserDef.Set_EleInfo("sstStr01Cls oDataTable");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);

  oClsNam = "sstDxf03Typ" + (std::string) oCppTypClass->cClsNam + "Cls";
  // oVarUserDef.Set_EleNam("sstStr01Cls oDataTable");
  oVarUserDef.Set_EleNam(oClsNam + " oTypeRec");
  oVarUserDef.Set_EleInfo("sstStr01Cls oDataTable");
  oVarUserDef.Set_Type(sstStr01Custom);

  // sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);


  // define new FUNCTION class set and write: constructor

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function
  oCppClsFnc.lBlcStart = 0;
  oCppClsFnc.lBlcRows = 0;
  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  // strncpy(oCppClsFnc.cFncPar,"QObject *parent):sstQt01TabMdlCls(parent", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncPar,"QObject *parent", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"// Constructor", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------

  // rowCount
  // oCppClsFnc.eCppType = sstStr01Int;  // Return type
  oCppClsFnc.eCppType = sstStr01ULong;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = 1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_rowCount ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc;
//  oCppClsFnc.lBlcStart = 0;
//  oCppClsFnc.lBlcRows = 0;
  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"rowCount", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex &", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"Count actual number of records", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // columnCount

  oCppClsFnc.eCppType = sstStr01Int;  // Return type
  // oCppClsFnc.eCppType = sstStr01ULong;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

    oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_columnCount ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"columnCount", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex &", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // data

  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_data ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"data", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"QVariant", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex &index, int role", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // headerData
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_HeaderData ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"headerData", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"QVariant", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"int section, Qt::Orientation orientation, int role", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // setData
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_setData ( 0,&oFmtInfoObj,  oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"setData", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"bool", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex & index, const QVariant & value, int role", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // flags
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_flags ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"flags", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"Qt::ItemFlags", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex &index", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // removeRows
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_removeRows ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"removeRows", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"bool", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"int position, int rows, const QModelIndex &index", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // insertRows
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = sstCpp01_CsvLib_FillBlc_insertRows ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"insertRows", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"bool", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"int position, int rows, const QModelIndex &index", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------

  // write doxy/class information to cpp header file of function class
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
