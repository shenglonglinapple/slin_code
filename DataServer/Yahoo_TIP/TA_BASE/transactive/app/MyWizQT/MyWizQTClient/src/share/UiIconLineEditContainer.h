#ifndef __CLASS_UI_LINE_EDIT_CONTAINER_HH__
#define __CLASS_UI_LINE_EDIT_CONTAINER_HH__

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

class CUiSkin9GridImage;
class CUiIconLineEditContainer : public QWidget
{
	Q_OBJECT
public:
	CUiIconLineEditContainer(QWidget* parent = 0);
	~CUiIconLineEditContainer();
private:
	CUiSkin9GridImage* m_background;
	QLayout* m_layout;
	QLineEdit* m_edit;
	QLabel* m_leftIcon;
	QLabel* m_rightIcon;

signals:
	void rightIconClicked();
private slots:
	void cleanRightIcon();
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent* event);

public:
	void setBackgroundImage(QString fileName, QPoint pt);
	void setLeftIcon(QString fileName);
	void setRightIcon(QString fileName);
	void setPlaceholderText(const QString& strText);
	void setAutoClearRightIcon(bool bAutoClean);
	//
	QLineEdit* edit() const { return m_edit; }

};

#endif // __CLASS_UI_LINE_EDIT_CONTAINER_HH__
