#ifndef __CLASS__SERVER_SETTING_DIALOG_H__
#define __CLASS__SERVER_SETTING_DIALOG_H__





#include <QtGui/QDialog>


QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE




class CClientLoginParam;

class CServerSettingDialog : public QDialog
{
    Q_OBJECT

public:
    CServerSettingDialog(QWidget *parent = 0);
	~CServerSettingDialog();

public:
	void setupUi();
	void translateLanguage();

public slots:
	void slotButtonOKlicked(bool checked);
	void slotButtonCancellicked(bool checked);

signals:
	/*
	class: CServerSettingDialog
	signals:
	void signalServerInfoChanged(CClientLoginParam* pClientLoginParam);
	fun send signals: slotButtonOKlicked()

	class: CClientLoginDialog
	public slots: 
	void slotServerInfoChanged(CClientLoginParam* pClientLoginParam);
	*/
	void signalServerInfoChanged(CClientLoginParam* pClientLoginParam);
private:
	void _CreateConnect();
private:
	QString m_str_LineEdit_IPAddress_Value;
	QString m_str_LineEdit_Port_Value;
private:
	CClientLoginParam* m_pClientLoginParam;
private:
	QLabel* m_pLabel_IPAddress;
	QLineEdit* m_pLineEdit_IPAddress;

	QLabel* m_pLabel_Port;
	QLineEdit* m_pLineEdit_Port;

	QPushButton* m_pPushButton_OK;
	QPushButton* m_pPushButton_Cancel;

};

//QT_END_NAMESPACE


#endif//__CLASS__SERVER_SETTING_DIALOG_H__
