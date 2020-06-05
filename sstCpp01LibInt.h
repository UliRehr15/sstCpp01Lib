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
// sstCpp01LibInt.h    15.08.16  Re.    15.08.16  Re.


#ifndef   _SST_CPP01_LIB_INT_HEADER
#define   _SST_CPP01_LIB_INT_HEADER

/**
 * @defgroup sstCpp01InternLib sstCpp01InternLib: Intern sst cpp coding library
 *
 * Intern sst library for cpp code generating <BR>
 *
 */


// Defines ---------------------------------------------------------------------

// Structures and Classes ------------------------------------------------------



//==============================================================================
/**
* @brief // write info rows to cpp header file <BR>
* iStat = sstCpp01_Hed_wrt_class_info ( iKey, &sExpFile, &cGrpNam, &poClsTypDsVerw, &cClsDat);
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey            [in]  For the moment 0
* @param sExpFile        [in]  Header-File
* @param cGrpNam         [in]  Lib-Name
* @param poCppClass      [in]  Cpp Class
* @param cClsDat         [in]  Date Info
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 29.06.12
*/
//------------------------------------------------------------------------------
int sstCpp01_Hed_wrt_class_info (int                 iKey,
                               sstMisc01AscFilCls *sExpFile,
                               std::string        *cGrpNam,
                                 sstCpp01_Class_Cls *poCppClass,
                               // sstRec04Cls        *poClsTypDsVerw,
                               std::string        *cClsDat);
//==============================================================================
/**
* @brief // write one class definition in open cpp header file <BR>
* iStat = sstCpp01_Hed_wrt_class ( iKey, &oHedFil, &oCppClass);
*
* Class name is generated from Sys+Grp+Cls Name.
*
* iKey = 1: Write with Base Class
* if sExtBaseCls is empty: Base Class Name = SysNam+GrpNam+Base Class
*
*      class X:
*      {
*        public:      // Public functions and elements
*           X();      // Constructor: Defined in Fnc Table
*        private:     // Private functions and elements
*          int iDum;  // Class element: Defined in Typ Table
*      };
*
* Changed: 23.09.16  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey      [in] 0 or 1
* @param oHedFil   [in] Cpp Header File
* @param oCppClass [in] Cpp Class definition
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 29.06.12
*/
//------------------------------------------------------------------------------
int sstCpp01_Hed_wrt_class (int                   iKey,
                            sstMisc01AscFilCls   *oHedFil,
                            sstCpp01_Class_Cls   *oCppClass);
//==============================================================================
/**
* @brief // sstCpp01_Hed_ClsWrTypRow <BR>
* iStat = sstCpp01_Hed_ClsWrTypRow ( iKey, &oCppClsTyp, &sExpFile);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey       [in] For the moment 0
* @param oCppClsTyp [in out] oCppClsTyp
* @param sExpFile   [in out] sExpFile
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
int sstCpp01_Hed_ClsWrTypRow (int                  iKey,
                            sstCpp01_ClsTyp_Cls   *oCppClsTyp,
                            sstMisc01AscFilCls  *sExpFile);

//==============================================================================
/**
* @brief write cpp header file
*
* iStat = sstCpp01_wrt2CppHedFil ( iKey, *oStrTypeAct);
*
* Header File Name is Name of Class. <BR>
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey:       [in]  For the moment 0
* @param oCppClass:  [in]  Class object
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 29.06.12
*/
//------------------------------------------------------------------------------
int sstCpp01_wrt2CppHedFil (int               iKey,
                       sstCpp01_Class_Cls *oCppClass);
//==============================================================================
/**
* @brief write class object to cpp class file
*
* iStat = sstCpp01_WrtCls ( iKey, &sExpFile, &sBlcDsVerw, &oCppClsFnc);
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey        [in]  For the moment 0
* @param sExpFile    [in]  File Row
* @param sBlcDsVerw  [out] Interpretation Error at String
* @param oCppClsFnc  [out] Result cpp type dataset
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 29.06.12
*/
//------------------------------------------------------------------------------
int sstCpp01_WrtCls (int                    iKey,
                       sstMisc01AscFilCls    *sExpFile,
                       sstRec04Cls           *sBlcDsVerw,
                       sstCpp01_ClsFnc_Cls     *oCppClsFnc);
//==============================================================================
/**
* @brief Write Cpp Type information to file
*
* iStat = sstCpp01_TypeWrtFil ( iKey, *sExpFil, *oSstType);
*
* More Comment
*
* Changed: 30.08.12  Re.
*
* @ingroup sstCpp01InternLib
*
* @param iKey:     [in] For the moment 0
* @param sExpFil:  [in] File to write to
* @param oSstType: [in] Format information
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*
* @author Re.
*
* @date 30.08.12
*/
//------------------------------------------------------------------------------
int sstCpp01_TypeWrtFil (int                  iKey,
                    sstMisc01AscFilCls  *sExpFil,
                    sstStr01VarDefCls   *oSstType);


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

//// iStat = Test_VectorSys_Stack ( iKey);
//int Test_VectorSys_Stack (int iKey);

//// iStat = Test_VectorSys_Heap ( iKey);
//int Test_VectorSys_Heap (int iKey);

//// Test Compare functions
//int Test_CompareFunctions (int iKey);

//==============================================================================

#endif

// --------------------------------------------------------------- File End ----

