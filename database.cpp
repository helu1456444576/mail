#include "database.h"
#include "QSqlDatabase"
#include "qstring.h"
#include "qdebug.h"
#include "QSqlQuery"
#include "QDateTime"


DataBase::DataBase()
{
}

bool DataBase::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("flowermail");
    db.setUserName("root");
    db.setPassword("123456");
    qDebug()<<"before open";
    bool ok = db.open();
    if(ok){
        qDebug()<<"success connect database";
        return true;
    }
    else{
        qDebug()<<"fail connect database";
        return false;
    }
}

//create new mail
bool DataBase::mailCreate(Mail *mail)
{
    QSqlQuery query;
    QString createline = QString("insert into mail(theme,content,sendername,receivername,deleted,star,draft,readed,time) values('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(mail->getTheme()).arg(mail->getContent()).arg(mail->getSenderName()).arg(mail->getReceiverName()).arg(mail->getDeleted()).arg(mail->getStar()).arg(mail->getDraft()).arg(mail->getReaded()).arg(mail->getTime());
    //console log the sql line
    qDebug()<<createline;
    if(!query.exec(createline))
        return false;
    else {
        return true;
    }
}

//create new draft
bool DataBase::mailDraft(Mail mail)
{
    //change the draft flag to 1
    mail.setDraft(1);
    QSqlQuery query;
    QString sqlline = QString("insert into mail(theme,content,sendername,receivername,deleted,star,draft,readed,time) values('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(mail.getTheme()).arg(mail.getContent()).arg(mail.getSenderName()).arg(mail.getReceiverName()).arg(mail.getDeleted()).arg(mail.getStar()).arg(mail.getDraft()).arg(mail.getReaded()).arg(mail.getTime());
    //console log the sql line
    qDebug()<<sqlline;
    if(!query.exec(sqlline))
        return false;
    else {
        return true;
    }
}

//remove the mail to trash
bool DataBase::mailRemove(QList<int> mailidlist)
{
    int mailNum = mailidlist.size();
    QSqlQuery query;
    for(int i = 0; i < mailNum; i++)
    {
        QString sqlline = QString("update mail set deleted = 1 where id = '%1'").arg(mailidlist[i]);
        if(!query.exec(sqlline))
            return false;
    }
    return true;
}

//delete the mail totally
bool DataBase::mailDelete(QList<int> mailidlist)
{
    int mailNum = mailidlist.size();
    QSqlQuery query;
    for(int i = 0; i < mailNum; i++)
    {
        QString sqlline = QString("delete from mail where id = '%1'").arg(mailidlist[i]);
        if(!query.exec(sqlline))
            return false;
    }
    return true;
}

//change the readedflag
bool DataBase::mailReaded(QList<int> mailidlist)
{
    int mailNum = mailidlist.size();
    QSqlQuery query;
    for(int i = 0; i < mailNum; i++)
    {
        QString sqlline = QString("update mail set readed = 1 where id = '%1'").arg(mailidlist[i]);
        qDebug()<<sqlline;
        if(!query.exec(sqlline))
            return false;
    }
    return true;
}

//signal the mail star
bool DataBase::mailStar(QList<int> mailidlist)
{
    int mailNum = mailidlist.size();
    QSqlQuery query;
    for(int i = 0; i < mailNum; i++)
    {
        QString sqlline = QString("update mail set star = 1 where id = '%1'").arg(mailidlist[i]);
        if(!query.exec(sqlline))
            return false;
    }
    return true;
}

//select user's whole sender mails(not include the drafts)
QList<Mail> DataBase::senderMailSelected(QString username)
{
    QList<Mail> mailList;
    QSqlQuery query;
    QString sqlline = QString("select *from mail where sendername = '%1' and draft = 0").arg(username);
    query.exec(sqlline);
    while (query.next()) {
        int mailid =query.value(0).toInt();
        QString theme = query.value(1).toString();
        QString content = query.value(2).toString();
        QString sendername = query.value(3).toString();
        QString receivername = query.value(4).toString();
        int deleted = query.value(5).toInt();
        int star = query.value(6).toInt();
        int draft = query.value(7).toInt();
        int readed = query.value(8).toInt();
        QString time = query.value(9).toString();

        Mail tmpMail(mailid,theme,content,sendername,receivername,deleted,star,draft,readed,time);
        mailList.append(tmpMail);
    }
    return mailList;
}

//select user's deleted mails
QList<Mail> DataBase::deletedMailSelected(QString username)
{
    QList<Mail> mailList;
    QSqlQuery query;
    QString sqlline = QString("select *from mail where receivername = '%1' and deleted = 1").arg(username);
    query.exec(sqlline);
    while (query.next()) {
        int mailid =query.value(0).toInt();
        QString theme = query.value(1).toString();
        QString content = query.value(2).toString();
        QString sendername = query.value(3).toString();
        QString receivername = query.value(4).toString();
        int deleted = query.value(5).toInt();
        int star = query.value(6).toInt();
        int draft = query.value(7).toInt();
        int readed = query.value(8).toInt();
        QString time = query.value(9).toString();

        Mail tmpMail(mailid,theme,content,sendername,receivername,deleted,star,draft,readed,time);
        mailList.append(tmpMail);
    }
    return mailList;
}

//select user's received mails(deleted = 0)
QList<Mail> DataBase::receiverMailSelected(QString username)
{
    QList<Mail> mailList;
    QSqlQuery query;
    QString sqlline = QString("select *from mail where receivername = '%1' and deleted = 0").arg(username);
    query.exec(sqlline);
    while (query.next()) {
        int mailid =query.value(0).toInt();
        QString theme = query.value(1).toString();
        QString content = query.value(2).toString();
        QString sendername = query.value(3).toString();
        QString receivername = query.value(4).toString();
        int deleted = query.value(5).toInt();
        int star = query.value(6).toInt();
        int draft = query.value(7).toInt();
        int readed = query.value(8).toInt();
        QString time = query.value(9).toString();

        Mail tmpMail(mailid,theme,content,sendername,receivername,deleted,star,draft,readed,time);
        mailList.append(tmpMail);
    }
    return mailList;
}

//select user's draft mails
QList<Mail> DataBase::draftMailSelected(QString username)
{
    QList<Mail> mailList;
    QSqlQuery query;
    QString sqlline = QString("select *from mail where sendername = '%1' and draft = 1").arg(username);
    query.exec(sqlline);
    while (query.next()) {
        int mailid =query.value(0).toInt();
        QString theme = query.value(1).toString();
        QString content = query.value(2).toString();
        QString sendername = query.value(3).toString();
        QString receivername = query.value(4).toString();
        int deleted = query.value(5).toInt();
        int star = query.value(6).toInt();
        int draft = query.value(7).toInt();
        int readed = query.value(8).toInt();
        QString time = query.value(9).toString();

        Mail tmpMail(mailid,theme,content,sendername,receivername,deleted,star,draft,readed,time);
        mailList.append(tmpMail);
    }
    return mailList;
}

//select the mail by itsid
Mail DataBase::mailSelectedByMailid(int mailid)
{
    QSqlQuery query;
    QString sqlline = QString("select *from mail where mailid = '%1'").arg(mailid);
    query.next();
    Mail tmpMail(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toString(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toInt(),query.value(9).toString());
    return tmpMail;
}

//return the draft mail(for reedit)
//Mail DataBase::mailReedit(int mailid)
//{
//    QSqlQuery query;
//    QString sqlline = QString("select *from mail where mailid = '%1'").arg(mailid);
//    query.next();
//    Mail tmpMail(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toString(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toInt(),query.value(9).toString());
//    return tmpMail;
//}
