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
// sstCpp01Lib.h    15.08.16  Re.    15.08.16  Re.
//

#ifndef   _SST_CPP01_LIB_HEADER
#define   _SST_CPP01_LIB_HEADER

/**
 * @defgroup sstCpp01Lib sstCpp01Lib: sst cpp code generating library (Version 1)
 *
 */

// Defines ---------------------------------------------------------------------

// forward declaration ---------------------------------------------------------

//------------------------------------------------------------------------------


//==============================================================================
/**
* @brief Definition Enum sstCpp01_ClassType_enum
*
* All Cpp Class types.  <BR>
*
* Changed: 01.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 01.06.12
*/
// ----------------------------------------------------------------------------
enum _sstCpp01_ClassType_enum
{ myClsPublic,       /**< public           */
  myClsProtected,    /**< protected        */
  myClsPrivate,      /**< private          */
  myClsUnknown,      /**< unknown          */
     };
typedef enum _sstCpp01_ClassType_enum sstCpp01_ClassType_enum;
//==============================================================================
#define dCPPFILROWLENGTH 1001    /**< fix size char row   @ingroup sstRecord04Lib */
//==============================================================================
/**
* @brief File Row in Cpp Header or Code File
*
* Fixed record size, so storable in sst Table system.
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 09.08.16
*/
// ----------------------------------------------------------------------------
class sstCpp01_FilRowCls
{
  public:   // Public functions
    sstCpp01_FilRowCls();   // Constructor
    // ~X();   // Destructor
    //==============================================================================
    /**
    * @brief // set string to cpp file row <BR>
    * iStat = oCppFilRow.setRow ( oStr);
    *
    * @param oStr [in] set string
    */
    // ----------------------------------------------------------------------------
    void setRow(std::string oStr);
    //==============================================================================
    /**
    * @brief // get string from cpp fil row <BR>
    * oStr = oCppFilRow.getRow ();
    *
    * @return Return cpp file row as std::string
    */
    // ----------------------------------------------------------------------------
    std::string getRow();
// ----------------------------------------------------------------------------
  private:  // Private functions
    char  cCharRow[dCPPFILROWLENGTH];        /**< fix size char row  */
};
//==============================================================================//==============================================================================
/**
* @brief Definition sstCpp01_ClsTyp_Cls
*
* More Comment
*
* Changed: 03.07.12  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 03.07.12
*/
// ----------------------------------------------------------------------------
class sstCpp01_ClsTyp_Cls
{
  public:   // Öffentliche Funktionen
     sstCpp01_ClsTyp_Cls();  // Konstruktor
     sstCpp01_ClassType_enum eClsVisiTyp;  /**< eClsVisiTyp public, protected or private  */
     sstStr01VarDefCls sClsMem;      /**< sClsMem   */
  private:  // Private Funktionen
};
//==============================================================================
/**
* @brief Definition sstCpp01_ClsFnc_Cls
*
* Class information writes class frame in file
*
* Changed: 03.07.12  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 03.07.12
*/
// ----------------------------------------------------------------------------
class sstCpp01_ClsFnc_Cls
{
  public:
     sstCpp01_ClsFnc_Cls();  // Constructur
     sstStr01VarType_enum      eCppType;                  /**< Return type of function      */
     sstCpp01_ClassType_enum eClsVisiTyp;                       /**< public, protected or private */
     char              cClsNam[dSST_STR01_VAR_NAM_LEN];   /**< Class Name         */
     char              cFncNam[dSST_STR01_VAR_NAM_LEN];   /**< Function Name      */
     char              cFncPar[dCPPFILROWLENGTH];         /**< Function Parameter without parenthis */
     char              cFncCom[dCPPFILROWLENGTH];         /**< Function Comment   */
     long              lBlcStart;                         /**< lBlcStart in Codeblock Table   */
     long              lBlcRows;                          /**< lBlcRows in Codeblock Table    */
  private:
};
//==============================================================================
/**
* @brief Definition sstCpp01_Class_Cls
*
* More Comment
*
* Changed: 12.09.12  Re.
*
* 12.09.12: Generating Date inserted.  Re.
*
* @ingroup sstCpp01Lib
*
* @author Re.
*
* @date 03.07.12
*/
// ----------------------------------------------------------------------------
class sstCpp01_Class_Cls
{
  public:   // Öffentliche Funktionen
  // sstCpp01_Class_Cls(): ClsTypDsVerw(sstCpp01_ClsTyp_Cls),ClsFncDsVerw(sstCpp01_ClsFnc_Cls),ClsBlcDsVerw(sstMisc01AscRowCls);  // Konstruktor
  sstCpp01_Class_Cls();  // Konstruktor
//     int GetDate(int iKey, StrDS1_stru *sDateStr);
//     int SetDate(int iKey, StrDS1_stru sDateStr);
     //==============================================================================
     /**
     * @brief // Get date string <BR>
     * iStat = oCppClass.GetDate( iKey, &sDateStr);
     *
     * @param iKey [in] For the moment 0
     * @param sDateStr [out] Return date string
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetDate(int iKey, std::string *sDateStr);
     //==============================================================================
     /**
     * @brief // Set date to object <BR>
     * iStat = oCppClass.SetDate( iKey, &sDateStr);
     *
     * @param iKey [in] For the moment 0
     * @param sDateStr [in] Set date string
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetDate(int iKey, std::string sDateStr);
     //==============================================================================
     /**
     * @brief // Set class name to class object <BR>
     * iStat = oCppClass.SetClsNam( iKey, &oClsNam);
     *
     * @param iKey    [in] For the moment 0
     * @param oClsNam [in] Set class name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetClsNam(int iKey, std::string oClsNam);
     //==============================================================================
     /**
     * @brief // Set system name to class object <BR>
     * iStat = oCppClass.SetSysNam( iKey, &oSysNam);
     *
     * @param iKey    [in] For the moment 0
     * @param oSysNam [in] Set system name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetSysNam(int iKey, std::string oSysNam);
     //==============================================================================
     /**
     * @brief // Set group name to class object <BR>
     * iStat = oCppClass.SetGrpNam( iKey, &oGrpNam);
     *
     * @param iKey    [in] For the moment 0
     * @param oGrpNam [in] Set group name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetGrpNam(int iKey, std::string oGrpNam);
     //==============================================================================
     /**
     * @brief // Get System name <BR>
     * oSysNamStr = oCppClass.GetSysNam();
     *
     * @retval   = string system name
     */
     // ----------------------------------------------------------------------------
     std::string GetSysNam();
     //==============================================================================
     /**
     * @brief // Get group name <BR>
     * oGrpNamStr = oCppClass.GetGrpNam();
     *
     * @retval   = string group name
     */
     // ----------------------------------------------------------------------------
     std::string GetGrpNam();
     //==============================================================================
     /**
     * @brief // Get class name <BR>
     * oClsNamStr = oCppClass.GetClsNam();
     *
     * @retval   = string class name
     */
     // ----------------------------------------------------------------------------
     std::string GetClsNam();
     //==============================================================================
     /**
     * @brief // Get Lib class name <BR>
     * oLibClsNamStr = oCppClass.GetLibClsNam();
     *
     * sysnam + grpnam + clsnam + "Cls"
     *
     * @retval   = string generated lib class name
     */
     // ----------------------------------------------------------------------------
     std::string GetLibClsNam();
     //==============================================================================
     /**
     * @brief // write all type defs in class info area of header file <BR>
     * iStat = oCppClass.HeadWrtTypDefInfo (iKey);
     *
     * @param iKey    [in] For the moment 0
     * @param sHedFil [in] sHedFil
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int HeadWrtTypDefInfo(int                 iKey,
                           sstMisc01AscFilCls *sHedFil);
     //==============================================================================
     /**
     * @brief // return number of member <BR>
     * uiNumOfMem = oCppClass.getNumberOfMember();
     *
     * @retval return unsigned int number of member
     */
     // ----------------------------------------------------------------------------
     unsigned int getNumberOfMember();
     //==============================================================================
     /**
     * @brief // return string with all member names <BR>
     * sStrAllNames = oCppClass.getMemberNameStr();
     *
     * @retval   = string with all member names as csv
     */
     // ----------------------------------------------------------------------------
     std::string getMemberNameStr();
     //==============================================================================
     /**
     * @brief // return string with all member types <BR>
     * sStrAllTypes = oCppClass.getMemberTypeStr();
     *
     * @retval   = string with all member types as csv
     */
     // ----------------------------------------------------------------------------
     std::string getMemberTypeStr();
     //==============================================================================

