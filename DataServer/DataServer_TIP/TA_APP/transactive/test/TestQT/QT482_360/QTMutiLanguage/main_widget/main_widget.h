#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTranslator>
#include "setting_dialog.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:

	explicit MainWidget(QWidget *parent = 0);
	~MainWidget();
	void setLanguage(LANGUAGE current_language);
	void translateLanguage();
	void setTranslator(QTranslator* translator);

private slots:

	void showSetting();
	void switchLanguage(int index);

private:
	
	QLabel *welcome_label;
	QPushButton *setting_button;
	QPushButton *ok_button;
	QPushButton *cancel_button;

	SettingDialog *setting_dialog;
	LANGUAGE current_language;
	QTranslator *translator;
};

#endif //MAIN_WIDGET_H
