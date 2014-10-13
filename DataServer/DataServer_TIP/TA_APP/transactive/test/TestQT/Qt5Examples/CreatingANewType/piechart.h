/*
 * 在C++中我们通常将用户的交互与处理函数用信号槽绑定起来，
 * 比如窗口尺寸的变化，颜色的变化等，
 * 但在QML中，我们更多的使用属性绑定来完成这些功能。
 * 我们可以将这个属性值绑定到另一个对象或者本身的属性值上，
 * 这样当后者改变时，前者也能够跟着发生改变
 * ，而不需要我们在一个专门的onXXX()函数中进行这样的处理。
*/

#ifndef PIECHART_H
#define PIECHART_H

//![0]
#include <QtQuick/QQuickPaintedItem>
#include <QColor>


// 为了基于QPainter API实现自定义的绘制效果，我们需要继承这个类。
//如果不需要使用QPainter API，我们可以继承QQuickItem，
//甚至如果连可视化也不需要，QObject以及它的子类都可以作为我们继承的对象
class PieChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    //Q_PROPERTY(QColor color READ getColor WRITE setColor)

    // 我们为Q_PROPERTY添加了NOTIFY特性
    // 告诉编译器该属性值发生变化时"colorChanged"信号将被发出
    // 这样我们不再需要特别为该信号写onColorChanged()处理函数
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY signalColorChanged)
public:
    // 使用Q_INVOKABLE宏将该函数注册到Qt的元系统中，这样QML才能对它进行处理
     Q_INVOKABLE void clearChart();
public:
    // 因为需要使用到Qt的元对象系统
    // 注册两个自定义属性
    // 作为可视化组件我们需要将其父对象设置为QQuickItem
    PieChart(QQuickItem *parent = 0);

     // 定义属性的读写函数
    QString getName() const;
    void setName(const QString &name);

    QColor getColor() const;
    void setColor(const QColor &color);

    // 最后我们重载QQuickPaintedItem的paint函数，实现我们的自定义绘图
    void paint(QPainter *painter);

signals:
    void signalChartCleared();       // 接着像通常一样定义了一个信号
    void signalColorChanged();
private:
    QString m_name;
    QColor m_color;
};
//![0]

#endif

