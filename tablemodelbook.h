#ifndef TABLEMODELBOOK_H
#define TABLEMODELBOOK_H

#include <QAbstractTableModel>

class TableModelBook : public QAbstractTableModel
{
    Q_OBJECT

public:
     explicit TableModelBook(int rowCount=100,int pageSize=10,bool allChecked=false,QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
     QList<int> m_dataList;
     QMap<int,Qt::CheckState> rowCheckStateMap;//对应行是否被选中

private:
    QHash<int,int>m_pageHash;

    int m_pageSize;
    int m_rowCount;
    QStringList  header;//表格头部内容
    int indexOfROw(int row)const;
    void fetchData(int page);
    void populateModel();
    int colNumberWithCheckBox;

     bool allSelected;//是否全选的标志


};

#endif // TABLEMODELBOOK_H
