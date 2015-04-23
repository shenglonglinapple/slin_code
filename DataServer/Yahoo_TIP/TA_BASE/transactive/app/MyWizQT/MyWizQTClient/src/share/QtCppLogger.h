#ifndef __CLASS_QT_CPP_LOGGER_HH__
#define __CLASS_QT_CPP_LOGGER_HH__

#include <QtCore/QtGlobal>
#include <QtCore/QObject>
#include <QtCore/QMutex>

class QBuffer;


class QtCppLogger : public QObject
{
    Q_OBJECT

protected:
    QtCppLogger();
    ~QtCppLogger();
public:

#if QT_VERSION < 0x050000
    static void messageHandler(QtMsgType type, const char* msg);
#else
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif
    static void writeLog(const QString& strMsg);
    static void getAllLogs(QString& text);
    static QtCppLogger* logger();
private Q_SLOTS:
    void onBuffer_readRead() { emit readyRead(); }
Q_SIGNALS:
    void readyRead();

private:
    QMutex m_mutex;
    QBuffer* m_buffer;

    void getAll(QString& text);

    QString logFileName();
    QString msg2LogMsg(const QString& strMsg);
    void saveToLogFile(const QString& strMsg);
    void addToBuffer(const QString& strMsg);
private:
	qint64 WizGetFileSize(const QString& strFileName);
	void WizDeleteFile(const QString& strFileName);
	QString WizExtractFilePath(const QString& strFileName);
	QString WizExtractFileName(const QString& strFileName);
};



#endif // __CLASS_QT_CPP_LOGGER_HH__
