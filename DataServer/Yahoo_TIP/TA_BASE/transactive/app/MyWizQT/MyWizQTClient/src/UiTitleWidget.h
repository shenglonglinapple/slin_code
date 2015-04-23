#ifndef __CLASS__UI_TITLE_WIDGET_H__
#define __CLASS__UI_TITLE_WIDGET_H__

#include <QtCore/QString>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE
class QToolButton;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
class QToolButton;
class QPoint;
class QRect;
QT_END_NAMESPACE



class CUiTitleWidget : public QWidget
{
	Q_OBJECT;
public:
	explicit CUiTitleWidget(QWidget* pAffectedWidget, QWidget* parent = 0);
private slots:
	void onCloseClicked();
	void onMinSizeClicked();
	void onMaxSizeClicked();

public:
	void setCanResize( bool bValue );
	void setTitle(const QString& strValue);
private:
	void _SetStyleSheet();
	void _SetAttribute();
private:
	QToolButton* m_minsize;
	QToolButton* m_maxsize;
	QToolButton* m_close;
	QLabel* m_titleLabel;
	QString m_maxSheet;
	QString m_restoreStyleSheet;
private:
	QWidget* m_pAffectedWidget;
	QString m_strTitle;
};

#endif // __CLASS__UI_TITLE_WIDGET_H__
