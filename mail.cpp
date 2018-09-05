#include "mail.h"

Mail::Mail()
{
}

Mail::Mail(QString mailtheme, QString content, QString sendername, QString receivername)
{
    //get the time
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    this->theme = mailtheme;
    this->content = content;
    this->sendername = sendername;
    this->receivername = receivername;
    //default value
    this->deleted = 0;
    this->star = 0;
    this->draft = 0;
    this->readed = 0;
    this->time = current_date;
}

Mail::Mail(int mailid, QString theme, QString content, QString sendername, QString receivername, int deleted, int star, int draft, int readed,QString time)
{
    this->mailid = mailid;
    this->theme = theme;
    this->content = content;
    this->sendername = sendername;
    this->receivername = receivername;
    this->deleted = deleted;
    this->star = star;
    this->draft = draft;
    this->readed = readed;
    this->time = time;
}

QString Mail::getTheme()
{
    return theme;
}

QString Mail::getContent()
{
    return content;
}

QString Mail::getSenderName()
{
    return sendername;
}

QString Mail::getReceiverName()
{
    return receivername;
}

int Mail::getDeleted()
{
    return deleted;
}

int Mail::getStar()
{
    return star;
}

int Mail::getDraft()
{
    return draft;
}

int Mail::getReaded()
{
    return readed;
}

QString Mail::getTime()
{
    return time;
}
int Mail::getMailId()
{
    return mailid;
}
//get methods
void Mail::setDeleted(int flag)
{
    this->deleted = flag;
}

void Mail::setStar(int flag)
{
    this->star = flag;
}

void Mail::setDraft(int flag)
{
    this->draft = flag;
}

void Mail::setReaded(int flag)
{
    this->readed = flag;
}
