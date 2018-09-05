#include "widget.h"
#include "ui_widget.h"
#include "tablemodel.h"
#include <QDebug>
#include <QListWidgetItem>
#include <QAbstractItemView>
#include <QInputDialog>
#include <QDir>
#include "tablemodelbook.h"
#include <QStandardItemModel>
#include <QLineEdit>
#include <QMessageBox>
#include "database.h"
#include "user.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    nowUser=new User("hl","123456");
    //初始化model中的一些值
    //查询数据库获得所有收到的文件
    QString name=nowUser->getUserName();
    DataBase db;
    receiverMails=db.receiverMailSelected("hl");

    //更改构造函数将list赋值进去
    //收件箱
     model=new TableModel(100,8,false,this,receiverMails);
    ui->tableView->setModel(model);
  //  ui->tableViewMailMail->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setFrameShape(QFrame::NoFrame);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //设置显示全部联系人的页面
    //查询数据库获得当前用户的所有联系人
    //更改构造函数将list赋值进去
    modelBook=new TableModelBook(100,8,false,this);
    ui->tableViewAllBook->setModel(modelBook);
    ui->tableViewAllBook->resizeColumnsToContents();
    ui->tableViewAllBook->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewAllBook->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewAllBook->horizontalHeader()->setHighlightSections(false);
    ui->tableViewAllBook->verticalHeader()->setVisible(false);
    ui->tableViewAllBook->setShowGrid(false);
    ui->tableViewAllBook->setFrameShape(QFrame::NoFrame);
    ui->tableViewAllBook->setSelectionMode(QAbstractItemView::SingleSelection);


    //获取草稿箱的列表
    draftMail=db.draftMailSelected("hl");
       //设置草稿箱的表格
    modelDraft=new TableModelDraft(100,8,false,this,draftMail);
    ui->tableViewDraft->setModel(modelDraft);
    ui->tableViewDraft->resizeColumnsToContents();
    ui->tableViewDraft->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDraft->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewDraft->horizontalHeader()->setHighlightSections(false);
    ui->tableViewDraft->verticalHeader()->setVisible(false);
    ui->tableViewDraft->setShowGrid(false);
    ui->tableViewDraft->setFrameShape(QFrame::NoFrame);
    ui->tableViewDraft->setSelectionMode(QAbstractItemView::SingleSelection);


}

Widget::~Widget()
{
    delete ui;
}


//点击listWidget时改变stackWidget的页面内容
void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    int i=ui->listWidget->currentRow();
    //stack->setCurrentIndex(i);
    ui->stackedWidget->setCurrentIndex(i);
}

