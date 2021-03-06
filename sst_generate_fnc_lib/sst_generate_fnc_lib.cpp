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

#include "sst_generate_fnc_lib.h"

//=============================================================================
int main(int argc, char *argv [])
{

  std::string sDateStr;  // Generating Date

  std::string sTypDefFilNam;
  sstMisc01PrtFilCls oSstPrt;

  sstCppGenFncLibCls oGenFnc;

  int iStat = 0;
//-----------------------------------------------------------------------------

  // Open Protocol with filename
  iStat = oSstPrt.SST_PrtAuf ( 1, (char*) "sst_generate_fnc_lib.prt");
  assert(iStat >= 0);

  if (argc <= 1)
  {
    printf("\n");
    printf("Call sst_generate_fnc_lib typelib.def\n");
    printf("\n");
    printf("Programm generates cpp library for Database io from def-file\n");

    oSstPrt.SST_PrtZu(1);
    return 0;
  }

  sstCppTypDefTabCls oTypDefTab(&oSstPrt);

  // Open Casc Object for reading
  sTypDefFilNam = argv[1];

  // oGenTyp.setGrpNam("Typ");
  oGenFnc.setGrpNam("Fnc");
  sDateStr = "21.03.18";

  // Load all classes from TypeDef File
  iStat = oTypDefTab.LoadTypDefFromFile(0,sTypDefFilNam);
  if (iStat < 0)
  {
    oSstPrt.SST_PrtZu(1);
    assert(0);
  }

  // Write all Class definitions in one header file with extra base class
  // Write code class file for every Type Class with extra base class file
  iStat = oGenFnc.FilWrtClsFncOpen3 ( 0, &oTypDefTab, sDateStr);

  // Close protocol file
  oSstPrt.SST_PrtZu(1);

  return 0;
}
//=============================================================================
int sstCppGenFncLibCls::FilWrtClsFncOpen3 (int                 iKey,
                                           sstCppTypDefTabCls *oTypeDefTable,
                                           std::string         sDateStr)