     sstRec04Cls  *ClsTypDsVerw;   /**< table with all type definitions */
     sstRec04Cls  *ClsFncDsVerw;   /**< Table with for all function definitions */
     sstRec04Cls  *ClsBlcDsVerw;   /**< Table with all function inside code rows */
     char cClsNam[dSST_STR01_VAR_NAM_LEN];  /**< Class name */
     char cSysNam[dSST_STR01_VAR_NAM_LEN];  /**< System (parent) name of class, for example dxf, csv, ...  */
     char cGrpNam[dSST_STR01_VAR_NAM_LEN];  /**< Function Group name of class, for example typ, fnc   */
  private:  // Private Funktionen
     std::string sDateStr;  // Write Date in generating header and class file
};


//==============================================================================
/**
* @brief write filename/date row in cpp code and header file
*
* iStat = str_CppFil_wrt_head ( iKey, *sExpFile, *cFilDat);
*
* For example:
* Row: // Template.h   29.04.10  Re.   29.04.10  Re.
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey:     [in] For the moment 0
* @param sExpFile: [in] Header or Class file
* @param cFilDat:  [in] Date for writing in header
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
int sstCpp01_Fil_wrt_head (int                 iKey,
                         sstMisc01AscFilCls *sExpFile,
                         std::string        *cFilDat);
//==============================================================================
/**
* @brief // write comment to cpp header file <BR>
* iStat = sstCpp01_Hed_WrtCom ( iKey, *sExpFile, *cObjNam);
*
* Row: Definitions of class "XXX"
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey      [in]  For the moment 0
* @param sExpFile  [in]  sExpFile
* @param cObjNam   [out] cObjNam
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
int sstCpp01_Hed_WrtCom (int                 iKey,
                       sstMisc01AscFilCls *sExpFile,
                       std::string        *cObjNam);
//==============================================================================
/**
* @brief // write define open rows in cpp header file  <BR>
* iStat = sstCpp01_Hed_wrt_def_open ( iKey, &sExpFile, cLibNam, cSysNam, cGrpNam, cObjNam);
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey      [in]  For the moment 0
* @param sExpFile  [in]  File
* @param cLibNam   [out] cLibNam
* @param cSysNam   [out] cSysNam
* @param cGrpNam   [out] cGrpNam
* @param cObjNam   [out] cObjNam
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
int sstCpp01_Hed_wrt_def_open (int                  iKey,
                             sstMisc01AscFilCls  *sExpFile,
                             std::string          cLibNam,
                             std::string          cSysNam,
                             std::string          cGrpNam,
                             std::string          cObjNam);
//==============================================================================
/**
* @brief // write include rows to cpp class file <BR>
* iStat = sstCpp01_Cls_WrtInc ( iKey, &sExpFile, &oCppClass);
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey     [in]  For the moment 0
* @param sExpFile  [in]  File Row
* @param oCppClass  [out] Interpretation Error at String
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
int sstCpp01_Cls_WrtInc (int                   iKey,
                       sstMisc01AscFilCls   *sExpFile,
                       sstCpp01_Class_Cls     *oCppClass);
//=============================================================================
int sstCpp01_Hed_wrt_defgroup (int                 iKey,
                               sstMisc01AscFilCls *sExpFile,
                               std::string         cGrpNam);
//==============================================================================
/**
* @brief // write end define rows in cpp header file <BR>
* iStat = sstCpp01_Hed_wrt_def_close ( iKey, *sExpFile);
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey      [in]  For the moment 0
* @param sExpFile  [in]  File Row
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
int sstCpp01_Hed_wrt_def_close (int                 iKey,
                              sstMisc01AscFilCls *sExpFile);
//==============================================================================
/**
* @brief // write one class definition to cpp header file <BR>
* iStat = sstCpp01_wrt2CppHedFil2 ( iKey, *sCppHedFil, &oCppClass);
*
* Header File Name is Name of Class. <BR>
*
* Changed: 29.06.12  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey:      [in]  For the moment 0
* @param sCppHedFil [in]  sCppHedFil
* @param oCppClass  [in]  oCppClass
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
int sstCpp01_wrt2CppHedFil2 (int                   iKey,
                        sstMisc01AscFilCls   *sCppHedFil,
                        sstCpp01_Class_Cls     *oCppClass);
//==============================================================================
/**
* @brief // write information to cpp class file of member class <BR>
* iStat = sstCpp01_wrt2CppClsFil2 ( iKey, *sCppHedFil, *oCppClass);
*
* More Comment
*
* Changed: 09.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey [in] For the moment 0
* @param sCppHedFil [in] sCppHedFil
* @param oCppClass  [in] oCppClass
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
int sstCpp01_wrt2CppClsFil2 (int                   iKey,
                        sstMisc01AscFilCls   *sCppHedFil,
                        sstCpp01_Class_Cls     *oCppClass);
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
* @brief // Open all tables of CppClass <BR>
* iStat = sstCpp01_ClassTab_Open ( iKey, *oCppClass);
*
* More Comment
*
* Changed: 10.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey [in] For the moment 0
* @param oCppClass [in] oCppClass
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
int sstCpp01_ClassTab_Open (int iKey, sstCpp01_Class_Cls *oCppClass);
//==============================================================================
/**
* @brief // Close all tables of CppClass <BR>
* iStat = sstCpp01_ClassTab_Close ( iKey, *oCppClass);
*
* More Comment
*
* Changed: 10.08.16  Re.
*
* @ingroup sstCpp01Lib
*
* @param iKey [in] For the moment 0
* @param oCppClass [in] oCppClass
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
int sstCpp01_ClassTab_Close (int iKey, sstCpp01_Class_Cls *oCppClass);

#endif // SST_REC01_LIB

