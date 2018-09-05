#include "tablemodelbook.h"
#define CHECK_BOX_COLUMN 0

TableModelBook::TableModelBook(int rowCount,int pageSize,bool allchecked,QObject *parent)
    : QAbstractTableModel(parent)
{
    this->m_pageSize=pageSize;
    this->m_rowCount=rowCount;
    this->allSelected=allchecked;
    populateModel();
}

QVariant TableModelBook::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
        return header[section];
    return QAbstractTableModel::headerData(section,orientation,role);
}

int TableModelBook::rowCount(const QModelIndex &parent) const
{
    return m_rowCount;

    // FIXME: Implement me!
}

int TableModelBook::columnCount(const QModelIndex &parent) const
{
    return 3;

    // FIXME: Implement me!
}

QVariant TableModelBook::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(Qt::DisplayRole==role&&index.column()!=CHECK_BOX_COLUMN){
        int i=indexOfROw(index.row());
        switch(index.column())
        {
            case 1:
                return m_dataList.at(i);
                break;
            case 2:
                return m_dataList.at(i)+1;
                break;
            defualt:
                return QVariant();
        }

    }
    if(role==Qt::CheckStateRole){
        if(index.column()==CHECK_BOX_COLUMN){
            if(rowCheckStateMap.contains(index.row()))
                return rowCheckStateMap[index.row()]==Qt::Checked?Qt::Checked:Qt::Unchecked;
            return Qt::Unchecked;//有问题
        }
    }

    // FIXME: Implement me!
    return QVariant();
}
Qt::ItemFlags TableModelBook::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags=Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    if(index.column()==CHECK_BOX_COLUMN)
        flags|=Qt::ItemIsUserCheckable;
     return  flags;
}

bool TableModelBook::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;
    if(role==Qt::CheckStateRole&&index.column()==CHECK_BOX_COLUMN){
        /*if(allSelected){
            rowCheckStateMap[index.row()]=Qt::Checked;//全选后设置每一项被check
            return true;
        }*/
        if(value==Qt::Checked){
            rowCheckStateMap[index.row()]=Qt::Checked;
            if(m_dataList.size()>index.row())
                emit dataChanged(index,index);//如果该复选框被选中执行的操作
        }else{
            rowCheckStateMap[index.row()]=Qt::Unchecked;
            if(m_dataList.size()>index.row())
                emit dataChanged(index,index);
        }
    }
    return true;
}

int TableModelBook::indexOfROw(int row) const{
    int page=row/m_pageSize;
    if(!m_pageHash.contains(page)){
        (const_cast<TableModelBook*>(this))->fetchData(page);
    }
    return m_pageHash.value(page)+row%m_pageSize;
}

void TableModelBook::fetchData(int page){
    int pageStartIndex=m_dataList.count();
    m_pageHash.insert(page,pageStartIndex);

    for(int i=0;i<m_pageSize;++i){
        int data=page*m_pageSize+i;

        m_dataList.append(data);
    }
}

void TableModelBook::populateModel(){
    header<<tr("邮箱")<<tr("电话")<<tr("分组");
}
