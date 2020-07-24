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
                                                sstCpp01_Class_Cls *oCppTypClass,
                                                sstCpp01_Class_Cls *oCppFncClass,
                                                dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;
  std::string oTypNamStr;
  oTypNamStr = oCppTypClass->GetSysNam() + oCppTypClass->GetGrpNam() + oCppTypClass->GetClsNam() + "Cls";

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
int sstCppGenFncLibCls::FillBlc_ConstructorDb (int                  iKey,
                                               sstStr01VarDefCls    oClsMemDef,
                                               sstCpp01_Class_Cls  *oCppFncClass)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;
  dREC04RECNUMTYP lSatzNr = 0;

  // for example:
  // this->poTabObj = new  SysGrpObjCls ();

  sstCpp01_ClsTyp_Cls oCppClsTyp1;        // one class member object in type class
  dREC04RECNUMTYP dMemTypeNum = oCppFncClass->ClsTypDsVerw->count();

  for (dREC04RECNUMTYP ll = 1; ll <= dMemTypeNum; ll++)
  {
    oCppFncClass->ClsTypDsVerw->Read( 0, ll, &oCppClsTyp1);
    std::string oBlcRow;
    std::string oTmpEleNam;
    std::string oDefinition;
    oTmpEleNam = oCppClsTyp1.sClsMem.Get_EleNam();  // if type is custom, in string elenam is definition and name

    std::size_t pos = oTmpEleNam.find(" ");      // find end of definition
    oDefinition = oTmpEleNam.substr ( 0, pos);   // extract definition

    oBlcRow = "  this->p" + oCppClsTyp1.sClsMem.Get_EleInfo() + " = new " + oDefinition + "();";
    oCppFncClass->writeBlcRow( 0, &lSatzNr, oBlcRow);
  }

  // oCppFncClass->writeBlcRow( 0, &lSatzNr,"  iStat = -1;");

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_DestructorDb (int                  iKey,
                                              sstStr01VarDefCls    oClsMemDef,
                                              sstCpp01_Class_Cls  *oCppFncClass)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;
  dREC04RECNUMTYP lSatzNr = 0;

//  delete this->poTabEN;
//  delete this->poTabZE;
//  delete this->poTabZN;
//  delete this->poTabFR;

  sstCpp01_ClsTyp_Cls oCppClsTyp1;        // one class member object in type class
  dREC04RECNUMTYP dMemTypeNum = oCppFncClass->ClsTypDsVerw->count();

  for (dREC04RECNUMTYP ll = dMemTypeNum; ll >= 1; ll--)
  {
    oCppFncClass->ClsTypDsVerw->Read( 0, ll, &oCppClsTyp1);
    std::string oBlcRow;
/*    std::string oTmpEleNam;
    std::string oDefinition;
    oTmpEleNam = oCppClsTyp1.sClsMem.Get_EleNam();  // if type is custom, in string elenam is definition and name

    std::size_t pos = oTmpEleNam.find(" ");      // find end of definition
    oDefinition = oTmpEleNam.substr ( 0, pos);*/   // extract definition

    oBlcRow = "  delete this->p" + oCppClsTyp1.sClsMem.Get_EleInfo() + ";";
    oCppFncClass->writeBlcRow( 0, &lSatzNr, oBlcRow);
  }

  // oCppFncClass->writeBlcRow( 0, &lSatzNr,"  iStat = -1;");

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

//  if ( iKey != 0) return -1;

//  int iStat = 0;
//  iStat = -1;
//  iStat = this->poTab[Obj]->Read( 0, dRecNo, vRecAdr);
//  return iStat;

  std::string oBlcRow;
  oBlcRow = "  iStat = this->poTab" + oClsMemDef.Get_ObjNam() + "->Read( 0, dRecNo, vRecAdr);";

  oCppFncClass->writeBlcRow(0,lSatzNr,"  if ( iKey != 0) return -1;");
  oCppFncClass->writeBlcRow( 0, lSatzNr, oBlcRow);

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

//  if ( iKey != 0) return -1;

//  int iStat = 0;

