#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <Qt>
#include <QList>
#include <QHash>


class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MyModel(int rowCount=100,int pageSize,QObject *parent=0);


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QHash<int,int> m_pageHash;//key是页码值, value是此页的第一项数据在dataList中的下标值
    QList<int> m_dataList;// 存储数据的容器
    int m_pageSize;//每页显示的数据量
    int m_rowCount;//要显示的行数
    //获得每一页数据的起始位置
    int indexOfRow(int row)const;
    //读取每一页的数据
    void fetchData(int page);


};

#endif // MYMODEL_H
