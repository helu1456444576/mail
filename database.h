#ifndef DATABASE_H
#define DATABASE_H
#include "mail.h"
#include <QList>

#include "qstring.h"

class DataBase
{
public:
    DataBase();
    //database connec
    bool connectDB();
    //user option

    //mail option
    bool mailCreate(Mail *mail);
    bool mailDraft(Mail mail);
    bool mailRemove(QList<int> mailidlist);
    bool mailDelete(QList<int> mailidlist);

    bool mailReaded(QList<int> mailidlist);
    bool mailStar(QList<int> mailidlist);
    QList<Mail> senderMailSelected(QString username);
    QList<Mail> deletedMailSelected(QString username);
    QList<Mail> receiverMailSelected(QString username);
    QList<Mail> draftMailSelected(QString username);

    Mail mailSelectedByMailid(int mailid);
    //Mail mailReedit(int mailid);
};

#endif // DATABASE_H
