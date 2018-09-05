#ifndef MODELDATA_H
#define MODELDATA_H

#include <QAbstractTableModel>

class modelData : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit modelData(int rowCount=100,int pageSize=10,QObject *parent = 0);

    // Header:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QHash<int,int> m_pageHash; // key是页码值, value是此页的第一项数据在dataList中的下标值
    QList<int> m_dataList;// 存储数据的容器
    int m_pageSize;// 每页显示的数据量
    int m_rowCount; // 要显示的行数

    //返回这一项在这一页的哪一个位置
    int indexOfRow(int row) const;

    void fetchData(int page);// 读取数据, 可是以模拟生成的, 实际工程中很可能是从数据库中动态读取


};

#endif // MODELDATA_H
