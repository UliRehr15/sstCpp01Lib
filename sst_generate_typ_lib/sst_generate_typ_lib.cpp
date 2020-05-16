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

#include "sst_generate_typ_lib.h"

//=============================================================================
int main(int argc, char *argv [])
{

  std::string sDateStr;  // Generating Date
  std::string sSysNam;

  std::string sTypDefFilNam;
  sstMisc01PrtFilCls oSstPrt;

  sstCppGenTypLibCls oGenTyp;

  int iStat = 0;
  // int iStat1 = 0;
//-----------------------------------------------------------------------------

  // Open Protocol with filename
  iStat = oSstPrt.SST_PrtAuf ( 1, (char*) "sst_generate_typ_lib.prt");
  assert(iStat >= 0);

  if (argc <= 1)
  {
    printf("\n");
    printf("Call sst_generate_typ_lib typelib.def\n");
    printf("\n");
    printf("Programm generates cpp library for typ/csv io from def-file\n");

    oSstPrt.SST_PrtZu(1);
    return 0;
  }

  sstCppTypDefTabCls oTypDefTab(&oSstPrt);

  // Open Casc Object for reading
  sTypDefFilNam = argv[1];

  oGenTyp.setGrpNam("Typ");
  sDateStr = "21.03.18";

  iStat = oTypDefTab.LoadTypDefFromFile(0,sTypDefFilNam);
  if (iStat < 0)
  {
    oSstPrt.SST_PrtZu(1);
    return 0;
  }

  // Set Name of system
  sSysNam = oTypDefTab.getSysNam();

  iStat = oGenTyp.sstcsv_FilWrtClsTypOpen2 ( 0, &oTypDefTab, sDateStr);

  // Close protocol file
  oSstPrt.SST_PrtZu(1);

  return 0;
}
//=============================================================================
int sstCppGenTypLibCls::sstcsv_FilWrtClsTypOpen2 (int                 iKey,
                                                  sstCppTypDefTabCls *oTypeDefTable,
                                                  std::string         sDateStr)
