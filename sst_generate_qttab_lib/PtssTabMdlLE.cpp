//  PtssTabMdlLE.cpp   21.03.18  Re.   21.03.18  Re.
//
//  Functions for Class "Ptss"
//
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#include <string>
 
#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
 
#include <list>
#include <dl_dxf.h>
#include <dl_creationadapter.h>
#include <rs_vector.h>
#include <QtWidgets>
#include <sstQt01Lib.h>
#include <PtssTypLib.h>
#include <PtssFncLib.h>
 
#include "PtssTabMdlLib.h"
 
// // Constructor
PtssTabMdlLECls::PtssTabMdlLECls(QObject *parent, sstMisc01PrtFilCls *poTmpPrt, PtssFncDatabaseCls *poTmpDatabase):sstQt01TabMdlCls(parent)
{
  this->poPrt = poTmpPrt;
  this->poDatabase = poTmpDatabase;
  
  dREC04RECNUMTYP dRecNum = this->poDatabase->CountDbLE();
  
  for (dREC04RECNUMTYP ll=1; ll<=dRecNum; ++ll)
  {
    this->sstTabVector.push_back(ll);
  }
}
 
// // Constructor
PtssTabMdlLECls::~PtssTabMdlLECls()
{
 
}
 
// Count actual number of records
int PtssTabMdlLECls::rowCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = this->poDatabase->CountDbLE();
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
int PtssTabMdlLECls::columnCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = 1;
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
QVariant PtssTabMdlLECls::data(const QModelIndex &index, int role) const
{
//  Bloc Code Generation Start
  PtssTypLECls oTypRec;
  DL_Attributes oDLAttributes;
 
  int iStat = this->poDatabase->ReadDbLE( 0, this->sstTabVector[index.row()], &oTypRec);
  assert (iStat == 0);
 
  switch(role){
  case Qt::DisplayRole:
    {
      switch (index.column())
      {
        case 0: return QString::fromUtf8(oTypRec.LE1); break;
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
QVariant PtssTabMdlLECls::headerData(int section, Qt::Orientation orientation, int role) const
{
//  Bloc Code Generation Start
  if (role == Qt::DisplayRole)
  {
      if (orientation == Qt::Horizontal) {
          switch (section)
          {
        case 0: return QString("LE1");
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
bool PtssTabMdlLECls::setData(const QModelIndex & index, const QVariant & value, int role)
{
//  Bloc Code Generation Start
 
if (role == Qt::EditRole)
{
  //save value from editor to oTestRecDss
  PtssTypLECls oTypRec;
  DL_Attributes oDLAttributes;
  dREC04RECNUMTYP dMainRecNo = 0;
 
  dREC04RECNUMTYP dRecNo = index.row() +1;
  this->poDatabase->ReadDbLE( 0, this->sstTabVector[index.row()], &oTypRec);
 
  bool bOK = 1;
      switch (index.column())
      {
        case 0: 
      {
        QString locStr = value.toString();
        strncpy(oTypRec.LE1, locStr.toUtf8(),10); break;
      }
 
  }
  if (bOK) this->poDatabase->WriteDbLE( 0, &oTypRec, &dRecNo);
 
  }
  return true;
//  Bloc Code Generation End
}
 
// return number of table columns
Qt::ItemFlags PtssTabMdlLECls::flags(const QModelIndex &index) const
{
//  Bloc Code Generation Start
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
//  Bloc Code Generation End
}
 
// return number of table columns
bool PtssTabMdlLECls::removeRows(int position, int rows, const QModelIndex &index)
{
//  Bloc Code Generation Start
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position + rows - 1);
 
  // rows is always = 1 at the moment
  // Position is 0 > n-1
 
  for (int row = 0; row < rows; ++row) {
    // this->poDatabase->RecSetDeleted(0,position+1);
  }
  endRemoveRows();
 
  this->sstTabVector.erase (this->sstTabVector.begin()+position);
 
  return true;
//  Bloc Code Generation End
}
 
// return number of table columns
bool PtssTabMdlLECls::insertRows(int position, int rows, const QModelIndex &index)
{
//  Bloc Code Generation Start
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position + rows - 1);
  
  // rows is always = 1 at the moment
  // Position is 0 > n-1
  dREC04RECNUMTYP dRecNo = 0;
  
  for (int row = 0; row < rows; ++row) {
    // this->poDatabase->Read(0,this->poDatabase->count(),&this->oTypeRec);
    // this->poDatabase->WritNew( 0, &this->oTypeRec, &dRecNo);
  }
 
  endInsertRows();
 
  this->sstTabVector.push_back(dRecNo);
  
  return true;
//  Bloc Code Generation End
}
