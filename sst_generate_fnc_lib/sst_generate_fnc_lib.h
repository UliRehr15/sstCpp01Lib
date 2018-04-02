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
// sst_generate_qttab_lib.h   06.02.2018  Re.   06.02.2018  Re.
//

#ifndef   _SST_GENERATE_TYP_LIB_HEADER
#define   _SST_GENERATE_TYP_LIB_HEADER


// Prototypen datei.c ----------------------------------------------------------



//==============================================================================
/**
* @brief Definition Class X
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup examples
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstCppGenFncLibCls
{
  public:   // Public functions
     sstCppGenFncLibCls();   // Constructor
   // ~sstCppGenFncLibCls();   // Destructor

//==============================================================================
/**
* @brief // Write Function classes to code header and code class files
* iStat = FilWrtClsFncOpen3 ( iKey, *oTypDefTab, sDateStr);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey       [in] For the moment 0
* @param oTypDefTab [in] sst table with all var def types (Group of Classes)
* @param sDateStr   [in] Generation Date
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 09.08.16
*/
//------------------------------------------------------------------------------
int FilWrtClsFncOpen3 (int    iKey,
                              sstCppTypDefTabCls *oTypDefTab,
                              std::string  sDateStr);
//==============================================================================
/**
* @brief // sst_WrtClsData_inPipe_toFilesF2 <BR>
* iStat = sst_WrtClsData_inPipe_toFilesF2 ( iKey, &sHedFil, &oCppTypClass);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param sHedFil      [in] sHedFil
* @param oCppTypClass [in] oCppTypClass
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 09.08.16
*/
//------------------------------------------------------------------------------
int sst_WrtClsData_inPipe_toFilesF2 (int                   iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstCpp01_Class_Cls     *oCppTypClass);
//==============================================================================
/**
* @brief // sst_WrtClsData_inPipe_toFilesF2 <BR>
* iStat = sst_WrtClsData_inPipe_toFilesF2 ( iKey, &sHedFil, &oCppTypClass);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param sHedFil      [in] sHedFil
* @param oCppTypClass [in] oCppTypClass
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 09.08.16
*/
//------------------------------------------------------------------------------
int sst_WrtBaseClsData (int                   iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstCpp01_Class_Cls     *oCppTypClass);
//==============================================================================

int sstCpp01_CsvLib_FillBlc_rowCount (int               iKey,
                             // sstStr01Cls *oFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);

int sstCpp01_CsvLib_FillBlc_columnCount (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);

int sstCpp01_CsvLib_FillBlc_data (int               iKey,
                             sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);

int sstCpp01_CsvLib_FillBlc_HeaderData (int               iKey,
                                        sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);
int sstCpp01_CsvLib_FillBlc_setData (int               iKey,
                             sstStr01Cls *poFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);
int sstCpp01_CsvLib_FillBlc_flags (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);
int sstCpp01_CsvLib_FillBlc_removeRows (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);
int sstCpp01_CsvLib_FillBlc_insertRows (int               iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
/**
* @brief // Write CSV_Read Code block to code table <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Read ( iKey, *oFormatInfo, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param oFormatInfo  [in] oFormatInfo
* @param oCppTypClass [in] oCppTypClass
* @param oCppFncClass [in] oCppFncClass
* @param lSatzNr      [in] lSatzNr
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 09.08.16
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_Read (int               iKey,
                             sstStr01Cls      *oFormatInfo,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // // Write CSV_Write Code block to code table <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Write ( iKey, *oFormatInfo, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 16.02.10  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param oFormatInfo  [in] oFormatInfo
* @param oCppTypClass [in] oCppTypClass
* @param oCppFncClass [in] oCppFncClass
* @param lSatzNr      [in] lSatzNr
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 16.02.10
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_Write (int               iKey,
                              sstStr01Cls      *oFormatInfo,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -getNumber- <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Number ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 02.08.17  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param oCppTypClass [in] oCppTypClass
* @param oCppFncClass [in] oCppFncClass
* @param lSatzNr      [in] lSatzNr
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 02.08.17
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_Number (int               iKey,
//                              sstStr01Cls      *oFormatInfo,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -getNumber- <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Number ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 02.08.17  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param oCppTypClass [in] oCppTypClass
* @param oCppFncClass [in] oCppFncClass
* @param lSatzNr      [in] lSatzNr
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 02.08.17
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_StrNam (int               iKey,
//                              sstStr01Cls      *oFormatInfo,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -getNumber- <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Number ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 02.08.17  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
* @param oCppTypClass [in] oCppTypClass
* @param oCppFncClass [in] oCppFncClass
* @param lSatzNr      [in] lSatzNr
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 02.08.17
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_StrTyp (int               iKey,
//                              sstStr01Cls      *oFormatInfo,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
//==============================================================================
/**
* @brief // Create sstStr01Cls.Read code row <BR>
* iStat = sstCpp01_CsvLib_CreatePrtStrRd ( iKey, cFrontTxt, *oCppCls, cEleNam, cEleNamLen, *sBlcTxt);
*
* More Comment
*
* Changed: 10.08.16  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey [in] For the moment 0
* @param cFrontTxt [in] For the moment 0
* @param oCppCls [in] For the moment 0
* @param cEleNam [in] cEleNam
* @param cEleNamLen [in] cEleNamLen
* @param sBlcTxt [out] Result sBlcTxt
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 10.08.16
*/
//------------------------------------------------------------------------------
int sstCpp01_CsvLib_CreatePrtStrRd (int               iKey,
                               std::string      cFrontTxt,
                               sstCpp01_Class_Cls *oCppCls,
                               std::string      cEleNam,
                               std::string      cEleNamLen,
                               std::string      *sBlcTxt);
//==============================================================================
/**
* @brief // Create sstStr01Cls.write code row <BR>
* iStat = sstCpp01_CsvLib_CreatePrtStrWr ( iKey, cFrontTxt, *oCppCls, *oTypDef, *sBlcTxt);
*
* More Comment
*
* Changed: 10.08.16  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey [in] For the moment 0
* @param cFrontTxt [in] cFrontTxt
* @param oCppCls [in] oCppCls
* @param oTypDef [in] oTypDef
* @param sBlcTxt [out] Result sBlcTxt
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 10.08.16
*/
//------------------------------------------------------------------------------
int sstCpp01_CsvLib_CreatePrtStrWr (int                iKey,
                               std::string        cFrontTxt,
                               sstCpp01_Class_Cls  *oCppCls,
                               sstStr01VarDefCls *oTypDef,
//                               std::string       *sVonStr,
//                               std::string       *sBisStr,
                               std::string       *sBlcTxt);


//==============================================================================
/**
* @brief // Shortstory <BR>
* iStat = oTest =  Func_1( iKey);
*
* @param iKey [in] For the moment 0
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
    // Func_1(int iKey);
// ----------------------------------------------------------------------------
  // int Dum2;       /**< Dummy2 */
  void setGrpNam(const std::string &value);

  std::string getGrpNam() const;

private:  // Private functions
  int Dum;        /**< Dummy */
  std::string sGrpNam;  /**< Group Name like typ, fnc or qttab */
};
//-----------------------------------------------------------------------------



#endif

// ------------------------------------------------------------------- Ende ----
