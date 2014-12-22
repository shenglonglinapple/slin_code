#ifndef __CLASS__PWD_LINE_EDIT_H__
#define __CLASS__PWD_LINE_EDIT_H__


#include <QtGui/QLineEdit>


class CPwdLineEdit : public QLineEdit
{
public:
	CPwdLineEdit(QWidget *parent);
	~CPwdLineEdit();
public:
	void keyPressEvent(QKeyEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

};



#endif//__CLASS__PWD_LINE_EDIT_H__
