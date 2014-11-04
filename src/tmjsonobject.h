#ifndef TMJSONOBJECT_H
#define TMJSONOBJECT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

typedef struct type_IPCCMD_REQUEST
{
    uint ProviderType;
    uint MessageId;
} IPCCMD_REQUEST, * LPIPCCMD_REQUEST;

typedef struct type_IPCCMD_RESULT
{
    uint ProviderType;
    uint MessageId;
} IPCCMD_RESULT, *LPIPCCMD_RESULT;

// IPCST_IPCINFO (8 bytes)
// Abstract data type for IPC command (union of all IPCCMD_* types).
// Command type is as specified in GetCommandType()
typedef union type_IPCST_INFO
{
    IPCCMD_REQUEST Request;
    IPCCMD_RESULT Result;
} IPCST_IPCINFO, *LPIPCST_IPCINFO;

class TmJsonObject : public QObject, public QJsonObject
{
    Q_OBJECT
public:
    explicit TmJsonObject(QObject *parent = 0);

signals:

public slots:

};

#endif // TMJSONOBJECT_H
