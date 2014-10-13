/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
//![0]
#include "piechart.h"
#include <QtQuick/QQuickView>
#include <QGuiApplication>


#include <QCoreApplication>           // 注意到Chapter中为QGuiApplication
#include <QQmlEngine>                 // 提供QML组件的运行环境
#include <QQmlComponent>              // 提供对QML组件的封装与访问
#include <QDebug>
#include "person.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 我们使用模板函数注册了这个类型，
    //"Charts"为import的命名空间，PieChart为类型名，1,0即是版本号1.0。
    qmlRegisterType<PieChart>("Charts", 1, 0, "PieChart");

    // 然后创建一个QQuickView来显示QML组件
    QQuickView view;
    // 窗口大小设置为根目录大小
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    // 调用资源中的app.qml
    view.setSource(QUrl("qrc:///app.qml"));
    view.show();

    ////
    qmlRegisterType<Person>("People", 1,0, "Person");            // 注册QML类型


    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl("qrc:example.qml"));    // 获取QML文件中的组件
    Person *person = qobject_cast<Person *>(component.create());  // 创建该组件的实例化对象
    if (person)
    {
        qWarning() << "The person's name is" << person->name();   // 依然是通过->访问其成员函数
        qWarning() << "They wear a" << person->shoeSize() << "sized shoe";
    }
    else
    {
        qWarning() << component.errors();             // 类型转换失败则输出错误信息
    }


    return app.exec();
}
//![0]

