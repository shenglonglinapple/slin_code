#ifndef __CLASS__CLIENT_LOGIN_WINDOW_H__
#define __CLASS__CLIENT_LOGIN_WINDOW_H__


#include <QtCore/QString>

#include <QtGui/QMainWindow>
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



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CClientLoginParam;
class CLoginSettingWindow;
class CPwdLineEdit;

class CClientLoginWindow : public QDialog
{
    Q_OBJECT

public:
    CClientLoginWindow(QWidget *parent = 0);
	~CClientLoginWindow();
public slots:
	void slotButtonSettingClicked(bool checked);
	void slotButtonLoginClicked(bool checked);
	void slotButtonCancelClicked( bool checked );
signals:
	void signalLoginToServerRes(int nLoginToServerRes);
public slots:
	void slotServerInfoChanged(std::string strServerIP, int nServerPort);
private:
	void _CreateConnect();
	void _SetupUi();
	void _TranslateLanguage();


private:
	QString m_pComboBox_UserName_Value;
	QString m_pLineEdit_Password_Value;
private:
	CLoginSettingWindow* m_pLoginSettingWindow;
private:
	CClientLoginParam* m_pClientLoginParam;
private:
	QLabel* m_pLabel_UserName;
	QComboBox* m_pComboBox_UserName;

	QLabel* m_pLabel_Password;
	CPwdLineEdit* m_pLineEdit_Password;

	QPushButton* m_pPushButtonSetting;
	QPushButton* m_pPushButtonLogin;
	QPushButton* m_pPushButtonCancle;
};

//QT_END_NAMESPACE


#endif//__CLASS__CLIENT_LOGIN_WINDOW_H__
