# sstCpp01Lib
sst C++ Code Creating Library

This Library is created with QtCreator 4.5.2 and gcc 7.3.0.

Tool sst_generate_csv_lib

Tool generates code for lib sst_str01_lib for import /export of csv data.
record definition comes from file with type def data.

- Tool Generate_Typ_Lib generates Record/Csv Objects from TypeDef File.
- Tool Generate_Fnc_Lib generates Database Objects from TypeDef File.
- Tool Generate_QtTab_Lib generates Qt Table Model Objects from TypeDef File.

Structure of coding projects should be:

.. [libs] <BR>
   [sstStr01Lib] <BR>
   [sstMath01Lib] <BR>
   [sstMisc01Lib] <BR>
   [sstRec04Lib] <BR>
   [Doxygen_ouput] <BR>

August 2016, Hanover, Germany, Uli Rehr

Versions <BR>
20160815: Vers. 1.0: First Check in. <BR>
20160926: Vers. 1.1: Some improvements for generating sstDxf02Lib Code. <BR>
20170116: Vers. 1.2: New class VarTypeDef Table. <BR>
                     Create Test project. <BR>
20170811: Vers. 1.3: Generate new functions -GetNumberElements, GetAllNameStr, GetAllTypeStr-. <BR>
20171225: Vers. 1.4: More Doxygen help. <BR>
20180127: Vers. 1.5: Insert function SetReadPosition in CSV_READ, CSV_WRITE.  <BR>
20180315: Vers. 1.6: New App -Generate_QtTab_Lib-, which generates Qt Table Model Objects Code <BR>
                     from TypeDef file. Needs generated code from app -Generate_Csv_Lib-.  <BR>
20180318: Vers. 1.7: Fit library for sst_dxf03_lib. <BR>
20180323: Vers. 1.8: Small improvements in working with typeDef files. <BR>
20180323: Vers. 1.9: New Table Class for storing TypeDef Records. <BR>
                     New Tool -Generate_Typ_Lib-, which generate record/csv objects code from TypeDef file. <BR>
20180402: Vers. 1.10: New Tool -Generate_Fnc_Lib, which generate database objects code from Typedef file. <BR>
20180501: Vers. 1.11: Tool -Generate_qttab_Lib- extended. <BR>
                      Tool -Generate_fnc_lib- extended. <BR>
20180504: Vers. 1.12: Tool -Generate_qttab_lib- extended. <BR>
                      Tool -Generate_csv_lib- removed and replaced by -typ- and -fnc-. <BR>
20180528: Vers. 1.13: Small improvements in generate_typ, generate_fnc. <BR>
20180610: Vers. 1.14: Tool -Generate_qttab_Lib- extended for general, not dxf case. <BR>
                      Tool -Generate_fnc_lib- extended for general, not dxf case. <BR>
20180914: Vers. 1.15: Update to QtCreator 4.5.2 and gcc 7.3.0. <BR>
