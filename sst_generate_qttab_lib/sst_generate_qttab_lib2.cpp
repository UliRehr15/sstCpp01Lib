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

#include "sst_generate_qttab_lib.h"

//=============================================================================
sstCppGenQtTabLibCls::sstCppGenQtTabLibCls()
{

}
//=============================================================================
void sstCppGenQtTabLibCls::setGrpNam(const std::string &sTmpGrpNam)
{
  this->sGrpNam = sTmpGrpNam;
}
//=============================================================================
std::string sstCppGenQtTabLibCls::getGrpNam() const
{
  return this->sGrpNam;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_constructor(int                 iKey,
                                              sstCpp01_Class_Cls *oCppTypClass,
                                              sstCpp01_Class_Cls *oCppFncClass,
                                              dREC04RECNUMTYP    *lSatzNr)
{
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  this->poPrt = poTmpPrt;");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  this->poDatabase = poTmpDatabase;");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  ");

  // Build EntityCount Call
  std::string oEntityCountStr;
//  oEntityCountStr = "  dREC04RECNUMTYP dRecNum = this->poDatabase->EntityCount(RS2::Entity";
//  oEntityCountStr += oCppTypClass->cClsNam;
//  oEntityCountStr += ");";
  oEntityCountStr = "  dREC04RECNUMTYP dRecNum = this->poDatabase->CountDb";
  oEntityCountStr += oCppTypClass->cClsNam;
  oEntityCountStr += "();";
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,oEntityCountStr);
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  ");

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  for (dREC04RECNUMTYP ll=1; ll<=dRecNum; ++ll)");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    this->sstTabVector.push_back(ll);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  }");

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_rowCount (int                 iKey,
                                            sstCpp01_Class_Cls *oCppTypClass,
                                            sstCpp01_Class_Cls *oCppFncClass,
                                            dREC04RECNUMTYP    *lSatzNr)