//-----------------------------------------------------------------------------
{
  std::string sGrpNam;  // Nam of function group, f.e. Typ, Fnc or Dbs
  std::string sSysNam;  // Nam of function group, f.e. Typ, Fnc or Dbs

  std::string sHedFilNam;  // Nam of header file
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls sHedFil;

  sstStr01VarDefCls oStrType;
  sstStr01VarDefCls oStrTypeAct;  // actual class element
  sstCpp01_Class_Cls oCppTypClass;  // One Type Class with all Elements, functions and function code blocks
  sstCpp01_Class_Cls oCppTypBaseClass;  // One Type Class with all Elements, functions and function code blocks
  sstCpp01_ClsTyp_Cls oCppClsTyp1;  // for type class, extended var type
  dREC04RECNUMTYP dTypeDefTabRecNum = 0;
  dREC04RECNUMTYP SatzNr = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  sGrpNam = this->getGrpNam();
  sSysNam = oTypeDefTable->getSysNam();

  // Set Date in typ class
  iStat = oCppTypClass.SetDate ( 0, sDateStr);

  // Reset values
  strncpy(oCppTypClass.cClsNam,"",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cGrpNam,sGrpNam.c_str(),dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,sSysNam.c_str(),dSST_STR01_VAR_NAM_LEN);

  // Write Type classes to header and class file

  // iStat = Str1Cpy(0, &sGrpNam,(char*)"Typ");
  sGrpNam = "Typ";
  sHedFilNam = sSysNam;
//  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + sGrpNam + "Lib";
  sHedFilNam = sHedFilNam + ".h";

  sCppFilNam = sSysNam;
  sCppFilNam = sCppFilNam + "_";
  sCppFilNam = sCppFilNam + sGrpNam;
  sCppFilNam = sCppFilNam + ".cpp";

  // CascObjekt öffnen zum Schreiben.
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


  //=== Write Enum Class to Header ============================================

  // Return number of TypDef records from file
  dTypeDefTabRecNum = oTypeDefTable->count();

  {
    sstCpp01_Class_Cls oCppEnumClass;
    iStat = sstCpp01_ClassTab_Open ( 0, &oCppEnumClass);

    oCppEnumClass.SetDate( 0, sDateStr);
    oCppEnumClass.SetClsNam(0,"Base");
    oCppEnumClass.SetSysNam(0,sSysNam);
    oCppEnumClass.SetGrpNam(0,"Typ");

    for (dREC04RECNUMTYP ii = 1; ii <= dTypeDefTabRecNum; ii++)
    {

      // Datensatz an absoluter Position lesen.
      iStat = oTypeDefTable->Read( 0, ii, &oStrType);

      // if object name is different to actual object name, open new object
      size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

      if (dStrPos != 0)
      {

        oCppClsTyp1.eClsVisiTyp = myClsPublic;
        oCppClsTyp1.sClsMem = oStrType;

        iStat = oCppEnumClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
      }

      oStrTypeAct = oStrType;

    }

    iStat = this->WriteEnumCls( 0, &sHedFil, &oCppEnumClass);
    iStat = sstCpp01_ClassTab_Close ( 0, &oCppEnumClass);
  }

  //===========================================================================

  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypBaseClass);

  oCppTypBaseClass.SetDate( 0, sDateStr);

  oCppTypBaseClass.SetClsNam(0,"Base");
  oCppTypBaseClass.SetSysNam(0,oTypeDefTable->getSysNam());
  oCppTypBaseClass.SetGrpNam(0,this->getGrpNam());

  sstStr01VarDefCls oVarUserDef;
  oVarUserDef.Set_EleNam("sstStr01Cls oCsvCnvt");
  oVarUserDef.Set_EleInfo("oCsvCnvt Info");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppTypBaseClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &SatzNr);

  // Write last type class data to class and header file
  iStat = sst_WrtClsData_inPipe_toFilesT2 ( 0, &sHedFil, sGrpNam, &oCppTypBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypBaseClass);

  //===========================================================================

  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  dTypeDefTabRecNum = oTypeDefTable->count();

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= dTypeDefTabRecNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oTypeDefTable->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dPos1 = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());
    if (dPos1 != 0)
    {

      // Write one type class data to class and header file
      iStat = this->sst_WrtClsData_inPipe_toFilesT2 ( 1, &sHedFil, sGrpNam, &oCppTypClass);

      // save class name for member class
      strncpy(oCppTypClass.cSysNam,oStrType.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cGrpNam,sGrpNam.c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cClsNam,oStrType.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN); // Class name plus group name


      oStrTypeAct = oStrType;

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / Ñffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

    }

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;
    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);

  }

  // Write last class data to files
  // iStat = sst_WrtClsData_inPipe_toFilesT ( 1, &sHedFil, &oCppTypClass);
  iStat = this->sst_WrtClsData_inPipe_toFilesT2 ( 1, &sHedFil, sGrpNam, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

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
int sstCppGenTypLibCls::sst_WrtClsData_inPipe_toFilesT2 (int               iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    // sstMisc01AscFilCls   *sClsFil,
                                     std::string      sGrpNam,
                                    sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_Class_Cls oCppFncClass;
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // functions for type class
  sstStr01Cls      oFormatInfo;

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
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls oCppFil;
  std::string sDateStr;

  sCppFilNam = oCppTypClass->GetSysNam();
  sCppFilNam += oCppTypClass->GetGrpNam();
  sCppFilNam += oCppTypClass->GetClsNam();
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = oCppFil.fopenWr( 0, sCppFilNam.c_str());

  iStat = oCppTypClass->GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &oCppFil, &sDateStr);

  // Write comment and includes to cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &oCppFil, oCppTypClass,"");
//===========================================================================

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);

  // define new TYPE class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;


  lSatzNrBlc = 0;
  // Fill inside of typ constructor class function.
  iStat = this->sstCpp01_CsvLib_FillBlc_Constructor( 0,  oCppTypClass, oCppTypClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart;
  oCppClsFnc.lBlcStart = lSatzNrBlc;

  oCppTypClass->SetGrpNam(0, sGrpNam);
  // oLocFncClsNam = oCppFncClass.GetLibClsNam();

  // oLocClsNam = oCppTypClass->GetSysNam()+oCppTypClass->GetGrpNam()+oCppTypClass->GetClsNam();
  oLocClsNam = oCppTypClass->GetLibClsNam();

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
//  oCppClsFnc.eCppType = sstStr01Int;
//  oCppClsFnc.eClsVisiTyp = myClsPublic;

//  oCppClsFnc.lBlcStart = lSatzNrBlc + 1;
//  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart + 1;

//  strcpy(oCppClsFnc.cClsNam,oCppTypClass->cClsNam);
//  strcpy(oCppClsFnc.cFncNam,(char*)"SetTestData");
//  strcpy(oCppClsFnc.cFncPar,"");
//  strcpy(oCppClsFnc.cFncCom,"/**< Set Test Data */");
//  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  }

  //===========================================================================

  // define new FUNCTION class set and write: Number
  oCppClsFnc.eCppType = sstStr01UInt; // Return Type
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = this->sstCpp01_CsvLib_FillBlc_Number ( 0,  oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;
  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getMemberNumber", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Get Number of Class member", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: StringName
  oCppClsFnc.eCppType = sstStr01String;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = this->sstCpp01_CsvLib_FillBlc_StrNam ( 0, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getStringName", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Get Csv-String with all Class member names", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: StringType
  oCppClsFnc.eCppType = sstStr01String;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block
  iStat = this->sstCpp01_CsvLib_FillBlc_StrTyp ( 0, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"getStringType", dSST_STR01_VAR_NAM_LEN);

  memset(oCppClsFnc.cFncPar,0,dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Get Csv-String with all Class member definition types", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: READ

  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  // oCppClsFnc.lBlcStart = 1;

  // Fill Function Block Read
  iStat = this->sstCpp01_CsvLib_FillBlc_Read ( 0, &oFormatInfo, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;
  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"Csv_Read", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc.cFncPar,"int iKey, std::string *sErrTxt, std::string *s", dCPPFILROWLENGTH);
  strncat(oCppClsFnc.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  // strncat(oCppClsFnc.cFncPar,"_Str, ", dCPPFILROWLENGTH);
  strncat(oCppClsFnc.cFncPar,"_Str", dCPPFILROWLENGTH);

  // strncat(oCppClsFnc.cFncPar, oLocClsNam.c_str(), dCPPFILROWLENGTH);

  // build variable oVarName
//  strncat(oCppClsFnc.cFncPar, " *o", dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Csv Read Function", dCPPFILROWLENGTH);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: WRITE
  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Write
  iStat = sstCpp01_CsvLib_FillBlc_Write ( 0, &oFormatInfo, oCppTypClass, oCppTypClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;
  strncpy( oCppClsFnc.cClsNam, oLocClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncNam,"Csv_Write", dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncPar,"int iKey ", dCPPFILROWLENGTH);

  // strncat(oCppClsFnc.cFncPar, oLocClsNam.c_str(), dCPPFILROWLENGTH);

  // build variable oVarName
//  strncat(oCppClsFnc.cFncPar, " *o", dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cGrpNam, dCPPFILROWLENGTH);
//  strncat(oCppClsFnc.cFncPar, oCppTypClass->cClsNam, dCPPFILROWLENGTH);

  strncat(oCppClsFnc.cFncPar,", std::string *s", dCPPFILROWLENGTH);
  strncat(oCppClsFnc.cFncPar, oCppTypClass->cSysNam, dCPPFILROWLENGTH);
  strncat(oCppClsFnc.cFncPar,"_Str", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Csv Write Function", dCPPFILROWLENGTH);
  // iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  iStat = oCppTypClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //===========================================================================

  // write information to cpp header file of member class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, oCppTypClass);

  // write information to cpp class file of member class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &oCppFil, oCppTypClass);

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
int sstCppGenTypLibCls::WriteEnumCls (int iKey,
                                      sstMisc01AscFilCls  *sHedFil,
                                      sstCpp01_Class_Cls  *poCppEnumClass)
//-----------------------------------------------------------------------------
{
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // write doxy/class information to cpp header file of function class
  //  iStat = sstCpp01_wrt2CppHedFil2 ( 0, sHedFil, poCppEnumClass);

  // write class info/doxygen block in cpp header file
  std::string oLibNam = "SysLib";
  std::string oDateNam = "12.05.2020";
  // iStat = sstCpp01_Hed_wrt_class_info ( 0, sHedFil, oLibNam.c_str(), poCppEnumClass, oDateNam.c_str());

//  enum _PtssTyp_enm {ePtss_Error,
//                     ePtss_HA,
//                     ePtss_HE,
//                     ePtss_ML,
//                     ePtss_PK,
//                     ePtss_LN,
//                     ePtss_FN,
//                     ePtss_PR,
//                     ePtss_FE,
//                     ePtss_SN,
//                     ePtss_FR,
//                     ePtss_SE,
//                     ePtss_ZN,
//                     ePtss_ZE,
//                     ePtss_LE,
//                     ePtss_TN,
//                     ePtss_TT,
//                     ePtss_TE,
//                     ePtss_ON,
//                     ePtss_OD,
//                     ePtss_OE,
//                     ePtss_EN,
//                     ePtss_CM,
//                     ePtss_YN,
//                     ePtss_YE,
//                     ePtss_YL,
//                     ePtss_YA,
//                     ePtss_YB,
//                     ePtss_YD,
//                     ePtss_YX,
//                     ePtss_IN,
//                     ePtss_IE,
//                     ePtss_IL,
//                     ePtss_IA,
//                     ePtss_IB,
//                     ePtss_ID
//                    };
//  typedef enum _PtssTyp_enm PtssTyp_enm;



  std::string oEnumRowStart;
  std::string oEnumRowType;
  std::string oEnumRowEnd;
  std::string oBlankRow;
  std::string oTmpRow;
  oTmpRow = poCppEnumClass->GetSysNam() + poCppEnumClass->GetGrpNam();
  oEnumRowStart = "  enum _" + oTmpRow + "_enm {e" + poCppEnumClass->GetSysNam() + "_Error,";
  oBlankRow     = " ";
  oEnumRowEnd   = "  typedef enum _" + oTmpRow + "_enm " + oTmpRow + "_enm;";

  iStat = sHedFil->Wr_StrDS1(0, &oBlankRow);
  iStat = sHedFil->Wr_StrDS1(0, &oEnumRowStart);

  sstCpp01_ClsTyp_Cls oCppClsTyp1;        // one class member object in type class
  dREC04RECNUMTYP dMemTypeNum = poCppEnumClass->ClsTypDsVerw->count();

  for (dREC04RECNUMTYP ll = 1; ll <= dMemTypeNum; ll++)
  {

    poCppEnumClass->ClsTypDsVerw->Read( 0, ll, &oCppClsTyp1);
    std::string oTmpEleNam;
    oTmpEleNam = oCppClsTyp1.sClsMem.Get_ObjNam();
    oEnumRowType = "                     e" + poCppEnumClass->GetSysNam() + "_" + oTmpEleNam + ",";
    iStat = sHedFil->Wr_StrDS1(0, &oEnumRowType);
  }

  oTmpRow = "                    };";
  iStat = sHedFil->Wr_StrDS1(0, &oTmpRow);
  iStat = sHedFil->Wr_StrDS1(0, &oEnumRowEnd);
  iStat = sHedFil->Wr_StrDS1(0, &oBlankRow);

  // Fatal Errors goes to an assert
  assert(iStat >= 0);

  return iStat;
}
//=============================================================================
