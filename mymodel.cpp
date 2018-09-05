#include "mymodel.h"
#include <QDebug>


MyModel::MyModel(int rowCount,int pageSize,QObject *parent)
    : QAbstractTableModel(parent)
{
    this->m_pageSize=pageSize;
    this->m_rowCount=rowCount;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex MyModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex MyModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
   return m_rowCount;
   //返回每一页的行数
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
   return 1;//假设先只有一列之后再修改

}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if(Qt::DisplayRole==role){
        int i=indexOfRow(index.row());
        return m_dataList.at(i);
    }
    //不知道什么意思
    return QVariant();
}
int MyModel::indexOfRow(int row)const{
    int page=row/m_pageSize;//该行数据在第几页
    if(!m_pageHash.contains(page)){
        //如果不存在该页则新建一个页面
        (const_cast<MyModel*>(this))->fetchData(page);
    }

    //返回这一项在这一页的哪一个位置
    return m_pageHash.value(page)+row%m_pageSize;
}

//初始化新建页面的值
void MyModel::fetchData(int page){
    int pageStartIndex=m_dataList.count();//存储此页码与其所对应的开始下标值
    m_pageHash.insert(page,pageStartIndex);

    //使用分页查询，从数据库中读取数据
    for(int i=0;i<m_pageSize;++i){
        int content=page*m_pageSize+i;
        m_dataList.append((content));

    }

}