//-----------------------------------------------------------------------------
{
  std::string sBlcTxt;  // one row inside function block
  sstCpp01_FilRowCls sBlcRow;
  dREC04RECNUMTYP lClsTypNum = 0;
  std::string oEntityCountStr;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

  // Fill Function Block

  sBlcRow.setRow("//  Bloc Code Generation Start");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  // Build EntityCount Call
//  oEntityCountStr = "  iStat = this->poDatabase->EntityCount(RS2::Entity";
//  oEntityCountStr += oCppTypClass->cClsNam;
//  oEntityCountStr += ");";
  oEntityCountStr = "  iStat = this->poDatabase->CountDb";
  oEntityCountStr += oCppTypClass->cClsNam;
  oEntityCountStr += "();";
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,oEntityCountStr);

  sBlcRow.setRow("//  Bloc Code Generation End");
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
int sstCppGenQtTabLibCls::FillBlc_columnCount (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  if (oCppTypClass->ClsTypDsVerw->count() <= 0) return -2;
  std::string oTmpStr;
  sstStr01Cls oStrCnvt;
  iStat = oStrCnvt.Csv_UInt4_2String( 0, oCppTypClass->ClsTypDsVerw->count(), &oTmpStr);

  // Fill Function Block
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");
  // iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = oTypeRec.getMemberNumber();");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = " + oTmpStr +";");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

  // Expression (iRet >= 0) has to be fullfilled
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_data (int               iKey,
                             sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  sstCpp01_FilRowCls sBlcRow;
  dREC04RECNUMTYP lClsTypNum = 0;
  std::string oCallStr;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

//  int col = index.column();

//  switch(role){
//  case Qt::DisplayRole:
//    {
//      sstRec04TestRec1Cls oTestRec1;
//
//      int iStat = this->oDataTable.Read( 0, this->sstTabVector[index.row()], &this->oTypeRec);
//      assert (iStat == 0);
//
//      switch (index.column())
//      {
//      // case 0:  return QString::number(oTestRec1.dVal, 'f', 4); break;
//      case 0:  return oTestRec1.iVal;
//      case 1:  return QString::fromUtf8( oTestRec1.cVal); break;
//      default: return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() +1); break;
//      }
//    }
//  case Qt::FontRole:
//      if (col == 5) //change font only for cell(0,0)
//      {
//          QFont boldFont;
//          boldFont.setBold(true);
//          return boldFont;
//      }
//      break;
//    }
//    return QVariant();

  // Fill Function Block

  oCppFncClass->writeBlcRow( 0, lSatzNr, "//  Bloc Code Generation Start");
  // sBlcRow.setRow("//  Bloc Code Generation Start");
  // iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  oCallStr  = "  ";
  oCallStr += oCppTypClass->GetSysNam();
  oCallStr += oCppTypClass->GetGrpNam();
  oCallStr += oCppTypClass->GetClsNam();
  oCallStr += "Cls oTypRec;";

  // oCppFncClass->writeBlcRow( 0, lSatzNr, "  " + this->GetDxfConstructStr(oCppFncClass->GetClsNam()));  // DXF
  oCppFncClass->writeBlcRow( 0, lSatzNr, oCallStr);  // OTHER

  // oCppFncClass->writeBlcRow( 0, lSatzNr, oCallStr);
  // oCppFncClass->writeBlcRow( 0, lSatzNr, "  DL_Attributes oDLAttributes;");

  // oCallStr = "  int iStat = this->poDatabase->Read";  // DXF
  oCallStr = "  int iStat = this->poDatabase->ReadDb";
  oCallStr += oCppTypClass->GetClsNam();
  // oCallStr += "( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);";  // DXF
  oCallStr += "( 0, this->sstTabVector[index.row()], &oTypRec);";

  oCppFncClass->writeBlcRow( 0, lSatzNr, " ");
  oCppFncClass->writeBlcRow( 0, lSatzNr, oCallStr);
  oCppFncClass->writeBlcRow( 0, lSatzNr, "  assert (iStat == 0);");
  oCppFncClass->writeBlcRow( 0, lSatzNr, " ");

  sBlcRow.setRow("  switch(role){");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("  case Qt::DisplayRole:");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("    {");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("      switch (index.column())");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("      {");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  // Loop all member of class
  sstCpp01_ClsTyp_Cls oCppClsTypRec;  // class type/member record
  std::string sBlcRowStr;

  for (unsigned int ii=0;ii < lClsTypNum; ii++)
  {
    iStat = oCppTypClass->ClsTypDsVerw->Read(0,ii+1,&oCppClsTypRec);
    assert(iStat >= 0);

    std::string sValue;
    poFormatInfo->Csv_UInt2_2String(0,ii,&sValue);
    sBlcRowStr.clear();
    sBlcRowStr = "        case " + sValue + ": return ";

    // First Letter of Member should be upper
    std::string sEleFncNam;
    sEleFncNam = oCppClsTypRec.sClsMem.Get_EleNam();
    // char& c = sEleFncNam[0];  // reference to character inside string
    // c = std::toupper(c);
    // sEleFncNam = "oTypeRec.get" + sEleFncNam + "()";   // all
    sEleFncNam = "oTypRec." + sEleFncNam;                // dxf

    switch (oCppClsTypRec.sClsMem.Get_Type())
    {
    case (sstStr01Char):
    {
      // sBlcRowStr += "QString::fromUtf8(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +");";
      // sBlcRowStr += "QString::fromUtf8(" + sEleFncNam +".c_str());";
      sBlcRowStr += "QString::fromUtf8(" + sEleFncNam + ");";
      break;
    }
    case (sstStr01Date):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam +";";
      break;
    }
    case (sstStr01Bool):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam +";";
      break;
    }
    case (sstStr01Int):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam +";";
      break;
    }
    case (sstStr01UInt):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam +";";
      break;
    }
    case (sstStr01Long):
    {
      // sBlcRowStr += "(qlonglong) oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += "(qlonglong) " + sEleFncNam + ";";
      break;
    }
    case (sstStr01ULong):
    {
      // sBlcRowStr += "(qulonglong) oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += "(qulonglong) " + sEleFncNam +";";
      break;
    }
    case (sstStr01Float):
    {
      // sBlcRowStr += "QString::number(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +", 'f', 2);";
      sBlcRowStr += "QString::number(" + sEleFncNam +", 'f', 2);";
      break;
    }
    case (sstStr01Double):
    {
      // sBlcRowStr += "QString::number(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +", 'f', 4);";
      sBlcRowStr += "QString::number(" + sEleFncNam +", 'f', 4);";
      break;
    }
    case (sstStr01String):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam +";";
      break;
    }
    default: break;
    }
    sBlcRowStr += " break;";
    sBlcRow.setRow(sBlcRowStr.c_str());
    iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  }

  sBlcRow.setRow("      }");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("    }");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("  }");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("  return QVariant();");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcRow.setRow("//  Bloc Code Generation End");
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
int sstCppGenQtTabLibCls::FillBlc_HeaderData (int               iKey,
                                        sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  // std::string sBlcTxt;  // one row inside function block
  sstCpp01_FilRowCls sBlcRow;
  // std::string sLocStr;  // one row inside function block
  dREC04RECNUMTYP lClsTypNum = 0;
  // sstCpp01_ClsTyp_Cls oClsTyp;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;


//  if (role == Qt::DisplayRole)
//  {
//      if (orientation == Qt::Horizontal) {
//          switch (section)
//          {
//          case 0:
//              return QString("Integer");
//          case 1:
//              return QString("Unsigned Int");
//          case 2:
//              return QString("Long");
//          case 3:
//              return QString("Unsigned Long");
//          case 4:
//              return QString("Real/Float");
//          case 5:
//              return QString("Double");
//          case 6:
//              return QString("Bool");
//          case 7:
//              return QString("Character");
//          }
//      }
//  }
//  return QVariant();



  // Fill Function Block

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  if (role == Qt::DisplayRole)");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  {");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"      if (orientation == Qt::Horizontal) {");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"          switch (section)");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"          {");


  // Loop all member of class
  sstCpp01_ClsTyp_Cls oCppClsTypRec;  // class type/member record
  std::string sBlcRowStr;

  for (unsigned int ii=0;ii < lClsTypNum; ii++)
  {
    iStat = oCppTypClass->ClsTypDsVerw->Read(0,ii+1,&oCppClsTypRec);
    assert(iStat >= 0);

    // sstStr01Cls oCnvt;
    std::string sValue;
    poFormatInfo->Csv_UInt2_2String(0,ii,&sValue);
    sBlcRowStr.clear();
    sBlcRowStr = "        case " + sValue + ": return QString(\"";

    sBlcRowStr += oCppClsTypRec.sClsMem.Get_EleNam();
    sBlcRowStr += "\");";
    iStat = oCppFncClass->writeBlcRow(0,lSatzNr,sBlcRowStr);
    // iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  }

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"      }");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    }");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  return QVariant();");

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

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
int sstCppGenQtTabLibCls::FillBlc_setData (int               iKey,
                                     sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  // std::string sBlcTxt;  // one row inside function block
  // sstCpp01_FilRowCls sBlcRow;
  std::string sLocRowStr;  // one row inside function block
  dREC04RECNUMTYP lClsTypNum = 0;
  std::string oCallStr;
  // sstCpp01_ClsTyp_Cls oClsTyp;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

//  if (role == Qt::EditRole)
//  {
//    //save value from editor to oTestRecDss
//    sstRec04TestRec2Cls oTestRec2;

//    dREC04RECNUMTYP dRecNo = index.row() +1;
//    oTestRec2Table.ReadRecPos ( 0, this->sstTabVector[index.row()], &oTestRec2);

//    bool bOK = 1;

//  switch (index.column())
//  {
//  case 0: oTestRec2.iVal = value.toInt(&bOK);  break;
  //  case 1: oTestRec2.uiVal = value.toUInt(&bOK) ; break;
  //  case 2: oTestRec2.lVal = value.toLongLong(&bOK) ; break;
  //  case 3: oTestRec2.ulVal = value.toULongLong(&bOK) ; break;
//  case 4: oTestRec2.fVal = value.toFloat(&bOK) ; break;
  //  case 5: oTestRec2.dVal = value.toDouble(&bOK); break;
//  case 6: oTestRec2.bVal = value.toBool(); break;
//  case 7:
//  {
//    QString locStr = value.toString();
//    strncpy(oTestRec2.cVal, locStr.toUtf8(),10);
//    break;
//  }
//  }

//  if (bOK) oTestRec2Table.WriteRecPos( 0, dRecNo, &oTestRec2);

//}
//return true;


  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"//  Bloc Code Generation Start");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");

  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"if (role == Qt::EditRole)");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"{");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  //save value from editor to oTestRecDss");

  oCallStr  = "  ";
  oCallStr += oCppTypClass->GetSysNam();
  oCallStr += oCppTypClass->GetGrpNam();
  oCallStr += oCppTypClass->GetClsNam();
  oCallStr += "Cls oTypRec;";

  // oCppFncClass->writeBlcRow( 0, lSatzNr, "  " + this->GetDxfConstructStr(oCppFncClass->GetClsNam()));  // DXF
  oCppFncClass->writeBlcRow( 0, lSatzNr, oCallStr);  // OTHER

  // oCppFncClass->writeBlcRow( 0, lSatzNr, "  DL_Attributes oDLAttributes;");
  oCppFncClass->writeBlcRow( 0, lSatzNr, "  dREC04RECNUMTYP dMainRecNo = 0;");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  dREC04RECNUMTYP dRecNo = index.row() +1;");
  // iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  this->poDatabase.Read ( 0, this->sstTabVector[index.row()], &oTypRec);");
  // oCallStr = "  this->poDatabase->Read";  // DXF
  oCallStr = "  this->poDatabase->ReadDb";
  oCallStr += oCppTypClass->GetClsNam();
  // oCallStr += "( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);";  // DXF
  oCallStr += "( 0, this->sstTabVector[index.row()], &oTypRec);";
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr, oCallStr);
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  bool bOK = 1;");

  // iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"//  Bloc Code Generation Start");
  // iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"      switch (index.column())");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"      {");

  // Loop all member of class
  sstCpp01_ClsTyp_Cls oCppClsTypRec;  // class type/member record
  std::string sBlcRowStr;

  for (unsigned int ii=0;ii < lClsTypNum; ii++)
  {
    iStat = oCppTypClass->ClsTypDsVerw->Read(0,ii+1,&oCppClsTypRec);
    assert(iStat >= 0);


    // sstStr01Cls oCnvt;
    std::string sValue;
    poFormatInfo->Csv_UInt2_2String(0,ii,&sValue);
    sBlcRowStr.clear();
    sBlcRowStr = "        case " + sValue + ": ";
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,sBlcRowStr);
    sBlcRowStr.clear();
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"      {");

    // First Letter of Member should be upper
    std::string sEleFncNam;
    sEleFncNam = oCppClsTypRec.sClsMem.Get_EleNam();
    // char& c = sEleFncNam[0];  // reference to character inside string
    // c = std::toupper(c);
    // sEleFncNam = "        oTypRec.set" + sEleFncNam + "(";  // general
    sEleFncNam = "        oTypRec." + sEleFncNam + " = ";        // dxf

    switch (oCppClsTypRec.sClsMem.Get_Type())
    {
    case (sstStr01Char):
    {
      //    QString locStr = value.toString();
      // oTypeRec.setText( locStr.toStdString()); break;
      sLocRowStr.clear();
      sLocRowStr += "        QString locStr = value.toString();";
      iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,sLocRowStr);
      // strncpy(oTestRec2.cVal, locStr.toUtf8(),10);
      // sBlcRowStr += sEleFncNam + "locStr.toStdString()";
      sBlcRowStr += "        strncpy(oTypRec." + oCppClsTypRec.sClsMem.Get_EleNam() + ", locStr.toUtf8(),10)";
      break;
    }
    case (sstStr01Date):
    {
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +";";
      sBlcRowStr += sEleFncNam + "locStr.toStdString()";
      // sBlcRowStr += sEleFncNam +";";
      break;
    }
    case (sstStr01Bool):
    {
      //  case 6: oTestRec2.bVal = value.toBool(); break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toBool();";
      sBlcRowStr += sEleFncNam + "value.toBool()";
      break;
    }
    case (sstStr01Int):
    {
      //  case 0: oTestRec2.iVal = value.toInt(&bOK);  break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toInt(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toInt(&bOK)";
      break;
    }
    case (sstStr01UInt):
    {
      //  case 1: oTestRec2.uiVal = value.toUInt(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toUInt(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toUInt(&bOK)";
      break;
    }
    case (sstStr01Long):
    {
      //  case 2: oTestRec2.lVal = value.toLongLong(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toLongLong(&bOK);";
      sBlcRowStr += sEleFncNam  + "value.toLongLong(&bOK)";
      break;
    }
    case (sstStr01ULong):
    {
      //  case 3: oTestRec2.ulVal = value.toULongLong(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toULongLong(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toULongLong(&bOK)";
      break;
    }
    case (sstStr01Float):
    {
      //  case 4: oTestRec2.fVal = value.toFloat(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toFloat(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toFloat(&bOK)";
      break;
    }
    case (sstStr01Double):
    {
      //  case 5: oTestRec2.dVal = value.toDouble(&bOK); break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toDouble(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toDouble(&bOK)";
      break;
    }
    case (sstStr01String):
    {
      //    QString locStr = value.toString();
      // oTypeRec.setText( locStr.toStdString()); break;
      iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"    QString locStr = value.toString();");
      // sBlcRowStr += "strncpy(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +", locStr.toUtf8(),10);";
      sBlcRowStr += "strncpy(" + sEleFncNam +", locStr.toUtf8()),10";
      break;
    }
    default: break;
    }
    // sBlcRowStr += ");";  // General
    sBlcRowStr += ";";      // dxf
    sBlcRowStr += " break;";
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,sBlcRowStr);
    // iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"      }");
  }

  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  }");
  // iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  if (bOK) this->oDataTable.Writ( 0, &oTypeRec, dRecNo);");
  // iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  if (bOK) this->poDatabase->Writ( 0, &oTypeRec, dRecNo);");
  // oCallStr ="  if (bOK) this->poDatabase->Write";  // DXF
  oCallStr ="  if (bOK) this->poDatabase->WriteDb";
  oCallStr += oCppTypClass->GetClsNam();
  // oCallStr += "( 0, oTypRec, oDLAttributes, &dRecNo, &dMainRecNo);";  // DXF
  oCallStr += "( 0, &oTypRec, &dRecNo);";
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,oCallStr);
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  }");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  return true;");

  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"//  Bloc Code Generation End");

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
int sstCppGenQtTabLibCls::FillBlc_flags (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  if (oCppTypClass->ClsTypDsVerw->count() <= 0) return -2;

  //    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);

  // Fill Function Block
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);");

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

  // Expression (iRet >= 0) has to be fullfilled
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_removeRows (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  if (oCppTypClass->ClsTypDsVerw->count() <= 0) return -2;

  //  Q_UNUSED(index);
  //  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  //  // rows is always = 1 at the moment
  //  // Position is 0 > n-1

  //  for (int row = 0; row < rows; ++row) {
  //    oTestRec2Table.DeleteRecPos(0,position+1);
  //  }
  //  endRemoveRows();

  //  this->sstTabVector.erase (this->sstTabVector.begin()+position);

  //  return true;

  // Fill Function Block
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");

  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  Q_UNUSED(index);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  beginRemoveRows(QModelIndex(), position, position + rows - 1);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  // rows is always = 1 at the moment");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  // Position is 0 > n-1");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  for (int row = 0; row < rows; ++row) {");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    // this->poDatabase->RecSetDeleted(0,position+1);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  endRemoveRows();");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  this->sstTabVector.erase (this->sstTabVector.begin()+position);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  return true;");




  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

  // Expression (iRet >= 0) has to be fullfilled
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_insertRows (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr)

//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Die Anzahl der aktuell gespeicherten Datensätze zurückgeben.
  if (oCppTypClass->ClsTypDsVerw->count() <= 0) return -2;

//  Q_UNUSED(index);
//  beginInsertRows(QModelIndex(), position, position + rows - 1);

//  // rows is always = 1 at the moment
//  // Position is 0 > n-1
//  dREC04RECNUMTYP dRecNo = 0;

//  for (int row = 0; row < rows; ++row) {
//    sstRec04TestRec2Cls oTestRec;
//    oTestRec2Table.ReadRecPos(0,oTestRec2Table.RecordCount(),&oTestRec);
//    oTestRec2Table.WriteNew(0,&dRecNo,&oTestRec);
//  }

//  endInsertRows();

//  this->sstTabVector.push_back(dRecNo);

//  return true;

  // Fill Function Block
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");


  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  Q_UNUSED(index);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  beginInsertRows(QModelIndex(), position, position + rows - 1);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  // rows is always = 1 at the moment");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  // Position is 0 > n-1");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  dREC04RECNUMTYP dRecNo = 0;");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  for (int row = 0; row < rows; ++row) {");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    // this->poDatabase->Read(0,this->poDatabase->count(),&this->oTypeRec);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    // this->poDatabase->WritNew( 0, &this->oTypeRec, &dRecNo);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  }");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  endInsertRows();");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  this->sstTabVector.push_back(dRecNo);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  ");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  return true;");





  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

  // Expression (iRet >= 0) has to be fullfilled
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_SlotChangeTab( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;

//  emit this->sstSgnlTabMLChanged(oMapSignal);

  oBlcRow = "  emit this->SgnlTabChanged" + oCppFncClass->GetClsNam() + "(oMapSignal);";
  int iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_SlotUpdateTab( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;
  int iStat = 0;

//  emit this->poTabMdl->sstSgnlTabMLUpdated(oShapeItem);
//  this->resizeRowsToContents();

  oBlcRow = "  emit this->poTabMdl->SgnlTabUpdated" + oCppFncClass->GetClsNam() + "(oShapeItem);";
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo,"  this->resizeRowsToContents();");

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_SlotChangeTab(sstCpp01_Class_Cls *oCppTypClass,
                                                    sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SlotChangeTab" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSlot;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_SlotChangeTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  // strncpy( oCppClsFnc.cFncPar,"QObject *parent, sstMisc01PrtFilCls *poTmpPrt, sstDxf03DbCls *poTmpDatabase", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  std::string oLocStr = "sstQt01MapSignalCls oMapSignal";
  // oLocStr += oCppTypClass->GetSysNam();
  // oLocStr += "FncDatabaseCls *poTmpDatabase";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_SlotUpdateTab(sstCpp01_Class_Cls *oCppTypClass,
                                                    sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SlotUpdateTab" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSlot;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_SlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01ShapeItem oShapeItem";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_SgnlTabChanged(sstCpp01_Class_Cls *oCppTypClass,
                                                     sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SgnlTabChanged" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSignal;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // iStat = this->FillBlc_ViewSlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01MapSignalCls oMapSignal";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_SgnlTabUpdated(sstCpp01_Class_Cls *oCppTypClass,
                                                     sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SgnlTabUpdated" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSignal;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // iStat = this->FillBlc_ViewSlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01ShapeItem oShapeItem";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_ViewConstructor( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;
  int iStat = 0;
  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam() + oCppFncClass->GetGrpNam() + oCppFncClass->GetClsNam();

//  tonQtPtss01TabViewMLCls::tonQtPtss01TabViewMLCls(sstMisc01PrtFilCls *poTmpPrt,
//                                                   PtssFncDatabaseCls *poPtssDb)
//    : sstQt01TabViewCls(poTmpPrt)
//  {
//    poTabMdl = new [SYS]QtTabMdl[CLS]Cls( 0, poTmpPrt, po[SYS]Db);
//    this->setModel( poTabMdl );

//    connect(this,SIGNAL(sstSgnlTab[CLS]Updated(sstQt01ShapeItem)),this,SLOT(sstSlotUpdateTab[CLS](sstQt01ShapeItem)));
//    connect(this->poTabMdl,SIGNAL(sstSgnlTab[CLS]Changed(sstQt01MapSignalCls)),this,SLOT(sstSlotChangeTab[CLS](sstQt01MapSignalCls)));

  oBlcRow = "  poTabMdl = new " + oCppFncClass->GetSysNam() + "QtTabMdl" + oCppFncClass->GetClsNam() + "Cls( 0, poTmpPrt, poTmpDatabase);";
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo,"  this->setModel( poTabMdl );");
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo,"  ");
  oBlcRow = "  connect(this,SIGNAL(sstSgnlTab" + oCppFncClass->GetClsNam() + "Updated(sstQt01ShapeItem)),this,SLOT(sstSlotUpdateTab" + oCppFncClass->GetClsNam() + "(sstQt01ShapeItem)));";
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  oBlcRow = "  connect(this->poTabMdl,SIGNAL(sstSgnlTab" + oCppFncClass->GetClsNam() + "Changed(sstQt01MapSignalCls)),this,SLOT(sstSlotChangeTab" + oCppFncClass->GetClsNam() + "(sstQt01MapSignalCls)));";
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_ViewDestructor( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;

  //  delete poTabMdl;

  int iStat = oCppFncClass->writeBlcRow( 0, &dRecNo,"  delete poTabMdl;");

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_ViewSlotChangeTab( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;

//  emit this->sstSgnlTabMLChanged(oMapSignal);

  oBlcRow = "  emit this->SgnlTabChanged" + oCppFncClass->GetClsNam() + "(oMapSignal);";
  int iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillBlc_ViewSlotUpdateTab( sstCpp01_Class_Cls  *oCppFncClass)
{
  dREC04RECNUMTYP dRecNo = 0;
  std::string oBlcRow;
  int iStat = 0;

//  emit this->poTabMdl->sstSgnlTabMLUpdated(oShapeItem);
//  this->resizeRowsToContents();

  oBlcRow = "  emit this->poTabMdl->SgnlTabUpdated" + oCppFncClass->GetClsNam() + "(oShapeItem);";
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo, oBlcRow);
  iStat = oCppFncClass->writeBlcRow( 0, &dRecNo,"  this->resizeRowsToContents();");

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewConstructor( sstCpp01_Class_Cls *oCppTypClass,
                                                   sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = oCppFncClass->GetLibClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // Fill Function Block Read
  iStat = this->FillBlc_ViewConstructor( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name

  // Create parameter string
  std::string oLocStr = "sstMisc01PrtFilCls *poTmpPrt, ";
  oLocStr += oCppTypClass->GetSysNam();
  oLocStr += "FncDatabaseCls *poTmpDatabase";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  strncpy(oCppClsFnc.cFncCom,"Constructor", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewDestructor(sstCpp01_Class_Cls *oCppTypClass,
                                                 sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "~" + oCppFncClass->GetLibClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsPublic;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_ViewDestructor( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oCppFncClass->GetLibClsNam().c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
//  std::string oLocStr = "QObject *parent, sstMisc01PrtFilCls *poTmpPrt, ";
//  oLocStr += oCppTypClass->GetSysNam();
//  oLocStr += "FncDatabaseCls *poTmpDatabase";
//  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  strncpy(oCppClsFnc.cFncCom,"Destructor", dCPPFILROWLENGTH);  // Comment
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewSlotChangeTab(sstCpp01_Class_Cls *oCppTypClass,
                                                    sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SlotChangeTab" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSlot;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_ViewSlotChangeTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  // strncpy( oCppClsFnc.cFncPar,"QObject *parent, sstMisc01PrtFilCls *poTmpPrt, sstDxf03DbCls *poTmpDatabase", dCPPFILROWLENGTH);  // Function Parameter without parenthis
  std::string oLocStr = "sstQt01MapSignalCls oMapSignal";
  // oLocStr += oCppTypClass->GetSysNam();
  // oLocStr += "FncDatabaseCls *poTmpDatabase";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewSlotUpdateTab(sstCpp01_Class_Cls *oCppTypClass,
                                                    sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SlotUpdateTab" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSlot;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  iStat = this->FillBlc_ViewSlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01ShapeItem oShapeItem";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewSgnlTabChanged(sstCpp01_Class_Cls *oCppTypClass,
                                                     sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SgnlTabChanged" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSignal;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // iStat = this->FillBlc_ViewSlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01MapSignalCls oMapSignal";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
int sstCppGenQtTabLibCls::FillCls_ViewSgnlTabUpdated(sstCpp01_Class_Cls *oCppTypClass,
                                                     sstCpp01_Class_Cls *oCppFncClass)
{
  int iStat = 0;
  sstCpp01_ClsFnc_Cls oCppClsFnc;    // Next Function record for actual class
  std::string oLocFncClsNam = "SgnlTabUpdated" + oCppFncClass->GetClsNam();
  dREC04RECNUMTYP lSatzNr = 0;
  dREC04RECNUMTYP lSatzNrBlc = 0;
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count(); // Get end of code block

  std::string oFullClsNam;
  oFullClsNam = oCppFncClass->GetSysNam()+oCppFncClass->GetGrpNam()+oCppFncClass->GetClsNam()+"Cls";

  // define new class set and write: constructor
  oCppClsFnc.eCppType = sstStr01Unknown;  // Return type
  oCppClsFnc.eClsVisiTyp = myClsSignal;   // private or public function
  // oCppClsFnc.lBlcStart = 1;
  oCppClsFnc.lBlcStart = lSatzNrBlc+1;
  oCppClsFnc.lBlcRows = 0;

  // iStat = this->FillBlc_ViewSlotUpdateTab( oCppFncClass);
  lSatzNrBlc = oCppFncClass->ClsBlcDsVerw->count();  // Get end of code block
  oCppClsFnc.lBlcRows = lSatzNrBlc - oCppClsFnc.lBlcStart +1;

  strncpy( oCppClsFnc.cClsNam, oFullClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // class name
  strncpy( oCppClsFnc.cFncNam, oLocFncClsNam.c_str(), dSST_STR01_VAR_NAM_LEN);  // function name
  std::string oLocStr = "sstQt01ShapeItem oShapeItem";
  strncpy( oCppClsFnc.cFncPar, oLocStr.c_str(), dCPPFILROWLENGTH);  // Function Parameter without parenthis

  oCppClsFnc.setFncCom("Comment " + oLocFncClsNam);  // Comment
  oCppClsFnc.eCppType = sstStr01Custom;
  oCppClsFnc.setRetNam("void");
  iStat = oCppFncClass->ClsFncDsVerw->WritNew( 0, &oCppClsFnc, &lSatzNr);

  return iStat;
}
//=============================================================================
std::string sstCppGenQtTabLibCls::GetDxfConstructStr(const std::string oClsNam)
{
  std::string oDxfStr = "DL_LineData oTypRec(0,0,0,0,0,0);";  // DLDataLine

  if      (oClsNam.compare("Unknown")   == 0) oDxfStr = "";
  else if (oClsNam.compare("Container") == 0) oDxfStr = "";
  else if (oClsNam.compare("Block")     == 0) oDxfStr = "";
  else if (oClsNam.compare("FontChar")  == 0) oDxfStr = "";
  else if (oClsNam.compare("Insert")    == 0) oDxfStr = "";
  else if (oClsNam.compare("Line")      == 0) oDxfStr = "DL_LineData oTypRec(0,0,0,0,0,0);";
  else if (oClsNam.compare("Point")     == 0) oDxfStr = "DL_PointData oTypRec;";
  else if (oClsNam.compare("Circle")    == 0) oDxfStr = "DL_CircleData oTypRec(0,0,0,1);";
  else if (oClsNam.compare("MText")     == 0) oDxfStr = "DL_MTextData oTypRec(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,0.0,\"\",\"\",0.0);";
  else if (oClsNam.compare("Text")      == 0) oDxfStr = "DL_TextData oTypRec(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,\"\",\"\",0.0);";
  else oDxfStr = "";

  if (oDxfStr.length() == 0) assert(0);

  return oDxfStr;
}
//=============================================================================