//-----------------------------------------------------------------------------
{
  std::string sGrpNam;                    // Name of function group, f.e. Typ, Fnc or Dbs
  std::string sSysNam;
  std::string sHedFilNam;                 // Name of header file
  sstMisc01AscFilCls sHedFil;

  sstStr01VarDefCls oStrType;             // next TypeDef Record
  sstStr01VarDefCls oStrTypeAct;          // actual TypeDef Record
  sstCpp01_Class_Cls oCppTypClass;        // One Type class from TypDefTab with all classes
  sstCpp01_Class_Cls oCppFncBaseClass;
  sstCpp01_ClsTyp_Cls oCppClsTyp1;        // one class member object in type class
  dREC04RECNUMTYP dTypeDefTabRecNum = 0;  // Number of records in type def table from file
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
  // strncpy(oCppTypClass.cGrpNam,sGrpNam.c_str(),dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,sSysNam.c_str(),dSST_STR01_VAR_NAM_LEN);

  sHedFilNam = sSysNam;
  sHedFilNam += sGrpNam;
  sHedFilNam = sHedFilNam + "Lib";
  sHedFilNam = sHedFilNam + ".h";
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());

  //===========================================================================

   // write headrows in cpp file
   iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

   // Write comment to cpp header file
   iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, sSysNam, sGrpNam);

   // write define open rows in cpp header file
   iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sSysNam,
                                     sGrpNam, "");

   // write doxygen def group to header file
   iStat = sstCpp01_Hed_wrt_defgroup(0,&sHedFil, oCppTypClass.GetSysNam());

  //===========================================================================
  // write function base class data for loop classes
  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncBaseClass);

  oCppFncBaseClass.SetDate( 0, sDateStr);
  oCppFncBaseClass.SetClsNam(0,"Base");
  oCppFncBaseClass.SetSysNam(0,sSysNam);
  oCppFncBaseClass.SetGrpNam(0,sGrpNam);

  // Write base class data to class and header file without base class
  iStat = this->sst_WrtBaseClsData( 0, &sHedFil, &oCppFncBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncBaseClass);

  //===========================================================================

  // Datensatz-Verwaltung anlegen / Öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  dTypeDefTabRecNum = oTypeDefTable->count();

  // write all cpp header files
  // loop over all entries in typedef file
  for (dREC04RECNUMTYP ii = 1; ii <= dTypeDefTabRecNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oTypeDefTable->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    dREC04RECNUMTYP dNumTypRecsAct = oCppTypClass.ClsTypDsVerw->count();

    // if (dStrPos == oStrType.Get_ObjNam().npos)
    if (dStrPos != 0 && dNumTypRecsAct >= 1)
    {

       // Class name in table changed: new Class !
       // store class in pipe and start new one, if not empty

//===========================================================================

      iStat = oCppTypClass.GetDate( 0, &sDateStr);
      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      // Write last type class data to class and header file with base class
      iStat = this->sst_WrtClsData_inPipe_toFilesF2 ( 1, &sHedFil, &oCppTypClass);

      // Close list of class type definitions
      // Close list of class function definitions
      iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

      // Datensatz-Verwaltung anlegen / öffnen.
      iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);
    }

    oStrTypeAct = oStrType;

    // write new type definition to class list
    oCppClsTyp1.eClsVisiTyp = myClsPublic;
    oCppClsTyp1.sClsMem = oStrType;

    iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
  }

  iStat = oCppTypClass.GetDate( 0, &sDateStr);
  // save class name for member class
  strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

  // Write last class data to files with base class
  iStat = this->sst_WrtClsData_inPipe_toFilesF2 ( 1, &sHedFil, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // === Build Typ Class with all Classes from Def File =======================

  // Datensatz-Verwaltung anlegen / öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  oStrType.clear();
  oStrTypeAct.clear();

  // write all cpp header files
  // loop over all entries in typedef file
  for (dREC04RECNUMTYP ii = 1; ii <= oTypeDefTable->count(); ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oTypeDefTable->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    if (dStrPos != 0)
    {

      // write new type definition to class list
      oCppClsTyp1.eClsVisiTyp = myClsPublic;
      oCppClsTyp1.sClsMem = oStrType;

      oStrTypeAct = oStrType;
      iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
    }

  }

  // === write database class =================================================
  // with all tables

  sstCpp01_Class_Cls oCppFncClass;  // Class defintion for database class

  // Datensatz-Verwaltung anlegen / Öffnen.
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  oCppFncClass.SetSysNam( 0, oStrType.Get_SysNam());
  oCppFncClass.SetGrpNam( 0, "Fnc");
  oCppFncClass.SetClsNam( 0, "Database");
  oCppFncClass.SetDate( 0, sDateStr);

  // Class Name
  std::string oClsNamStr;
  oClsNamStr = oCppFncClass.GetSysNam() + oCppFncClass.GetGrpNam() + "DatabaseCls";
  dREC04RECNUMTYP lSatzNrBlc = 0;

  // Insert all Class elements into Type Store of Class

  for (dREC04RECNUMTYP ii = 1; ii <= dTypeDefTabRecNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oTypeDefTable->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    // if (dStrPos != 0 && ii > 1)
    if (dStrPos != 0)
    {

      std::string oEleNamStr = oStrType.Get_ObjNam();
      sstStr01VarDefCls oStrTypeDb;        // next TypDef Record
      oStrTypeDb.Set_Type(sstStr01Custom);
      oStrTypeDb.Set_ObjNam(oCppFncClass.GetClsNam());
      oStrTypeDb.Set_ObjInfo(oCppFncClass.GetClsNam());
      oStrTypeDb.Set_ObjInfo(oStrType.Get_ObjInfo());
      oStrTypeDb.Set_EleNam(oStrType.Get_SysNam() + sGrpNam + oEleNamStr + "Cls *poTab" + oEleNamStr);
      oStrTypeDb.Set_EleInfo("oTab" + oEleNamStr);
      oStrTypeDb.Set_SysNam(oStrType.Get_SysNam());
      oStrTypeDb.Set_SysInfo(oStrType.Get_SysInfo());

      oCppClsTyp1.eClsVisiTyp = myClsPublic;
      oCppClsTyp1.sClsMem = oStrTypeDb;

      iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
    }

    oStrTypeAct = oStrType;

  }

  // Write Infos for function Constructor to Database Cls <BR>
  iStat = this->FillCls_ConstructorDB( oStrTypeAct, &oCppFncClass);

  // Write Infos for function Destructor to Database Cls <BR>
  iStat = this->FillCls_DestructorDB( oStrTypeAct, &oCppFncClass);

  // write all cpp header files
  // loop over all entries in typedef file
  for (dREC04RECNUMTYP ii = 1; ii <= dTypeDefTabRecNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = oTypeDefTable->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    if (dStrPos != 0 && ii > 1)
    {

      // Write Stuff for Class Element -Functions ReadDb, WriteDb and CountDb into Pipe-Buffer
      iStat = this->sst_WrtClsData_inPipe_toFilesF3( 0, oStrTypeAct, &oCppFncClass);
    }

    oStrTypeAct = oStrType;

    // write new type definition to class list
//    oCppClsTyp1.eClsVisiTyp = myClsPublic;
//    oCppClsTyp1.sClsMem = oStrType;

    // iStat = oCppTypClass.ClsTypDsVerw->WritNew( 0, &oCppClsTyp1, &SatzNr);
  }

  // Write Stuff for Class Element Functions ReadDb, WriteDb and CountDb into Pipe-Buffer
  iStat = this->sst_WrtClsData_inPipe_toFilesF3( 0, oStrTypeAct, &oCppFncClass);

  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class
  dREC04RECNUMTYP lSatzNr = 0;
  lSatzNrBlc = oCppFncClass.ClsBlcDsVerw->count();

  // === Write class Function LoadFromCsvFiless
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_LoadFromCsvFiles( 0, &oCppTypClass, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*) "LoadFromCsvFiles", dSST_STR01_VAR_NAM_LEN);
  // strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Read Database from Csv Files", dCPPFILROWLENGTH);
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;

  // Write Function to Class
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  // === Write class Function SaveToCsvFiles
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_SaveToCsvFiles( 0, &oCppTypClass, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*) "SaveToCsvFiles", dSST_STR01_VAR_NAM_LEN);
  // strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Write Database to Csv Files", dCPPFILROWLENGTH);
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;

  // Write Function to Class
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  // === Write Function LoadAllFromMainFile
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_LoadAllFromMainFile( 0, oStrType, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*) "LoadAllFromMainFile", dSST_STR01_VAR_NAM_LEN);
  // strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Read Database from format main file", dCPPFILROWLENGTH);
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;

  // Write Function to Class
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  // === Write Function SaveAllToMainFile
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_SaveAllToMainFile( 0, oStrType, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*) "SaveAllToMainFile", dSST_STR01_VAR_NAM_LEN);
  // strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Write Database to format main file", dCPPFILROWLENGTH);
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;

  // Write Function to Class
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //---------------------------------------------------------------------------

  std::string oEleNamStr = oStrType.Get_ObjNam();

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type
  sstStr01VarDefCls oStrTypeDb;        // next TypDef Record
  oStrTypeDb.Set_Type(sstStr01Custom);
  oStrTypeDb.Set_ObjNam("");  // Empty because costum
  oStrTypeDb.Set_EleNam(oStrTypeAct.Get_SysNam() + sGrpNam + oEleNamStr + "Cls oTab" + oEleNamStr);
  oStrTypeDb.Set_ObjInfo("Database class for type records");
  oStrTypeDb.Set_SysNam(oStrTypeAct.Get_SysNam());
  oStrTypeDb.Set_SysInfo("");

  oCppVarUserDef.sClsMem = oStrTypeDb;
  // oCppVarUserDef.eClsVisiTyp = myClsPrivate;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  // Write Element to Class
  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);

  // write doxy/class information to cpp header file of function class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, &sHedFil, &oCppFncClass);

  // write information to cpp class file of function class
  // open code class file
  sstMisc01AscFilCls sCppFil;
  std::string sCppFilNam;

  sCppFilNam = oCppFncClass.GetSysNam();
  // sCppFilNam = sCppFilNam + "_";
  sCppFilNam += sGrpNam;
  sCppFilNam += oCppFncClass.GetClsNam();
  sCppFilNam += ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  // write headrows in cpp header file
  std::string oLocDatStr;
  oCppFncClass.GetDate(0,&oLocDatStr);
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &oLocDatStr);
  std::string oAddIncFilNam = oCppTypClass.GetSysNam() + "TypLib.h";

  // Write comment and includes to base cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppFncClass, oAddIncFilNam);

  // write information to cpp class file of member class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &sCppFil, &oCppFncClass);

  // close code class file
  iStat = sCppFil.fcloseFil(0);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncClass);

  //=== End of definition database class ======================================

  // write define end rows in cpp header file
  iStat = sstCpp01_Hed_wrt_def_close ( 0, &sHedFil);

  // Close HedFil object and File inside
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
int sstCppGenFncLibCls::sst_WrtClsData_inPipe_toFilesF2 (int                  iKey,
                                                         sstMisc01AscFilCls  *sHedFil,
                                                         sstCpp01_Class_Cls  *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_Class_Cls oCppFncClass;
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class

  sstMisc01AscFilCls sCppFil;

  std::string oLocFncClsNam;   // Local func class name
  std::string sCppFilNam;      // code class file name

  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  // if ( iKey != 0) return -1;
  if ( iKey < 0 || iKey > 1) return -1;

  std::string oAddIncFilNam = oCppTypClass->GetSysNam() + oCppTypClass->GetGrpNam() + "Lib.h";

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);
  // oCppFncClass.setExtBaseCls("sstQt01TabMdlCls");

  //===========================================================================

  // oLocTypClsNam = oCppTypClass->GetLibClsNam();
  oLocFncClsNam = oCppFncClass.GetLibClsNam();

  // open code class file
  sCppFilNam = oCppTypClass->cSysNam;
  // sCppFilNam = sCppFilNam + "_";
  sCppFilNam += sGrpNam;
  sCppFilNam += oCppTypClass->cClsNam;
  sCppFilNam += ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  // write headrows in cpp header file
  std::string oLocDatStr;
  oCppTypClass->GetDate(0,&oLocDatStr);
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &oLocDatStr);

  // Write comment and includes to base cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, &oCppFncClass, oAddIncFilNam);


  //===========================================================================

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  // Define Database Class Element
  sstStr01VarDefCls oVarUserDef;
  std::string oClsNam = oCppTypClass->GetSysNam() + "Db" + (std::string) oCppTypClass->cClsNam + "Cls";
  oVarUserDef.Set_EleNam(oClsNam + " oDataTable");
  oVarUserDef.Set_EleInfo("sstStr01Cls oDataTable");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);

  oClsNam = oCppTypClass->GetSysNam() + "Typ" + (std::string) oCppTypClass->cClsNam + "Cls";
  oVarUserDef.Set_EleNam(oClsNam + " oTypeRec");
  oVarUserDef.Set_EleInfo("sstStr01Cls oDataTable");
  oVarUserDef.Set_Type(sstStr01Custom);

  // sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);

  // define new FUNCTION class set and write: constructor

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: constructor

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = 0;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_Constructor( 0, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Constructor", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: Destructor

  // define new class set and write: destructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  // oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_Destructor( 0, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*)"~", dSST_STR01_VAR_NAM_LEN);
  strncat( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Destructor", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set: LoadTabFromCsv

  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  // oCppClsFnc.lBlcStart = 1;

  // Fill Function Block Read
  iStat = this->FillBlc_LoadTabFromCsv ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy(oCppClsFnc.cFncNam,"LoadTabFromCsv", dSST_STR01_VAR_NAM_LEN );
  strncpy(oCppClsFnc.cFncPar,"int iKey, const std::string oCsvFilNam, std::string *sErrTxt", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Load all records from csv file into datatable", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new FUNCTION class set: SaveTabToCsv

  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  iStat = this->FillBlc_SaveTabToCsv ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy(oCppClsFnc.cFncNam,"SaveTabToCsv", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc.cFncPar,"int iKey, const std::string oCsvFilNam, std::string *sErrTxt", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Save all records from datatable into Csv file", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // define new FUNCTION class set: Count

  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  iStat = this->FillBlc_Count( 0, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy(oCppClsFnc.cFncNam,"Count", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cRetNam,"dREC04RECNUMTYP", dSST_STR01_VAR_NAM_LEN);

  strncpy(oCppClsFnc.cFncCom,"Count all records in table", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // define new FUNCTION class set: Read

  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  iStat = this->FillBlc_Read( 0, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy(oCppClsFnc.cFncNam,"Read", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc.cFncPar,"int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Read data record from table with record number", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------
  // define new FUNCTION class set: Write

  oCppClsFnc.eCppType = sstStr01Int;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  iStat = this->FillBlc_Write( 0, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy(oCppClsFnc.cFncNam,"Write", dSST_STR01_VAR_NAM_LEN );

  strncpy(oCppClsFnc.cFncPar,"int iKey, dREC04RECNUMTYP *dRecNo, void *vRecAdr", dCPPFILROWLENGTH);

  strncpy(oCppClsFnc.cFncCom,"Write data record to table with record number or new with numer = 0", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);
  //-----------------------------------------------------------------------------

  // write doxy/class information to cpp header file of function class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, &oCppFncClass);

  // write information to cpp class file of function class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &sCppFil, &oCppFncClass);

  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncClass);

  // close code class file
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
int sstCppGenFncLibCls::sst_WrtClsData_inPipe_toFilesF3 (int                   iKey,
                                                         // sstMisc01AscFilCls   *sHedFil,
                                                         // dREC04RECNUMTYP *lSatzNrBlc,
                                                         const sstStr01VarDefCls oStrType,
                                                         // sstCpp01_Class_Cls   *oCppTypClass,
                                                         sstCpp01_Class_Cls   *oCppFncClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // for func class

  sstStr01VarDefCls oStrTypeAct;     // next TypDef Record

  sstMisc01AscFilCls sCppFil;

  std::string oLocFncClsNam;   // Local func class name
  std::string sCppFilNam;      // code class file name

  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;

  // int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();

  oStrTypeAct = oStrType;

  std::string oClsNamStr;
  oClsNamStr = oCppFncClass->GetSysNam() + oCppFncClass->GetGrpNam() + "DatabaseCls";

  // Database method -ReadDbTyp-
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_ReadDb( 0, oStrType, oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  std::string oParamStr;
  oParamStr = "int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr";
  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*)"ReadDb", dSST_STR01_VAR_NAM_LEN);
  strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar, oParamStr.c_str(), dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Read Record from Db Table", dCPPFILROWLENGTH);
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  // Database method -WriteDbTyp-
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_WriteDb( 0, oStrType, oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*)"WriteDb", dSST_STR01_VAR_NAM_LEN);
  strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  // strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncPar,"int iKey, void *vRecAdr, dREC04RECNUMTYP *pdRecNo", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Write Record to Db Tab", dCPPFILROWLENGTH);
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Int;
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  // Database method -CountDbTyp-
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  iStat = this->FillBlc_CountDb( 0, oStrType, oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, (char*) oClsNamStr.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*)"CountDb", dSST_STR01_VAR_NAM_LEN);
  strncat( oCppClsFnc.cFncNam, (char*) oStrTypeAct.Get_ObjNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Count Records from Db Tab", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cRetNam,"dREC04RECNUMTYP", dSST_STR01_VAR_NAM_LEN);  // Return Type
  // oCppClsFnc.eClsVisiTyp = myClsPrivate;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.eCppType = sstStr01Custom;  // Because Return type is not int
  // oCppClsFnc.lBlcStart = 0;
  // oCppClsFnc.lBlcRows = 0;
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

//  std::string oEleNamStr = oStrTypeAct.Get_ObjNam();

//  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type
//  sstStr01VarDefCls oStrTypeDb;        // next TypDef Record
//  oStrTypeDb.Set_Type(sstStr01Custom);
//  oStrTypeDb.Set_ObjNam(oCppFncClass->GetClsNam());
//  oStrTypeDb.Set_EleNam(oStrTypeAct.Get_SysNam() + sGrpNam + oEleNamStr + "Cls *poTab" + oEleNamStr);
//  oStrTypeDb.Set_ObjInfo(oStrTypeAct.Get_ObjInfo());
//  oStrTypeDb.Set_SysNam(oStrTypeAct.Get_SysNam());
//  oStrTypeDb.Set_SysInfo(oStrTypeAct.Get_SysInfo());

//  oCppVarUserDef.sClsMem = oStrTypeDb;
//  // oCppVarUserDef.eClsVisiTyp = myClsPrivate;
//  oCppVarUserDef.eClsVisiTyp = myClsPublic;

//  iStat = oCppFncClass->ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);


  // Fatal Errors goes to an assert
  assert(iStat >= 0);

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::sst_WrtBaseClsData (int               iKey,
                                     sstMisc01AscFilCls   *sHedFil,
                                     sstCpp01_Class_Cls *oCppTypClass)
//-----------------------------------------------------------------------------
{
  sstCpp01_Class_Cls oCppFncClass;

  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class

  sstMisc01AscFilCls sCppFil;

  std::string oLocFncClsNam;   // Local func class name
  std::string sCppFilNam;      // code class file name

  dREC04RECNUMTYP lSatzNr = 0;
  // dREC04RECNUMTYP lSatzNrBlc = 0;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  // if ( iKey != 0) return -1;
  if ( iKey < 0 || iKey > 1) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================

  strncpy(oCppFncClass.cSysNam,oCppTypClass->cSysNam, dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,sGrpNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);

  //===========================================================================

  oLocFncClsNam = oCppFncClass.GetLibClsNam();

  // open code class file
  sCppFilNam = oCppTypClass->cSysNam;
  sCppFilNam += sGrpNam;
  sCppFilNam += oCppTypClass->cClsNam;
  sCppFilNam += ".cpp";

  // CascObjekt öffnen zum Schreiben.
  iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  // write headrows in cpp header file
  std::string oLocDatStr;
  oCppTypClass->GetDate(0,&oLocDatStr);
  iStat = sstCpp01_Fil_wrt_head ( 0, &sCppFil, &oLocDatStr);

  // Write comment and includes to base cls file
  iStat = sstCpp01_Cls_WrtInc( 1, &sCppFil, oCppTypClass, "");

  //===========================================================================

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  // Define Database Class Element
  sstStr01VarDefCls oVarUserDef;
  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type
  std::string oClsNam = "sstRec04Cls";

  oVarUserDef.Set_EleNam(oClsNam + " *poRecTab");
  oVarUserDef.Set_EleInfo("sst Record Table");
  oVarUserDef.Set_Type(sstStr01Custom);

  oCppVarUserDef.sClsMem = oVarUserDef;
  // oCppVarUserDef.eClsVisiTyp = myClsPrivate;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);


  // define new FUNCTION class set and write: constructor

  // iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);

  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = 0;
  oCppClsFnc.lBlcRows = 0;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);
  strncpy(oCppClsFnc.cFncCom,"Constructor", dCPPFILROWLENGTH);
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------

  // write doxy/class information to cpp header file of function class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, &oCppFncClass);

  // write information to cpp class file of function class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &sCppFil, &oCppFncClass);

  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncClass);

  // close code class file
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
