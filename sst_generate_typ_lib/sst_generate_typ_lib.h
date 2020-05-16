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

////==============================================================================
///**
//* @brief Definition Class sstCppTypDefTabCls
//*
//* More Comment
//*
//* Changed: 19.02.10  Re.
//*
//* @ingroup examples
//*
//* @author Re.
//*
//* @date 19.02.10
//*/
//// ----------------------------------------------------------------------------
//class sstCppTypDefTabCls
//{
//  public:   // Public functions
//     sstCppTypDefTabCls(sstMisc01PrtFilCls *oSstPrt);   // Constructor
//    ~sstCppTypDefTabCls();   // Destructor
//     //==============================================================================
//     /**
//     * @brief // Shortstory <BR>
//     * iStat = oTest =  Func_1( iKey);
//     *
//     * @param iKey [in] For the moment 0
//     *
//     * @return Errorstate
//     *
//     * @retval   = 0: OK
//     * @retval   < 0: Unspecified Error
//     */
//     // ----------------------------------------------------------------------------
//int LoadTypDefFromFile (int iKey, const std::string sTypDefFilNam);
////==============================================================================
///**
//* @brief // Shortstory <BR>
//* iStat = oTest =  Func_1( iKey);
//*
//* @param iKey [in] For the moment 0
//*
//* @return Errorstate
//*
//* @retval   = 0: OK
//* @retval   < 0: Unspecified Error
//*/
//// ----------------------------------------------------------------------------
//std::string getSysNam() const;
////==============================================================================
//dREC04RECNUMTYP count();
//int Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);


//private:  // Private functions
//  sstRec04Cls  *DsVerw;   /**< sst Record Table storage */
//  std::string  sSysNam;   /**< System Name (System Name of last TypeDef Record) */
//  sstMisc01PrtFilCls *poPrt;
//};
////-----------------------------------------------------------------------------


//==============================================================================
/**
* @brief Definition Class sstCppGenTypLibCls
*
* More Comment
*
* Changed: 05.04.18  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 05.04.18
*/
// ----------------------------------------------------------------------------
class sstCppGenTypLibCls
{
  public:   // Public functions
     sstCppGenTypLibCls();   // Constructor
   // ~sstCppGenTypLibCls();   // Destructor

//==============================================================================
/**
* @brief // Write CSV Type classes to system header and type class file <BR>
* iStat = sstcsv_FilWrtClsTypOpen2 ( iKey, *DsVerw, sSysNam, sDateStr);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstRec04Lib
*
* @param iKey     [in] For the moment 0
* @param DsVerw   [in] sst table with var def types
* @param sSysNam  [in] System Name
* @param sDateStr [in] Code Generation Date
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
int sstcsv_FilWrtClsTypOpen2 (int          iKey,
//                              sstRec04Cls *DsVerw,
                              sstCppTypDefTabCls *DsVerw,
                              // std::string  sSysNam,
                              std::string  sDateStr);
//==============================================================================
/**
* @brief // sst_WrtClsData_inPipe_toFilesT <BR>
* iStat = sst_WrtClsData_inPipe_toFilesT ( iKey, *sHedFil, *sClsFil, sGrpNam, *oCppTypClass);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstRec04Lib
*
* @param iKey         [in] For the moment 0
* @param sHedFil      [in] sHedFil
* @param sClsFil      [in] sClsFil
* @param sGrpNam      [in] sGrpNam
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
int sst_WrtClsData_inPipe_toFilesT2 (int                    iKey,
                                    sstMisc01AscFilCls     *sHedFil,
                                    // sstMisc01AscFilCls     *sClsFil,
                                    std::string             sGrpNam,
                                    sstCpp01_Class_Cls     *oCppTypClass);
//==============================================================================
int WriteEnumCls (int iKey,
                  sstMisc01AscFilCls  *sHedFil,
                  sstCpp01_Class_Cls  *poCppEnumClass);
//==============================================================================
/**
* @brief // Write constructor Code block to code table <BR>
* iStat = sstCpp01_CsvLib_FillBlc_Constructor ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 09.08.16  Re.
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
* @date 09.08.16
*/
//==============================================================================
int sstCpp01_CsvLib_FillBlc_Constructor (int                 iKey,
                                         sstCpp01_Class_Cls *oCppTypClass,
                                         sstCpp01_Class_Cls *oCppFncClass,
                                         dREC04RECNUMTYP    *lSatzNr);
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
  // int Dum;        /**< Dummy */
  std::string sGrpNam;  /**< Group Name like typ, fnc or qttab */
};
//-----------------------------------------------------------------------------



#endif

// ------------------------------------------------------------------- Ende ----