//  if(*pdRecNo == 0) {
//    // Add Record
//    iStat = this->poTabObj->Write( 0, pdRecNo ,vRecAdr);
//    dREC04RECNUMTYP RecNo = 0;
//    [Sys][Grp][Obj]Cls oMainRec;
//    oMainRec.d[Grp]TabRecNo = *pdRecNo;
//    oMainRec.eSysGrp = eSys_Obj;
//    iStat = this->WriteDbMain(0,&oMainRec, &RecNo);
//  }
//  else {
//    // Update Record
//    iStat = this->poTab[Obj]->Write( 0, pdRecNo ,vRecAdr);
//  }

  std::string oWriteStr;
  std::string oTypeStr;
  std::string oWriteNewStr;
  std::string oSysGrpStr;

  // oSysGrpStr = oCppFncClass->GetSysNam() + oCppFncClass->GetGrpNam();
  oSysGrpStr = oCppFncClass->GetSysNam() + "Typ";
  // oSysGrpStr = "RecTyp";
  oWriteStr    = "    iStat = this->poTab" + oClsMemDef.Get_ObjNam() + "->Write( 0, pdRecNo ,vRecAdr);";
//  oTypeStr     = "    oMainRec.e" + oSysGrpStr + " = e" + oCppFncClass->GetSysNam() +
//                 "_" + oClsMemDef.Get_ObjNam() +";";
  oTypeStr     = "    oMainRec.eRecTyp = e" + oCppFncClass->GetSysNam() +
                 "_" + oClsMemDef.Get_ObjNam() +";";
  oWriteNewStr = "    iStat = this->poTab" + oClsMemDef.Get_ObjNam() + "->Write( 0, pdRecNo ,vRecAdr);";


  oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  if ( iKey != 0) return -1;");
  oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  if(*pdRecNo == 0) {");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    // Add Record");
  oCppFncClass->writeBlcRow( 0, lSatzNr, oWriteStr.c_str());
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    dREC04RECNUMTYP RecNo = 0;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    " + oSysGrpStr + "MainCls oMainRec;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    oMainRec.dTypTabRecNo = *pdRecNo;");
  oCppFncClass->writeBlcRow( 0, lSatzNr, oTypeStr.c_str());
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    iStat = this->WriteDbMain(0,&oMainRec, &RecNo);");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  }");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  else {");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"    // Update Record");
  oCppFncClass->writeBlcRow( 0, lSatzNr, oWriteNewStr.c_str());
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  }  ");

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

  // return this->poTab[Obj]->Count();

  std::string oCountRow;
  oCountRow = " return this->poTab" + oClsMemDef.Get_ObjNam() + "->Count();";

  oCppFncClass->writeBlcRow( 0, lSatzNr, oCountRow.c_str());

  // oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = -1;");

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
                                                  sstCpp01_Class_Cls  *oCppTypClass,
                                                  sstCpp01_Class_Cls  *oCppFncClass,
                                                  dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

//  std::string oPtsFilNamShort;
//  std::string oPtsFilNamCsv;
//  sstMisc01FilNamCls oFilNamCnvt;
//  iStat = oFilNamCnvt.RemoveExtension( 0, ".Ptss", oPtsFilNam, &oPtsFilNamShort);
//  assert(iStat >= 0);
//  sstMisc01AscFilCls oPtsCsvFil;

//  oPtsFilNamCsv = oPtsFilNamShort + "_HA.Csv";
//  iStat = this->poTabHA->LoadTabFromCsv( 0, oPtsFilNamCsv, &oErrStr);
//  assert(iStat >= 0);  // Not found

  oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oPtsFilNamShort;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oPtsFilNamCsv;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oErrStr;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  sstMisc01FilNamCls oFilNamCnvt;");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  iStat = oFilNamCnvt.RemoveExtension( 0, \".Ptss\", oPtsFilNam, &oPtsFilNamShort);");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  assert(iStat >= 0);");
  oCppFncClass->writeBlcRow( 0, lSatzNr,"  sstMisc01AscFilCls oPtsCsvFil;");


  for ( dREC04RECNUMTYP ll = 1; ll <=  oCppTypClass->ClsTypDsVerw->count(); ll++)
  {
    sstCpp01_ClsTyp_Cls oCppClsTyp1;
    iStat = oCppTypClass->ClsTypDsVerw->Read( 0, ll, &oCppClsTyp1);
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  oPtsFilNamCsv = oPtsFilNamShort + \"_" + oCppClsTyp1.sClsMem.Get_ObjNam() + ".Csv\";");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  iStat = this->poTab" + oCppClsTyp1.sClsMem.Get_ObjNam() + "->LoadTabFromCsv( 0, oPtsFilNamCsv, &oErrStr);");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  assert(iStat >= 0);  // Error reading table");
    oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  }

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillBlc_SaveToCsvFiles (int                  iKey,
                                                sstCpp01_Class_Cls  *oCppTypClass,
                                                sstCpp01_Class_Cls  *oCppFncClass,
                                                dREC04RECNUMTYP     *lSatzNr)
