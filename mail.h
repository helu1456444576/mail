#ifndef MAIL_H
#define MAIL_H
#include "QDateTime"
#include <QString>

class Mail
{
public:
    Mail();
    Mail(QString mailtheme,QString content,QString sendername,QString receivername);
    Mail(int mailid,QString theme,QString content,QString sendername,QString receivername,int deleted,int star,int draft,int readed,QString time);

    //get method
    QString getTheme();
    QString getContent();
    QString getSenderName();
    QString getReceiverName();
    int getDeleted();
    int getStar();
    int getDraft();
    int getReaded();
    QString getTime();
    int getMailId();

    //set method
    void setDeleted(int flag);
    void setStar(int flag);
    void setDraft(int flag);
    void setReaded(int flah);

private:
    int mailid;
    QString theme;
    QString content;
    QString sendername;
    QString receivername;
    int deleted;
    int star;
    int draft;
    int readed;
    QString time;
};

#endif // MAIL_H
