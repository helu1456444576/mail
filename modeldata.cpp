#include "modeldata.h"
#include <QDebug>

modelData::modelData(int rowCount,int pageSize,QObject *parent)
    : QAbstractTableModel(parent)
{
    this->m_pageSize=pageSize;
    this->m_rowCount=rowCount;
}

QVariant modelData::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int modelData::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return m_rowCount;

    // FIXME: Implement me!
}

int modelData::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 1;

    // FIXME: Implement me!
}

QVariant modelData::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(Qt::DisplayRole==role){
        int i=indexOfRow(index.row());
        return m_dataList.at(i);
    }
    // FIXME: Implement me!
    return QVariant();
}

int modelData::indexOfRow(int row)const{
    int page=row/m_pageSize;
    if(!m_pageHash.contains(page)){
        (const_cast<modelData*>(this))->fetchData(page);
    }
    return m_pageHash.value(page)+row%m_pageSize;
}

void modelData::fetchData(int page){
    int pageStartIndex=m_dataList.count();
    m_pageHash.insert(page,pageStartIndex);

    for(int i=0;i<m_pageSize;++i){
        int data=page*m_pageSize+i;
        m_dataList.append(data);
    }
}
