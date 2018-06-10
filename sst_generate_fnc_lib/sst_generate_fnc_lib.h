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
//* @brief Definition Class X
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
//  // int Dum;        /**< Dummy */
//  // sstStr01VarDefCls oStrType;
//  // sstStr01VarDefFncCls oVarDefFnc;
//  sstRec04Cls  *DsVerw;   /**< sst Record Table storage */
//  std::string  sSysNam;   /**< System Name (System Name of last TypeDef Record) */
//  // dREC04RECNUMTYP dRecNo = 0;
//  sstMisc01PrtFilCls *poPrt;
//};
////-----------------------------------------------------------------------------


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
int FillBlc_Constructor(int                 iKey,
                        sstCpp01_Class_Cls *oCppFncClass,
                        dREC04RECNUMTYP    *lSatzNr);
//==============================================================================
int FillBlc_Destructor(int                 iKey,
                       sstCpp01_Class_Cls *oCppFncClass,
                       dREC04RECNUMTYP    *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -getNumber- <BR>
* iStat = FillBlc_LoadAllFromCsv ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
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
int FillBlc_LoadTabFromCsv (int               iKey,
//                              sstStr01Cls      *oFormatInfo,
//                             sstStr01VarDefCls  oClsMemDef,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -getNumber- <BR>
* iStat = FillBlc_LoadAllFromCsv ( iKey, *oCppTypClass, *oCppFncClass, *lSatzNr);
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
int FillBlc_SaveTabToCsv (int               iKey,
//                              sstStr01Cls      *oFormatInfo,
//                           sstStr01VarDefCls  oClsMemDef,
                              sstCpp01_Class_Cls *oCppTypClass,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -Count- <BR>
* iStat = FillBlc_Count ( iKey, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 02.08.17  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
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
int FillBlc_Count (int               iKey,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
/**
* @brief // Write Code Block for function -Read- <BR>
* iStat = FillBlc_Read ( iKey, *oCppFncClass, *lSatzNr);
*
* More Comment
*
* Changed: 02.08.17  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey         [in] For the moment 0
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
int FillBlc_Read (int               iKey,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
int FillBlc_Write (int               iKey,
                              sstCpp01_Class_Cls *oCppFncClass,
                              dREC04RECNUMTYP  *lSatzNr);
//==============================================================================
int FillBlc_ReadDb (int                  iKey,
                    sstStr01VarDefCls    oClsMemDef,
                    sstCpp01_Class_Cls  *oCppFncClass,
                    dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_WriteDb (int                  iKey,
                    sstStr01VarDefCls    oClsMemDef,
                    sstCpp01_Class_Cls  *oCppFncClass,
                    dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_CountDb (int                  iKey,
                     sstStr01VarDefCls    oClsMemDef,
                     sstCpp01_Class_Cls  *oCppFncClass,
                     dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_DatabaseWrite (int                  iKey,
                           sstStr01VarDefCls    oClsMemDef,
                           sstCpp01_Class_Cls  *oCppFncClass,
                           dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_LoadFromCsvFiles (int                  iKey,
                              sstStr01VarDefCls    oClsMemDef,
                              sstCpp01_Class_Cls  *oCppFncClass,
                              dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_SaveToCsvFiles (int                  iKey,
                            sstStr01VarDefCls    oClsMemDef,
                            sstCpp01_Class_Cls  *oCppFncClass,
                            dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_LoadAllFromMainFile (int                  iKey,
                                 sstStr01VarDefCls    oClsMemDef,
                                 sstCpp01_Class_Cls  *oCppFncClass,
                                 dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_SaveAllToMainFile (int                  iKey,
                               sstStr01VarDefCls    oClsMemDef,
                               sstCpp01_Class_Cls  *oCppFncClass,
                               dREC04RECNUMTYP     *lSatzNr);
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
