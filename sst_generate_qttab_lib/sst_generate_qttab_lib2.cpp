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
int sstCpp01_CsvLib_FillBlc_rowCount (int               iKey,
                             // sstStr01Cls *oFormatInfo,
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

  sBlcRow.setRow("//  Bloc Code Generation Start");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  // return oTestRec1Table.Count();
  sBlcRow.setRow("  ulStat = oDataTable.count();");
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
int sstCpp01_CsvLib_FillBlc_columnCount (int               iKey,
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

  // Fill Function Block
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation Start");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"  iStat = oTypeRec.getMemberNumber();");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"//  Bloc Code Generation End");

  // Expression (iRet >= 0) has to be fullfilled
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstCpp01_CsvLib_FillBlc_data (int               iKey,
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

  sBlcRow.setRow("//  Bloc Code Generation Start");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  sBlcRow.setRow(" ");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("  int iStat = this->oDataTable.Read( 0, this->sstTabVector[index.row()], &this->oTypeRec);");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow("   assert (iStat == 0);");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
  sBlcRow.setRow(" ");
  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

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
    char& c = sEleFncNam[0];  // reference to character inside string
    c = std::toupper(c);
    sEleFncNam = "oTypeRec.get" + sEleFncNam + "()";

    switch (oCppClsTypRec.sClsMem.Get_Type())
    {
    case (sstStr01Char):
    {
      // sBlcRowStr += "QString::fromUtf8(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +");";
      sBlcRowStr += "QString::fromUtf8(" + sEleFncNam +".c_str());";
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
int sstCpp01_CsvLib_FillBlc_HeaderData (int               iKey,
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
int sstCpp01_CsvLib_FillBlc_setData (int               iKey,
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
  // iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  sstRec04TestRec2Cls oTabRec;");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  dREC04RECNUMTYP dRecNo = index.row() +1;");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  this->oDataTable.Read ( 0, this->sstTabVector[index.row()], &oTypeRec);");
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
    char& c = sEleFncNam[0];  // reference to character inside string
    c = std::toupper(c);
    sEleFncNam = "        oTypeRec.set" + sEleFncNam + "(";

    switch (oCppClsTypRec.sClsMem.Get_Type())
    {
    case (sstStr01Char):
    {
      //    QString locStr = value.toString();
      // oTypeRec.setText( locStr.toStdString()); break;
      sLocRowStr += "        QString locStr = value.toString();";
      iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,sLocRowStr);
      sBlcRowStr += sEleFncNam + "locStr.toStdString());";
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
      //  case 6: oTestRec2.bVal = value.toBool(); break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toBool();";
      sBlcRowStr += sEleFncNam + "value.toBool());";
      break;
    }
    case (sstStr01Int):
    {
      //  case 0: oTestRec2.iVal = value.toInt(&bOK);  break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toInt(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toInt(&bOK));";
      break;
    }
    case (sstStr01UInt):
    {
      //  case 1: oTestRec2.uiVal = value.toUInt(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toUInt(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toUInt(&bOK));";
      break;
    }
    case (sstStr01Long):
    {
      //  case 2: oTestRec2.lVal = value.toLongLong(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toLongLong(&bOK);";
      sBlcRowStr += sEleFncNam  + "value.toLongLong(&bOK));";
      break;
    }
    case (sstStr01ULong):
    {
      //  case 3: oTestRec2.ulVal = value.toULongLong(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toULongLong(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toULongLong(&bOK));";
      break;
    }
    case (sstStr01Float):
    {
      //  case 4: oTestRec2.fVal = value.toFloat(&bOK) ; break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toFloat(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toFloat(&bOK));";
      break;
    }
    case (sstStr01Double):
    {
      //  case 5: oTestRec2.dVal = value.toDouble(&bOK); break;
      // sBlcRowStr += "oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +" = value.toDouble(&bOK);";
      sBlcRowStr += sEleFncNam + "value.toDouble(&bOK));";
      break;
    }
    case (sstStr01String):
    {
      //    QString locStr = value.toString();
      // oTypeRec.setText( locStr.toStdString()); break;
      iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"    QString locStr = value.toString();");
      // sBlcRowStr += "strncpy(oTypeRec." + oCppClsTypRec.sClsMem.Get_EleNam() +", locStr.toUtf8(),10);";
      sBlcRowStr += "strncpy(" + sEleFncNam +", locStr.toUtf8()),10);";
      break;
    }
    default: break;
    }
    sBlcRowStr += " break;";
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,sBlcRowStr);
    // iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);
    iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"      }");
  }

  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr," ");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  }");
  iStat = oCppFncClass->writeBlcRow( 0, lSatzNr,"  if (bOK) this->oDataTable.Writ( 0, &oTypeRec, dRecNo);");
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
int sstCpp01_CsvLib_FillBlc_flags (int               iKey,
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
int sstCpp01_CsvLib_FillBlc_removeRows (int               iKey,
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
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    this->oDataTable.RecSetDeleted(0,position+1);");
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
int sstCpp01_CsvLib_FillBlc_insertRows (int               iKey,
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
  // iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    sstRec04TestRec2Cls oTestRec;");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    this->oDataTable.Read(0,this->oDataTable.count(),&this->oTypeRec);");
  iStat = oCppFncClass->writeBlcRow(0,lSatzNr,"    this->oDataTable.WritNew( 0, &this->oTypeRec, &dRecNo);");
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
