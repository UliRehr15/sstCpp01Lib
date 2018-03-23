# sstCpp01Lib
sst C++ Code Creating Library

This library should be build with QT 5.5 and qt creator 3.5.1.

Tool sst_generate_csv_lib

Tool generates code for lib sst_str01_lib for import /export of csv data.
record definition comes from file with type def data.

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
20180315: Vers. 1.6: New App -Generate_QtTab_Lib-, which generates Qt Table Model Objects <BR>
                     from TypeDef file. Needs generated code from app -Generate_Csv_Lib-.  <BR>
20180318: Vers. 1.7: Fit library for sst_dxf03_lib. <BR>
20180323: Vers. 1.8: Small improvements in working with typeDef files. <BR>
