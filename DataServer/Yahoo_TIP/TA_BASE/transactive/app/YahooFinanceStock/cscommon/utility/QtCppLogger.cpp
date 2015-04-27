#include "QtCppLogger.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtCore/QBuffer>
#include <QtCore/QTextStream>



#define LOG_LINES_MAX 30000
#define LOG_DAYS_MAX 10
#define LOG_LINES_BUFFER_MAX 3000


QtCppLogger::QtCppLogger()
    : m_buffer(new QBuffer())
    , m_mutex(QMutex::Recursive)
{
}

QtCppLogger::~QtCppLogger()
{
}


#if QT_VERSION < 0x050000
void QtCppLogger::messageHandler(QtMsgType type, const char* msg)
{
    QString text = QString::fromUtf8(msg);
    logger()->saveToLogFile(text);
    logger()->addToBuffer(text);

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[DEBUG] %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "[WARNING]: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[CRITICAL]: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[FATAL]: %s\n", msg);
        abort();
    }
}
#else
void QtCppLogger::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    Q_UNUSED(context);

    logger()->saveToLogFile(msg);
    logger()->addToBuffer(msg);

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[DEBUG] %s\n", msg.toUtf8().constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "[WARNING]: %s\n", msg.toUtf8().constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[CRITICAL]: %s\n", msg.toUtf8().constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "[FATAL]: %s\n", msg.toUtf8().constData());
        abort();
    }
}
#endif
//////////////////////////
qint64 QtCppLogger::WizGetFileSize(const QString& strFileName)
{
	QFileInfo info(strFileName);
	return info.size();
}
void QtCppLogger::WizDeleteFile(const QString& strFileName)
{
	QDir dir(WizExtractFilePath(strFileName));
	dir.remove(WizExtractFileName(strFileName));
}
QString QtCppLogger::WizExtractFilePath(const QString& strFileName)
{
	QString str = strFileName;
	str.replace('\\', '/');
	int index = str.lastIndexOf('/');
	if (-1 == index)
	{
		return strFileName;
	}
	//
	return str.left(index + 1); //include separator
}
QString QtCppLogger::WizExtractFileName(const QString& strFileName)
{
	QString str = strFileName;
	str.replace('\\', '/');
	int index = str.lastIndexOf('/');
	if (-1 == index)
		return strFileName;

	return strFileName.right(str.length() - index - 1);
}

//////////////////////////
QString QtCppLogger::logFileName()
{
    QString strFileName = "./log_logfile.log";

    if (WizGetFileSize(strFileName) > 10 * 1024 * 1024)
    {
        WizDeleteFile(strFileName);
    }
    //
    return strFileName;
}

QString QtCppLogger::msg2LogMsg(const QString& strMsg)
{
    QString strTime = QDateTime::currentDateTime().toString(Qt::ISODate);
    return strTime + ": " + strMsg + "\n";
}

void QtCppLogger::saveToLogFile(const QString& strMsg)
{
    QFile f(logFileName());
    f.open(QIODevice::Append | QIODevice::Text);
    f.write(msg2LogMsg(strMsg).toUtf8());
    f.close();
}

void QtCppLogger::addToBuffer(const QString& strMsg)
{
    QMutexLocker locker(&m_mutex);
    Q_UNUSED(locker);
    //
    m_buffer->open(QIODevice::Append);
    m_buffer->write(msg2LogMsg(strMsg).toUtf8());
    m_buffer->close();
}

void QtCppLogger::getAll(QString &text)
{
    QMutexLocker locker(&m_mutex);
    Q_UNUSED(locker);
    //
    m_buffer->open(QIODevice::ReadOnly);
    QByteArray data = m_buffer->readAll();
    text = QString::fromUtf8(data.data());
    m_buffer->close();
    m_buffer->setBuffer(NULL);
}

QtCppLogger* QtCppLogger::logger()
{
    static QtCppLogger logger;
    return &logger;
}

void QtCppLogger::writeLog(const QString& strMsg)
{
    qDebug() << strMsg;
}
void QtCppLogger::getAllLogs(QString& text)
{
    logger()->getAll(text);
}

/*how to use
int main(int argc, char *argv[])
{
int ret = 0;
//===============
#if QT_VERSION > 0x050000
qInstallMessageHandler(Utils::Logger::messageHandler);
QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#else
qInstallMsgHandler(Utils::Logger::messageHandler);
#endif
//===============
qDebug()<<"Test Log"<<"ret="<<ret;
}
*/