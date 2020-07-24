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
// sst_generate_fnc_lib.h   06.02.2018  Re.   06.02.2018  Re.
//

#ifndef   _SST_GENERATE_FNC_LIB_HEADER
#define   _SST_GENERATE_FNC_LIB_HEADER

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstCpp01Lib.h>

//==============================================================================
/**
* @brief Definition Class sstCppGenFncLibCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstCpp01Lib
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
* @brief // Write Stuff for Functions ReadDb, WriteDb and CountDb into Pipe-Buffer <BR>
* iStat = sst_WrtClsData_inPipe_toFilesF3 ( iKey, &sHedFil, &oCppTypClass);
*
* More Comment
*
* Changed: 07.05.20  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey          [in] For the moment 0
* @param plSatzNrBlc   [in out] plSatzNrBlc
* @param oStrType      [in] oStrType
* @param poCppFncClass [in out] poCppFncClass
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 07.05.20
*/
//------------------------------------------------------------------------------
int sst_WrtClsData_inPipe_toFilesF3 (int                      iKey,
                                     // dREC04RECNUMTYP         *plStzBlcNr,
                                     const sstStr01VarDefCls  oStrType,
                                     sstCpp01_Class_Cls      *poCppFncClass);
//==============================================================================
/**
* @brief // Write base class data to class and header file without base class <BR>
* iStat = sst_WrtBaseClsData ( iKey, &sHedFil, &oCppTypClass);
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
int WriteEnumCls(int                  iKey,
                 sstMisc01AscFilCls  *sHedFil,
                 sstCpp01_Class_Cls  *oCppTypClass);
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
int FillBlc_SaveTabToCsv (int                 iKey,
                          sstCpp01_Class_Cls *oCppTypClass,
                          sstCpp01_Class_Cls *oCppFncClass,
                          dREC04RECNUMTYP    *lSatzNr);
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
/**
* @brief // Write Codebloc for function Constructor to Database Cls <BR>
* iStat = oCppDatabaseGen.FillBlc_Constructor( iKey, oClsMemDef, oCppFncClass);
*
* @param iKey         [in] For the moment 0
* @param oClsMemDef   [in] oClsMemDef
* @param oCppFncClass [in out] Class Database Definition
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
int FillBlc_ConstructorDb (int                  iKey,
                           sstStr01VarDefCls    oClsMemDef,
                           sstCpp01_Class_Cls  *oCppFncClass);
//==============================================================================
/**
* @brief // Write Codebloc for function Constructor to Database Cls <BR>
* iStat = oCppDatabaseGen.FillBlc_Constructor( iKey, oClsMemDef, oCppFncClass);
*
* @param iKey          [in] For the moment 0
* @param oClsMemDef   [in] oClsMemDef
* @param oCppFncClass [in out] Class Database Definition
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
int FillBlc_DestructorDb (int                  iKey,
                          sstStr01VarDefCls    oClsMemDef,
                          sstCpp01_Class_Cls  *oCppFncClass);
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
                              sstCpp01_Class_Cls  *oCppTypClass,
                              sstCpp01_Class_Cls  *oCppFncClass,
                              dREC04RECNUMTYP     *lSatzNr);
//==============================================================================
int FillBlc_SaveToCsvFiles (int                  iKey,
                            sstCpp01_Class_Cls  *oCppTypClass,
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
* @brief // Write definition and codebloc for function Constructor to Database Cls <BR>
* iStat = oCppDatabaseGen.FillCls_Constructor( oClsMemDef, oCppFncClass);
*
* @param iKey [in] For the moment 0
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
int FillCls_ConstructorDB( sstStr01VarDefCls    oClsMemDef,
                           sstCpp01_Class_Cls  *oCppFncClass);
//==============================================================================
/**
* @brief // Write definition and codebloc for function Destructor to Database Cls <BR>
* iStat = oCppDatabaseGen.FillCls_Destructor( oClsMemDef, oCppFncClass);
*
* @param iKey [in] For the moment 0
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
int FillCls_DestructorDB( sstStr01VarDefCls    oClsMemDef,
                          sstCpp01_Class_Cls  *oCppFncClass);
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