//窗口大小变化响应函数
void Widget::resizeEvent(QResizeEvent *event)
{
    //改变窗口大小时使listWIdget中的字的大小自适应
    ui->listWidget->setSpacing(ui->listWidget->width()/10);

    //窗口大小变化使改变重新初始化Model
//    TableModel* model=new TableModel(100,10,this);
//    ui->tableView->setModel(model);
//    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

//选择全选时改变状态
void Widget::on_checkBox_stateChanged(int arg1)
{
    for(int i=0;i<model->m_dataList.count();i++){
        QModelIndex indexNow =model->index(i, 0);
        if(ui->checkBox->isChecked()){
            model->setData(indexNow,Qt::Checked,Qt::CheckStateRole);
        }else{
            model->setData(indexNow,Qt::Unchecked,Qt::CheckStateRole);
        }

    }
//    ui->tableViewMail->setModel(model);

}

//选中邮件后的事件处理
void Widget::on_tableViewMail_doubleClicked(const QModelIndex &index)
{
    //选中邮件后，跳转到读邮件页面
    ui->stackedWidget->setCurrentIndex(6);
    //将邮件的具体信息传递过去


}

//新建群组
void Widget::on_pushButton_2_clicked()
{
    //弹出输入群组名的对话框
    bool ok;
    QString newGroupName=QInputDialog::getText(this,tr("新建组"),
                                               tr("组名:"),QLineEdit::Normal,
                                               QDir::home().dirName(),&ok);

    //将新建的群组名添加到listWidget中去
    if(ok&&!newGroupName.isEmpty()){
        QListWidgetItem *item=new QListWidgetItem();
        item->setText(newGroupName);
        item->setFont(QFont("Ubuntu", 15));
        item->setTextAlignment(Qt::AlignHCenter);
        ui->listWidgetBook->addItem(item);
        //将新建的群组名添加到数据库中
    }

}

//更新联系人tableModel的数据
void Widget::on_listWidgetBook_itemClicked(QListWidgetItem *item)
{
    //根据群组名查询数据库中该群组下的联系人
}

void Widget::on_tableViewAllBook_doubleClicked(const QModelIndex &index)
{
    //将该页面的收件人赋值为该联系人
      QMap<int,QVariant> i=modelBook->itemData(index);
      QString receiverName=i.find(0)->toString();

     ui->lineEditRecipient->setText(receiverName);

     //双击联系人列表转到给该联系人发邮件的页面
     ui->stackedWidget->setCurrentIndex(0);


}
//在通讯录中添加联系人
void Widget::on_addContactBtn_clicked()
{
    //获得当前群组名称
    QString nowGroupName=ui->listWidgetBook->currentItem()->text();
    //将该联系人在根据群组名存入数据库
    //新建TableModeBook的表格
    //参考登陆页面


}
//删除当前群组
void Widget::on_deleteGroupBtn_clicked()
{

    if(ui->listWidgetBook->currentItem()!=0x0){
        //获得当前群组名称
         QString nowGroupName=ui->listWidgetBook->currentItem()->text();
         QMessageBox msgBox;
          msgBox.setText("确定要删除"+nowGroupName+"群组并且删除该群组中的全部的联系人吗?");
          if(msgBox.exec()==QMessageBox::Yes){

              //删除该群组及其内的所有联系人
              //删除对应数据库中的数据
          }
    }else{
        //当前群组名为空弹出提示框
        QMessageBox msgBox;
         msgBox.setText("请选择要删除的群组");
         msgBox.exec();
    }

}

//在通讯录中删除联系人
/*void Widget::on_deleteContactBtn_clicked()
{
    //获得当前的tableModel的选中情况
    QMap<int,Qt::CheckState> modelMap=modelBook->rowCheckStateMap;
    QList<QString> deleteContacts;//被删除联系人姓名列表
    for(int i=0;i<modelMap.count();i++){
        if(modelMap.value(i)==Qt::Checked){
            deleteContacts.append(modelBook->m_dataList.at(i));//追加联系人用户名
            //在显示列表中删除这一项
            //在数据库中删除这一项
        }
    }

}*/

//彻底删除邮件
void Widget::on_deleteCompleteBtn_clicked()
{
    QMap<int,Qt::CheckState> modelMap=model->rowCheckStateMap;
    QList<int> deleteComMailId;//彻底删除邮件列表
    QList<Mail> dataList;//新生成的数据列表
    for(int i=0;i<model->rowCheckStateMap.count();i++){
        if(modelMap.value(i)==Qt::Checked){
            auto v = model->m_dataList.at(i);
            int j=v.getMailId();
            deleteComMailId.append(j);

        }
    }

    for(int i=0;i<model->m_dataList.count();i++){
        auto v = model->m_dataList.at(i);
        int j=v.getMailId();
        if(!deleteComMailId.contains(j)){
           dataList.append(model->m_dataList.at(i));
        }
    }

    //在数据库中删除这一项
    DataBase db;
    db.mailDelete(deleteComMailId);
    //在显示列表中删除这一项
    model=new TableModel(100,8,false,this,dataList);
   ui->tableView->setModel(model);


}

//不彻底删除邮件
void Widget::on_deleteCheckedBtn_clicked()
{
    QMap<int,Qt::CheckState> modelMap=model->rowCheckStateMap;
    QList<int> deleteComMails;//彻底删除邮件列表
    QList<Mail> deleteList;
    for(int i=0;i<model->rowCheckStateMap.count();i++){
        if(modelMap.value(i)==Qt::Checked){
            auto v = model->m_dataList.at(i);
            int j=v.getMailId();
            deleteComMails.append(j);
            //在显示列表中删除这一项
            //在数据库中将该项的删除标记改变
      }
    }
    for(int i=0;i<model->m_dataList.count();i++){
        auto v = model->m_dataList.at(i);
        int j=v.getMailId();
        if(!deleteComMails.contains(j)){
            deleteList.append(model->m_dataList.at(i));
        }
    }
    //在数据库中删除这一项
    DataBase db;
    db.mailRemove(deleteComMails);

    model=new TableModel(100,8,false,this,deleteList);
    ui->tableView->setModel(model);
}


//标记为全读
void Widget::on_markAllReadedBtn_clicked()
{

    QList<int> list;
    QList<Mail> dataList;
    for(int i=0;i<model->m_dataList.count();i++){
        list.append(i);
        dataList.append(model->m_dataList.at(i));
    }
    for(int i=0;i<model->m_dataList.count();i++){
        auto v = model->m_dataList.at(i);
        int j=v.getMailId();
        if(!list.contains(j)){
            dataList.append(model->m_dataList.at(i));
        }
    }

    //在数据库中改变每一项的读取状态
    DataBase db;
    db.mailReaded(list);
    //改变每一行显示的读取状态
    model=new TableModel(100,8,false,this,dataList);
    ui->tableView->setModel(model);
}

//删除草稿
void Widget::on_deleteDraft_clicked()
{
    QMap<int,Qt::CheckState> modelMap=modelDraft->rowCheckStateMap;
    QList<int> deleteComDraftMailId;//彻底删除草稿箱邮件列表
    QList<Mail> dataList;//新生成的数据列表
    for(int i=0;i<modelDraft->rowCheckStateMap.count();i++){
        if(modelMap.value(i)==Qt::Checked){
            auto v = modelDraft->m_dataList.at(i);
            int j=v.getMailId();
            deleteComDraftMailId.append(j);
        }
    }

    for(int i=0;i<modelDraft->m_dataList.count();i++){
        auto v = model->m_dataList.at(i);
        int j=v.getMailId();
        if(!deleteComDraftMailId.contains(j)){
           dataList.append(modelDraft->m_dataList.at(i));
        }
    }

    //在数据库中删除这一项
    DataBase db;
    db.mailDelete(deleteComDraftMailId);
    //在显示列表中删除这一项
    modelDraft=new TableModelDraft(100,8,false,this,dataList);
    ui->tableViewDraft->setModel(modelDraft);

}
//写邮箱发送按钮
void Widget::on_sendMailBtn_clicked()
{
    //获取发送的邮件信息
    QString senderName;
    QString receiverName;
    QString content;
    QString theme;
    senderName="hl";//将发件人改为当前用户的名字
    receiverName=ui->lineEditRecipient->text();
    theme=ui->lineEditTheme->text();
    content=ui->textEditContent->toPlainText();

    Mail *mail=new Mail(theme,content,senderName,receiverName);

    //将新建邮件存到数据库中
    DataBase db;
    if(db.mailCreate(mail)){
//        QMessageBox msgBox;
//         msgBox.setText("邮件发送成功");
//         msgBox.exec();
         QMessageBox::about(this,"提示","邮件发送成功");//提示用户邮件发送状态
    }else{
//        QMessageBox msgBox;
//         msgBox.setText("邮件发送失败");
//         msgBox.exec();
         QMessageBox::about(this,"提示","邮件发送失败");
    }
    //可以考虑跳转到已发送界面
}

//在写邮件时将邮件存为草稿
void Widget::on_saveDraftBtn_clicked()
{

    //获取草稿邮件信息
    QString senderName;
    QString receiverName;
    QString content;
    QString theme;
    senderName="hl";//将发件人改为当前用户的名字
    receiverName=ui->lineEditRecipient->text();
    theme=ui->lineEditTheme->text();
    content=ui->textEditContent->toPlainText();

    Mail *mail=new Mail(theme,content,senderName,receiverName);
    mail->setDraft(1);

    //将新建邮件存到数据库中
    DataBase db;
    if(db.mailCreate(mail)){

         QMessageBox::about(this,"提示","存为草稿成功");//提示用户邮件发送状态
    }else{

         QMessageBox::about(this,"提示","存为草稿失败");
    }

    //
}
