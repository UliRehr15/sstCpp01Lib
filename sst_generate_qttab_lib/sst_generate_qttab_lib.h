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

#ifndef   _SST_GENERATE_QTTAB_LIB_HEADER
#define   _SST_GENERATE_QTTAB_LIB_HEADER

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstCpp01Lib.h>

// Prototypen datei.c ----------------------------------------------------------


//==============================================================================
/**
* @brief Definition Class sstCppGenQtTabLibCls
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
class sstCppGenQtTabLibCls
{
  public:   // Public functions
     sstCppGenQtTabLibCls();   // Constructor
   // ~sstCppGenQtTabLibCls();   // Destructor

     //==============================================================================
     /**
     * @brief // Write CSV Function classes to system header and fnc class file
     * iStat = sstcsv_FilWrtClsFncOpen2 ( iKey, *DsVerw, sSysNam, sDateStr);
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
     * @param sDateStr [in] Code Generation date
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
     int sstcsv_FilWrtClsFncOpen3 (int          iKey,
                                   sstCppTypDefTabCls *poTypDefTab,
                                   std::string  sSysNam,
                                   std::string  sDateStr);
     //==============================================================================
     /**
     * @brief // Write CSV Function classes to system header and fnc class file
     * iStat = sstcsv_FilWrtClsFncOpen2 ( iKey, *DsVerw, sSysNam, sDateStr);
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
     * @param sDateStr [in] Code Generation date
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
     int sstcsv_FilWrtClsFncOpen4 (int                 iKey,
                                   sstCppTypDefTabCls *poTypDefTab,
                                   std::string         sSysNam,
                                   std::string         sDateStr);
     //==============================================================================
     /**
     * @brief // sst_WrtClsData_inPipe_toFilesF <BR>
     * iStat = sst_WrtClsData_inPipe_toFilesF ( iKey, &sHedFil, &sClsFil, &sGrpNam, &oCppTypClass);
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
     int sst_WrtClsData_inPipe_toFilesF2 (int                   iKey,
                                         sstMisc01AscFilCls   *sHedFil,
                                         std::string          sGrpNam,
                                         sstCpp01_Class_Cls     *oCppTypClass);
     //==============================================================================
     int sst_WrtBaseClsData (int               iKey,
                                          sstMisc01AscFilCls   *sHedFil,
                                          sstCpp01_Class_Cls *oCppTypClass);
     //==============================================================================
     int FillBlc_constructor(int                 iKey,
                             sstCpp01_Class_Cls *oCppTypClass,
                             sstCpp01_Class_Cls *oCppFncClass,
                             dREC04RECNUMTYP    *lSatzNr);
    //==============================================================================
     int FillBlc_rowCount (int               iKey,
                                  // sstStr01Cls *oFormatInfo,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_columnCount (int               iKey,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_data (int               iKey,
                                  sstStr01Cls *poFormatInfo,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_HeaderData (int               iKey,
                                             sstStr01Cls *poFormatInfo,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_setData (int               iKey,
                                  sstStr01Cls *poFormatInfo,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_flags (int               iKey,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_removeRows (int               iKey,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     //==============================================================================
     int FillBlc_insertRows (int               iKey,
                                  sstCpp01_Class_Cls *oCppTypClass,
                                  sstCpp01_Class_Cls *oCppFncClass,
                                  dREC04RECNUMTYP     *lSatzNr);
     int FillBlc_SlotChangeTab ( sstCpp01_Class_Cls *oCppFncClass);
     int FillBlc_SlotUpdateTab ( sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_SlotChangeTab(sstCpp01_Class_Cls *oCppTypClass,
                                   sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_SlotUpdateTab(sstCpp01_Class_Cls *oCppTypClass,
                                   sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_SgnlTabChanged(sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_SgnlTabUpdated(sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass);
  //==============================================================================
     int FillBlc_ViewConstructor( sstCpp01_Class_Cls *oCppFncClass);
     int FillBlc_ViewDestructor ( sstCpp01_Class_Cls *oCppFncClass);
     int FillBlc_ViewSlotChangeTab ( sstCpp01_Class_Cls *oCppFncClass);
     int FillBlc_ViewSlotUpdateTab ( sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewConstructor(sstCpp01_Class_Cls *oCppTypClass,
                                 sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewDestructor(sstCpp01_Class_Cls *oCppTypClass,
                                sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewSlotChangeTab(sstCpp01_Class_Cls *oCppTypClass,
                                   sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewSlotUpdateTab(sstCpp01_Class_Cls *oCppTypClass,
                                   sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewSgnlTabChanged(sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass);
     int FillCls_ViewSgnlTabUpdated(sstCpp01_Class_Cls *oCppTypClass,
                                    sstCpp01_Class_Cls *oCppFncClass);
     void setGrpNam(const std::string &value);
  //==============================================================================
  std::string getGrpNam() const;
  //==============================================================================
  std::string GetDxfConstructStr(const std::string oClsNam);
  //==============================================================================

private:  // Private functions
  std::string sGrpNam;        /**< Group Name like typ, fnc or qttab */
  std::string oAddCsvIncStr;  /**< Csv List string with additional Include files names */
};



#endif

// ------------------------------------------------------------------- Ende ----
