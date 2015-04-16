#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

typedef enum{
	UI_ZH,
	UI_EN
}LANGUAGE;

class SettingDialog : public QDialog
{
	Q_OBJECT

public:

	explicit SettingDialog(QWidget *parent = 0);
	~SettingDialog();
	void translateLanguage();
	void loadConfig();

signals:

	void switchLanguage(int index);

private:
	
	QLabel *language_label;
	QComboBox *language_combo_box;
	QLabel *info_label;
};

#endif //SETTING_DIALOG_H
