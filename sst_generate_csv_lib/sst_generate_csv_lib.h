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
// sst_generate_csv_lib.h   29.06.16  Re.   29.06.16  Re.
//

#ifndef   _SST_GENERATE_CSV_LIB_HEADER
#define   _SST_GENERATE_CSV_LIB_HEADER


// Prototypen datei.c ----------------------------------------------------------
//==============================================================================
/**
* @brief // Write CSV Type classes to type header and type class file <BR>
* iStat = sstcsv_FilWrtClsTypOpen ( iKey, *DsVerw, sSysNam, sDateStr);
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
int sstcsv_FilWrtClsTypOpen (int          iKey,
                             sstRec04Cls *DsVerw,
                             std::string  sSysNam,
                             std::string  sDateStr);
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
                              sstRec04Cls *DsVerw,
                              std::string  sSysNam,
                              std::string  sDateStr);
//==============================================================================
/**
* @brief // Write CSV Function classes to fnc header and fnc class file
* iStat = sstcsv_FilWrtClsFncOpen ( iKey, *DsVerw, sSysNam, sDateStr);
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
int sstcsv_FilWrtClsFncOpen (int          iKey,
                             sstRec04Cls *DsVerw,
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
int sstcsv_FilWrtClsFncOpen2 (int          iKey,
                              sstRec04Cls *DsVerw,
                              std::string  sSysNam,
                              std::string  sDateStr);
//==============================================================================
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
                              sstRec04Cls *DsVerw,
                              std::string  sSysNam,
                              std::string  sDateStr);
//==============================================================================
/**
* @brief // sst_WrtClsData_inPipe_toFilesT <BR>
* iStat = sst_WrtClsData_inPipe_toFilesT ( iKey, *sHedFil, *sClsFil, *oCppTypClass);
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
int sst_WrtClsData_inPipe_toFilesT (int                   iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    // sstMisc01AscFilCls   *sClsFil,
                                    sstCpp01_Class_Cls     *oCppTypClass);
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
int sst_WrtClsData_inPipe_toFilesF (int                   iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    // sstMisc01AscFilCls   *sClsFil,
                                    std::string          *sGrpNam,
                                    sstCpp01_Class_Cls     *oCppTypClass);
//==============================================================================
/**
* @brief // sst_WrtClsData_inPipe_toFilesT <BR>
* iStat = sst_WrtClsData_inPipe_toFilesT ( iKey, *sHedFil, *sClsFil, *oCppTypClass);
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
int sst_WrtClsData_inPipe_toFilesT2 (int                   iKey,
                                    sstMisc01AscFilCls   *sHedFil,
                                    sstMisc01AscFilCls   *sClsFil,
                                     std::string      sGrpNam,
                                    sstCpp01_Class_Cls     *oCppTypClass);
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
                                    sstMisc01AscFilCls   *sClsFil,
                                    std::string          sGrpNam,
                                    sstCpp01_Class_Cls     *oCppTypClass);

#endif

// ------------------------------------------------------------------- Ende ----
