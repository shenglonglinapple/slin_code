#include "main_widget.h"
#include "util.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setMinimumSize(400, 300);

	welcome_label = new QLabel();
	setting_button = new QPushButton();
	ok_button = new QPushButton();
	cancel_button = new QPushButton();
	setting_dialog = new SettingDialog();

	QHBoxLayout *botton_layout = new QHBoxLayout();
	botton_layout->addStretch();
	botton_layout->addWidget(setting_button);
	botton_layout->addWidget(ok_button);
	botton_layout->addWidget(cancel_button);
	botton_layout->setSpacing(10);
	botton_layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addWidget(welcome_label, 0, Qt::AlignCenter);
	main_layout->addLayout(botton_layout);
	main_layout->setSpacing(10);
	main_layout->setContentsMargins(10, 10, 10, 10);

	this->setLayout(main_layout);
	this->translateLanguage();



	QObject::connect(setting_button, SIGNAL(clicked()), this, SLOT(showSetting()));
	QObject::connect(setting_dialog, SIGNAL(switchLanguage(int)), this, SLOT(switchLanguage(int)));
	//QObject::connect(setting_button, &QPushButton::clicked, this, &MainWidget::showSetting);
	//connect(setting_dialog, &SettingDialog::switchLanguage, this, &MainWidget::switchLanguage);
}

MainWidget::~MainWidget()
{

}

void MainWidget::translateLanguage()
{
	this->setWindowTitle(tr("main widget"));
	welcome_label->setText(tr("welcome to Qt") + QString("26197884"));
	setting_button->setText(tr("setting"));
	ok_button->setText(tr("ok"));
	cancel_button->setText(tr("cancel"));
}

void MainWidget::setLanguage(LANGUAGE current_language)
{
	this->current_language = current_language;
}

void MainWidget::setTranslator(QTranslator* translator)
{
	this->translator = translator;
}

void MainWidget::switchLanguage(int index)
{
	LANGUAGE language;
	QString language_qm;
	switch(index)
	{
	case UI_ZH:
		language = UI_ZH;
		language_qm = QString(":/qm/main_widget_zh");
		break;

	case UI_EN:
		language = UI_EN;
		language_qm = QString(":/qm/main_widget_en");
		break;

	default:
		language = UI_ZH;
		language_qm = QString(":/qm/main_widget_zh");
	}

	if(current_language != language)
	{
		current_language = language;

		translator->load(language_qm);
		setting_dialog->translateLanguage();
		this->translateLanguage();

		Util::writeInit(QString("./user.ini"), QString("language"), QString::number(language, 10));
	}
}

void MainWidget::showSetting()
{
	setting_dialog->loadConfig();
	setting_dialog->exec();
}