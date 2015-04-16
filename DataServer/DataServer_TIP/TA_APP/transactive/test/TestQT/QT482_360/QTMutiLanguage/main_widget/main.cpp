#include "main_widget.h"
#include <QTranslator>
#include <QApplication>
#include "util.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

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

	QTranslator translator;  
	translator.load(QString(":/qm/main_widget_") + language_suffix);  
	app.installTranslator(&translator); 

	MainWidget main_widget;
	main_widget.setTranslator(&translator);
	main_widget.setLanguage(language);
	main_widget.show();
	return app.exec();
}