//-----------------------------------------------------------------------------
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  //  std::string oPtsFilNamShort;
  //  std::string oPtsFilNamCsv;
  //  sstMisc01FilNamCls oFilNamCnvt;
  //  iStat = oFilNamCnvt.RemoveExtension( 0, ".Ptss", oPtsFilNam, &oPtsFilNamShort);
  //  assert(iStat >= 0);
  //  sstMisc01AscFilCls oPtsCsvFil;

  //  oPtsFilNamCsv = oPtsFilNamShort + "_HA.Csv";
  //  iStat = this->poTabHA->SaveTabToCsv( 0, oPtsFilNamCsv, &oErrStr);
  //  assert(iStat >= 0);  // Not found

    oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oPtsFilNamShort;");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oPtsFilNamCsv;");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  std::string oErrStr;");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  sstMisc01FilNamCls oFilNamCnvt;");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  iStat = oFilNamCnvt.RemoveExtension( 0, \".Ptss\", oPtsFilNam, &oPtsFilNamShort);");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  assert(iStat >= 0);");
    oCppFncClass->writeBlcRow( 0, lSatzNr,"  sstMisc01AscFilCls oPtsCsvFil;");


    for ( dREC04RECNUMTYP ll = 1; ll <=  oCppTypClass->ClsTypDsVerw->count(); ll++)
    {
      sstCpp01_ClsTyp_Cls oCppClsTyp1;
      iStat = oCppTypClass->ClsTypDsVerw->Read( 0, ll, &oCppClsTyp1);
      oCppFncClass->writeBlcRow( 0, lSatzNr,"  oPtsFilNamCsv = oPtsFilNamShort + \"_" + oCppClsTyp1.sClsMem.Get_ObjNam() + ".Csv\";");
      oCppFncClass->writeBlcRow( 0, lSatzNr,"  iStat = this->poTab" + oCppClsTyp1.sClsMem.Get_ObjNam() + "->SaveTabToCsv( 0, oPtsFilNamCsv, &oErrStr);");
      oCppFncClass->writeBlcRow( 0, lSatzNr,"  assert(iStat >= 0);  // Error writing table");
      oCppFncClass->writeBlcRow( 0, lSatzNr," ");
    }

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
int sstCppGenFncLibCls::FillCls_ConstructorDB( sstStr01VarDefCls    oClsMemDef,
                                               sstCpp01_Class_Cls  *oCppFncClass)
{
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // function definition for database class
  int iStat = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  dREC04RECNUMTYP lSatzNr = 0;
  std::string oLocFncClsNam;  // full class name

  oLocFncClsNam = oCppFncClass->GetSysNam() + oCppFncClass->GetGrpNam() + "DatabaseCls";
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block

  // define new function set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // Fill Codebloc for actual function
  iStat = this->FillBlc_ConstructorDb( 0, oClsMemDef, oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);              // Parameter infos
  strncpy(oCppClsFnc.cFncCom,"Constructor", dCPPFILROWLENGTH);   // function comment
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenFncLibCls::FillCls_DestructorDB( sstStr01VarDefCls    oClsMemDef,
                                              sstCpp01_Class_Cls  *oCppFncClass)
{
  sstCpp01_ClsFnc_Cls oCppClsFnc;  // for func class
  int iStat = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  dREC04RECNUMTYP lSatzNr = 0;
  std::string oLocFncClsNam;  // full class name

  oLocFncClsNam = oCppFncClass->GetSysNam() + oCppFncClass->GetGrpNam() + "DatabaseCls";
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  // define new function set and write: destructor
  oCppClsFnc.eCppType = sstStr01Unknown;
  oCppClsFnc.eClsVisiTyp = myClsPublic;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // Fill Codebloc for actual function
  iStat = this->FillBlc_DestructorDb( 0, oClsMemDef, oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1 ;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy( oCppClsFnc.cFncNam, (char*)"~", dSST_STR01_VAR_NAM_LEN);
  strncat( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);
  strncpy(oCppClsFnc.cFncPar,"", dCPPFILROWLENGTH);            // Parameter infos
  strncpy(oCppClsFnc.cFncCom,"Destructor", dCPPFILROWLENGTH);  // function comment
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

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
