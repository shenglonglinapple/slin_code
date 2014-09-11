#include "PwdLineEdit.h"
/*
友好地提示用户，且不可复制、粘贴，实现密码的有力保护！
在做用户登录界面的时候，往往会用到密码框，则其中的一些功能也要求与普通的输入框不同，包括不能全选、复制、粘贴、无右键菜单等、设置密码不可见等功能
*/


CPwdLineEdit::CPwdLineEdit(QWidget *parent) :
QLineEdit(parent)
{
	//设置无右键菜单
	this->setContextMenuPolicy(Qt::NoContextMenu);
	//设置密码提示
	this->setPlaceholderText(QString("PassWord"));
	//设置密码隐藏
	this->setEchoMode(QLineEdit::Password);
	//设置密码框样式
	this->setStyleSheet("QLineEdit{border-width: 1px; border-radius: 4px; font-size:12px; color: black; border:1px solid gray;}"
		"QLineEdit:hover{border-width: 1px; border-radius: 4px; font-size:12px; color: black; border:1px solid rgb(70, 200, 50);}");
	//设置最大长度16位
	this->setMaxLength(16);
}

CPwdLineEdit::~CPwdLineEdit()
{

}

//屏蔽输入框全选、复制、粘贴功能
void CPwdLineEdit::keyPressEvent(QKeyEvent *event)
{
	if(event->matches(QKeySequence::SelectAll))
	{   
		return ;   
	}
	else if(event->matches(QKeySequence::Copy))
	{   
		return ;   
	}
	else if(event->matches(QKeySequence::Paste))
	{   
		return ;   
	}
	else
	{
		QLineEdit::keyPressEvent(event);
	}
} 


//主要设置鼠标位于密码框中时不可移动
void CPwdLineEdit::mouseMoveEvent(QMouseEvent *event)
{
	return ;
}