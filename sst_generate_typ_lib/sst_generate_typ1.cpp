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

#include "sst_generate_typ_lib.h"

//=============================================================================
sstCppGenTypLibCls::sstCppGenTypLibCls()
{

}
//=============================================================================
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_Constructor (int                  iKey,
                                                             sstCpp01_Class_Cls  *oCppTypClass,
                                                             sstCpp01_Class_Cls  *oCppFncClass,
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

  // Die Anzahl der aktuell gespeicherten Datens?tze zur?ckgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

  sstCpp01_ClsTyp_Cls oMemRec;

  std::string oBlcStr;
  std::string oObjNamStr;
  iStat = oCppTypClass->ClsTypDsVerw->Read( 0, 1, &oMemRec);
  oObjNamStr = oMemRec.sClsMem.Get_ObjNam();
  if (oObjNamStr.length() > 0)
  {  //   memset( this, 0, sizeof(PtssTypPKCls));
    oBlcStr =  "   memset( this, 0, sizeof(" + oCppTypClass->GetSysNam() + oCppTypClass->GetGrpNam() + oObjNamStr +"Cls));";
    iStat = oCppFncClass->writeBlcRow(0, lSatzNr, oBlcStr);
  }


  return iStat;
}
//=============================================================================
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_Read (int                  iKey,
                                                      sstStr01Cls         *oFormatInfo,
                                                      sstCpp01_Class_Cls  *oCppTypClass,
                                                      sstCpp01_Class_Cls  *oCppFncClass,
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

  // Die Anzahl der aktuell gespeicherten Datens?tze zur?ckgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;

  // Fill Function Block

//  StrDS1_stru sErrTxt;
//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

  // iStat = oCppFncClass->writeBlcRow(0, lSatzNr,"//  Bloc Function1 Start");
  iStat = oCppFncClass->writeBlcRow(0, lSatzNr,"//  sstStr01Cls sErrTxt;");
  iStat = oCppFncClass->writeBlcRow(0, lSatzNr,"  sstStr01Cls oCsvRow;");

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

//  sBlcTxt =  (char*) "//  Bloc Function1 End";
//  sBlcRow.setRow(sBlcTxt);
//  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

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
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_Write (int               iKey,
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

  // Die Anzahl der aktuell gespeicherten Datens?tze zur?ckgeben.
  lClsTypNum = oCppTypClass->ClsTypDsVerw->count();
  if (lClsTypNum <= 0) return -2;
  // Fill Function Block

//  StrDS1_stru sErrTxt;
//  int iRet  = 0;
//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;


//  sBlcTxt =  (char*) "//  Bloc Function Write Start";
//  sBlcRow.setRow(sBlcTxt);
//  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

  iStat = oCppFncClass->writeBlcRow(0, lSatzNr,"  sstStr01Cls oCsvRow;");
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
      iStat = sstCpp01_CsvLib_CreatePrtStrWr ( 0, (char*) "    iStat = oCsvRow.Csv_RealFrmt_2String ( 0, ",
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

//  sBlcTxt =  (char*) "//  Bloc Function Write End";
//  sBlcRow.setRow(sBlcTxt);
//  iStat = oCppFncClass->ClsBlcDsVerw->WritNew( 0, &sBlcRow, lSatzNr);

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
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_Number (int               iKey,
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
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_StrNam (int               iKey,
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
int sstCppGenTypLibCls::sstCpp01_CsvLib_FillBlc_StrTyp (int               iKey,
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
//=============================================================================
int sstCppGenTypLibCls::sstCpp01_CsvLib_CreatePrtStrRd (int               iKey,
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
    // *sBlcTxt = *sBlcTxt + "_Str, o";
    *sBlcTxt = *sBlcTxt + "_Str, ";
  }
  else
  {
    // *sBlcTxt = *sBlcTxt + "_Str, &o";
    *sBlcTxt = *sBlcTxt + "_Str, &";
  }

//  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;
//  *sBlcTxt = *sBlcTxt + oCppCls->cGrpNam;
//  *sBlcTxt = *sBlcTxt + oCppCls->cClsNam;
  *sBlcTxt += "this";
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
int sstCppGenTypLibCls::sstCpp01_CsvLib_CreatePrtStrWr (int          iKey,
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
//  *sBlcTxt = *sBlcTxt + "o";
//  *sBlcTxt = *sBlcTxt + oCppCls->cSysNam;
//  *sBlcTxt = *sBlcTxt + oCppCls->cGrpNam;
//  *sBlcTxt = *sBlcTxt + oCppCls->cClsNam;
  *sBlcTxt = *sBlcTxt + "this->";
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
void sstCppGenTypLibCls::setGrpNam(const std::string &sTmpGrpNam)
{
  this->sGrpNam = sTmpGrpNam;
}
//=============================================================================
std::string sstCppGenTypLibCls::getGrpNam() const
{
  return this->sGrpNam;
}
//=============================================================================
