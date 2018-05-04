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

  sstCppGenQtTabLibCls oGenQtTab;

  sstMisc01AscFilCls sImpFile;
  sstMisc01FilNamCls oFilNam;
  std::string sDateStr;  // Generating Date
  std::string sFncSysNam;

  std::string cTypFilNam;     // Filename without ending
  std::string cTypFilNamEnd;  // Filename with ending
  std::string cTypFilEnd;     // Filename ending
  sstMisc01PrtFilCls oSstPrt;

  int iStat = 0;
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
  cTypFilNamEnd = argv[1];
  iStat = sImpFile.fopenRd( 0, cTypFilNamEnd.c_str());
  if (iStat < 0)
  {
    printf("Can not open file: %s\n", cTypFilNamEnd.c_str());
    oSstPrt.SST_PrtZu(0);
    return -1;
  }

  // Split filenamestring to name and ending.
  iStat = oFilNam.SplitExtension( 0, &cTypFilNamEnd, &cTypFilEnd, &cTypFilNam);

  // Set Date of all source and header files
  sDateStr = "06.07.16";


  sstCppTypDefTabCls oTypDefTab(&oSstPrt);

  sDateStr = "21.03.18";

  iStat = oTypDefTab.LoadTypDefFromFile(0,cTypFilNamEnd);
  if (iStat < 0)
  {
    oSstPrt.SST_PrtZu(1);
    assert(0);
  }

  // Set Name of system
  sFncSysNam = "sstQtDxf01";
  oGenQtTab.setGrpNam("TabMdl");

    // Write all defintions in one header file
    // Write typ  and fnc code in one class code file
  iStat = oGenQtTab.sstcsv_FilWrtClsFncOpen3 ( 0, &oTypDefTab, sFncSysNam, sDateStr);

  // Close protocol file
  oSstPrt.SST_PrtZu(1);

  return 0;
}
//=============================================================================
int sstCppGenQtTabLibCls::sstcsv_FilWrtClsFncOpen3 (int          iKey,
                              sstCppTypDefTabCls *poTypDefTab,
                              std::string sFncSysNam,
                              std::string sDateStr)
