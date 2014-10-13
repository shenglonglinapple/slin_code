
#ifndef PERSON_H
#define PERSON_H

#include <QObject>
// ![0]
// 要注意的是由于这个对象并不需要可视化，我们继承最基础的QObject就可以了
class Person : public QObject
{
     // 因为QML组件基于元对象系统，所以QObject和Q_OBJECT都不能少
    Q_OBJECT
    // 两个自定义属性
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(int shoeSize READ shoeSize WRITE setShoeSize)
public:
    Person(QObject *parent = 0);

    QString name() const;
    void setName(const QString &);

    int shoeSize() const;
    void setShoeSize(int);

private:
    QString m_name;
    int m_shoeSize;
};
// ![0]

#endif // PERSON_H
