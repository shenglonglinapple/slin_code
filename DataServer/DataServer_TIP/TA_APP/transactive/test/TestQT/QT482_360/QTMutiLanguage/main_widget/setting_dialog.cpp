#include "setting_dialog.h"
#include "util.h"

SettingDialog::SettingDialog(QWidget *parent)
	: QDialog(parent)
{
	this->setMinimumSize(300, 200);
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

	language_label = new QLabel();
	language_combo_box = new QComboBox();
	info_label = new QLabel();

	language_combo_box->addItem("chinese", UI_ZH);
	language_combo_box->addItem("english", UI_EN);

	QHBoxLayout *language_layout = new QHBoxLayout();
	language_layout->addStretch();
	language_layout->addWidget(language_label);
	language_layout->addWidget(language_combo_box);
	language_layout->addStretch();
	language_layout->setSpacing(5);
	language_layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addWidget(info_label, 0, Qt::AlignCenter);
	main_layout->addLayout(language_layout);
	main_layout->setSpacing(10);
	main_layout->setContentsMargins(10, 10, 10, 10);

	this->setLayout(main_layout);
	this->translateLanguage();

	//connect(language_combo_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SettingDialog::switchLanguage);
}

SettingDialog::~SettingDialog()
{

}

void SettingDialog::translateLanguage()
{
	this->setWindowTitle(tr("setting dialog"));
	info_label->setText(tr("no brothers no programming"));
	language_label->setText(tr("language"));
	language_combo_box->setItemText(UI_ZH, tr("chinese"));
	language_combo_box->setItemText(UI_EN, tr("english"));
}

void SettingDialog::loadConfig()
{
	QString language_value;
	QString language_suffix = QString("zh");
	LANGUAGE language = UI_ZH;
	bool is_read = Util::readInit(QString("./user.ini"), QString("language"), language_value);
	if(is_read)
	{
		language = (LANGUAGE)language_value.toInt();
		if(language == UI_EN)
		{
			language_suffix = QString("en");
		}
	}

	int count = language_combo_box->count();
    for(int i=0; i <count; i++)
	{
        if(language == i)
		{
            language_combo_box->setCurrentIndex(language);
            break;
        }
    }
}