//-----------------------------------------------------------------------------
{
  std::string sHedFilNam;  // Nam of header file
  sstMisc01AscFilCls sHedFil;

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

  this->oAddCsvIncStr = "list;dl_dxf.h;dl_creationadapter.h;rs_vector.h;QtWidgets;sstQt01Lib.h;sstDxf03TypLib.h;sstDxf03Lib.h";

  // Set Date in typ class
  iStat = oCppTypClass.SetDate ( 0, sDateStr);

  // Reset values
  strncpy(oCppTypClass.cClsNam,"",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cGrpNam,"Typ",dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,poTypDefTab->getSysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

  // sGrpNam = "FncOpen";
  sGrpNam = "TabMdl";

  sHedFilNam = sFncSysNam;
//  sHedFilNam = sHedFilNam + "_";
  sHedFilNam = sHedFilNam + "Lib";
  sHedFilNam = sHedFilNam + ".h";

  // CascObjekt öffnen zum Schreiben.
  iStat = sHedFil.fopenWr( 0, sHedFilNam.c_str());
  // iStat = sCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================

   // write headrows in cpp file
   iStat = sstCpp01_Fil_wrt_head ( 0, &sHedFil, &sDateStr);

   // Write comment to cpp header file
   iStat = sstCpp01_Hed_WrtCom ( 0, &sHedFil, &sFncSysNam);

   // write define open rows in cpp header file
   iStat = sstCpp01_Hed_wrt_def_open ( 0, &sHedFil, "SST", sFncSysNam,
                                     sGrpNam, "");

   iStat = sstCpp01_Hed_wrt_inc( 0, &sHedFil, this->oAddCsvIncStr);


   // write doxygen def group to header file
   iStat = sstCpp01_Hed_wrt_defgroup(0,&sHedFil, oCppTypClass.GetSysNam());

  //===========================================================================c
  // Write Fnc base class.

  iStat = oCppTypClass.GetDate( 0, &sDateStr);

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncBaseClass);

  oCppFncBaseClass.SetDate( 0, sDateStr);

  oCppFncBaseClass.SetClsNam( 0, "Base");
  oCppFncBaseClass.SetSysNam( 0, sFncSysNam);
  oCppFncBaseClass.SetGrpNam( 0, this->getGrpNam());

  sstStr01VarDefCls oVarUserDef;
  oVarUserDef.Set_EleNam("sstStr01Cls oCsvRow");
  oVarUserDef.Set_EleInfo("oCsvCnvt Info");
  oVarUserDef.Set_Type(sstStr01Custom);

  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPublic;

  iStat = oCppFncBaseClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &SatzNr);

  // Write base class data to class and header file
  iStat = this->sst_WrtBaseClsData( 0, &sHedFil, &oCppFncBaseClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppFncBaseClass);
  //===========================================================================

  // Return number of TypDef records from file
  eTypeNum = poTypDefTab->count();

  // Datensatz-Verwaltung anlegen / \D6ffnen.
  // Open Dss Set 1 for Class Group 2
  // Open Dss Set 2 for Class Group 2
  iStat = sstCpp01_ClassTab_Open ( 0, &oCppTypClass);

  // write all cpp header files
  for (dREC04RECNUMTYP ii = 1; ii <= eTypeNum; ii++)
  {

    // Datensatz an absoluter Position lesen.
    iStat = poTypDefTab->Read( 0, ii, &oStrType);

    // if object name is different to actual object name, open new object
    size_t dStrPos = oStrTypeAct.Get_ObjNam().compare(oStrType.Get_ObjNam());

    dREC04RECNUMTYP dNumTypRecsAct = oCppTypClass.ClsTypDsVerw->count();

    // if (dStrPos == oStrType.Get_ObjNam().npos)
    if (dStrPos != 0 && dNumTypRecsAct > 1)
    {

       // Class name in table changed: new Class !
       // store class in pipe and start new one, if not empty

      iStat = oCppTypClass.GetDate( 0, &sDateStr);
      // save class name for member class
      strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
      strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

      // Write last type class data to class and header file
      iStat = this->sst_WrtClsData_inPipe_toFilesF2 ( 1, &sHedFil, sFncSysNam, &oCppTypClass);

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

  iStat = oCppTypClass.GetDate( 0, &sDateStr);
  // save class name for member class
  strncpy(oCppTypClass.cClsNam,oStrTypeAct.Get_ObjNam().c_str(),dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppTypClass.cSysNam,oStrTypeAct.Get_SysNam().c_str(),dSST_STR01_VAR_NAM_LEN);

  // Write last class data to files
  iStat = this->sst_WrtClsData_inPipe_toFilesF2 ( 1, &sHedFil, sFncSysNam, &oCppTypClass);

  // Datensatz-Verwaltung beenden.
  iStat = sstCpp01_ClassTab_Close ( 0, &oCppTypClass);

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
int sstCppGenQtTabLibCls::sst_WrtClsData_inPipe_toFilesF2 (int               iKey,
                                     sstMisc01AscFilCls   *sHedFil,
                                     std::string      sFncSysNam,
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
  if ( iKey < 0 || iKey > 1) return -1;

  iStat = strlen(oCppTypClass->cClsNam);
  if(iStat <= 0) return -2;

  //===========================================================================
  std::string sCppFilNam;  // Nam of cpp file
  sstMisc01AscFilCls oCppFil;
  std::string sDateStr;

  strncpy(oCppFncClass.cSysNam, sFncSysNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cGrpNam,this->getGrpNam().c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppFncClass.cClsNam,oCppTypClass->cClsNam, dSST_STR01_VAR_NAM_LEN);
  oCppFncClass.setExtBaseCls("sstQt01TabMdlCls");
  oCppFncClass.setQtMocMacroStr("Q_OBJECT");

  //===========================================================================
  sCppFilNam = oCppFncClass.GetSysNam();
  sCppFilNam += oCppFncClass.GetGrpNam();
  sCppFilNam += oCppFncClass.GetClsNam();
  sCppFilNam = sCppFilNam + ".cpp";

  iStat = oCppFil.fopenWr( 0, sCppFilNam.c_str());

  //===========================================================================
  iStat = oCppTypClass->GetDate( 0, &sDateStr);

  // write headrows in cpp header file
  iStat = sstCpp01_Fil_wrt_head ( 0, &oCppFil, &sDateStr);

  iStat = sstCpp01_Cls_WrtInc( 1, &oCppFil, &oCppFncClass, this->oAddCsvIncStr);

  //===========================================================================

  oLocTypClsNam = oCppTypClass->GetLibClsNam();
  oLocFncClsNam = oCppFncClass.GetLibClsNam();

  //===========================================================================

  iStat = sstCpp01_ClassTab_Open ( 0, &oCppFncClass);
  sstCpp01_ClsTyp_Cls oCppVarUserDef;  // for type class, extended var type

  // Define Database Class Element
  sstStr01VarDefCls oVarUserDef;
  std::string oClsNam = "sstDxf03DbCls";
  oVarUserDef.Set_EleNam(oClsNam + " *poDatabase");
  oVarUserDef.Set_EleInfo("Database with all tables");
  oVarUserDef.Set_Type(sstStr01Custom);

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);

  // Define Protocol object
  oVarUserDef.Set_EleNam("sstMisc01PrtFilCls *poPrt");
  oVarUserDef.Set_EleInfo("Protocol object");
  oVarUserDef.Set_Type(sstStr01Custom);

  oCppVarUserDef.sClsMem = oVarUserDef;
  oCppVarUserDef.eClsVisiTyp = myClsPrivate;

  iStat = oCppFncClass.ClsTypDsVerw->WritNew( 0, &oCppVarUserDef, &lSatzNr);
//-----------------------------------------------------------------------------
  // define new FUNCTION class set and write: constructor

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function
  oCppClsFnc.lBlcStart = 1;
  // Fill Function Block Read
  iStat = FillBlc_constructor( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);
  oCppClsFnc.lBlcRows = lSatzNrBlc;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy(oCppClsFnc.cFncPar,"QObject *parent, sstMisc01PrtFilCls *poTmpPrt, sstDxf03DbCls *poTmpDatabase", dCPPFILROWLENGTH);  // Function Parameter without parenthis

  strncpy(oCppClsFnc.cFncCom,"// Constructor", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // define new class set and write: destructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;
  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"~", dSST_STR01_VAR_NAM_LEN);  // function name
  strncat( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);  // Function Parameter empty
  strncpy(oCppClsFnc.cFncCom,"// Constructor", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------

  // rowCount
  oCppClsFnc.eCppType = sstStr01Int;  // Return type
  // oCppClsFnc.eCppType = sstStr01ULong;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function
  oCppClsFnc.setIsConstFunc(true);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_rowCount ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;
  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"rowCount", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy(oCppClsFnc.cFncPar,"const QModelIndex &", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"Count actual number of records", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------
  // columnCount

  oCppClsFnc.eCppType = sstStr01Int;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;  // private or public function
  oCppClsFnc.setIsConstFunc(true);       // const function

    oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_columnCount ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(true);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_data ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(true);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_HeaderData ( 0, &oFmtInfoObj, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(false);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_setData ( 0,&oFmtInfoObj,  oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(true);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_flags ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(false);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_removeRows ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

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
  oCppClsFnc.setIsConstFunc(false);       // const function

  oCppClsFnc.lBlcStart = lSatzNrBlc+1;

  // Fill Function Block Read
  iStat = FillBlc_insertRows ( 0, oCppTypClass, &oCppFncClass, &lSatzNrBlc);

  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, (char*)"insertRows", dSST_STR01_VAR_NAM_LEN);  // function name
  strncpy( oCppClsFnc.cRetNam, (char*)"bool", dSST_STR01_VAR_NAM_LEN);  // Name of return var
  strncpy(oCppClsFnc.cFncPar,"int position, int rows, const QModelIndex &index", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  strncpy(oCppClsFnc.cFncCom,"return number of table columns", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass.ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  //-----------------------------------------------------------------------------

  // write doxy/class information to cpp header file of function class
  iStat = sstCpp01_wrt2CppHedFil2 ( iKey, sHedFil, &oCppFncClass);

  // write information to cpp class file of function class
  iStat = sstCpp01_wrt2CppClsFil2 ( iKey, &oCppFil, &oCppFncClass);

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
int sstCppGenQtTabLibCls::sst_WrtBaseClsData (int               iKey,
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
