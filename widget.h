#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QResizeEvent>
#include <QSize>
#include <QIcon>
#include <QListWidgetItem>
#include "tablemodel.h"
#include "tablemodelbook.h"
#include "mail.h"
#include "user.h"
#include "database.h"
#include "tablemodeldraft.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_listWidget_clicked(const QModelIndex &index);


    void on_checkBox_stateChanged(int arg1);


    void on_tableViewMail_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_listWidgetBook_itemClicked(QListWidgetItem *item);

    void on_tableViewAllBook_doubleClicked(const QModelIndex &index);

    void on_addContactBtn_clicked();

    void on_deleteGroupBtn_clicked();

 //   void on_deleteContactBtn_clicked();

   void on_deleteCompleteBtn_clicked();

    void on_deleteCheckedBtn_clicked();

    void on_markAllReadedBtn_clicked();

    void on_deleteDraft_clicked();

    void on_sendMailBtn_clicked();

    void on_saveDraftBtn_clicked();

private:
    Ui::Widget *ui;
    // QWidget interface


    // QWidget interface


    // QWidget interface


    // QWidget interface
   TableModel* model;
   TableModelBook *modelBook;
   TableModelDraft *modelDraft;
   User *nowUser;
   QList<Mail> receiverMails;
   QList<Mail> draftMail;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // WIDGET_H
