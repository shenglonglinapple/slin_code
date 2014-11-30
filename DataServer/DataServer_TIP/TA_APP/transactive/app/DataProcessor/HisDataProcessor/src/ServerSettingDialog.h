#ifndef __CLASS__SERVER_SETTING_DIALOG_H__
#define __CLASS__SERVER_SETTING_DIALOG_H__


#include "CFDServerCommonData.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QtGui/QDialog>


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QImage>
#include <QtGui/QPixmap>


QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE
class CProcessorWorker;

class CServerSettingDialog : public QDialog
{
    Q_OBJECT

public:
    CServerSettingDialog(QWidget *parent = 0);
	~CServerSettingDialog();

public:
	void setupUi(QDialog* pDialog);
	void retranslateUi(QDialog *pDialog);

public slots:
	void slotButtonRunClicked(bool checked);
	void slotButtonCancelClicked(bool checked);
	void slotPrcessorDoWork();

signals:
	/*
	class: CServerSettingDialog
	signals:
	void signalPrcessorDoWork();
	fun send signals: slotButtonRunClicked()

	class: CServerSettingDialog
	public slots: 
	void slotPrcessorDoWork();
	*/
	void signalPrcessorDoWork();
private:
	void _CreateConnect();

private:
	CProcessorWorker* m_pProcessWorker;
private:
	std::string m_strValue_ConfigFileName;
	std::string m_strValue_HistoryDataDirectory;
	std::string m_strValue_SaveDataDirectoryBAR;
	std::string m_strValue_SaveDataDirectoryTIK;
	std::string m_strValue_DbType;
	std::string m_strValue_StartTime;
	std::string m_strValue_AutoRun;
	std::string m_strValue_AutoRunTime;/*1980-01-28 02:00:01*/


private:
	QFormLayout* m_pFormLayout;
	QHBoxLayout* m_pHBoxLayout_Buttons;

	QLabel* m_pLabel_HisData;
	QLineEdit* m_pLineEdit_HisData;

	QLabel* m_pLabel_SaveDataBar;
	QLineEdit* m_pLineEdit_SaveDataBar;

	QLabel* m_pLabel_SaveDataTik;
	QLineEdit* m_pLineEdit_SaveDataTik;

	QLabel* m_pLabel_DBType;
	QComboBox* m_pComboBox_DBType;

	QLabel* m_pLabel_StartTime;
	QLineEdit* m_pLineEdit_StartTime;

	QLabel* m_pLabel_AutoRun;
	QComboBox* m_pComboBox_AutoRun;

	QLabel* m_pLabel_AutoRunTime;
	QLineEdit* m_pLineEdit_AutoRunTime;//2014-01-28 02:00:01

	QPushButton* m_pPushButton_Run;
	QPushButton* m_pPushButton_Cancel;

};

QT_END_NAMESPACE


#endif//__CLASS__SERVER_SETTING_DIALOG_H__
