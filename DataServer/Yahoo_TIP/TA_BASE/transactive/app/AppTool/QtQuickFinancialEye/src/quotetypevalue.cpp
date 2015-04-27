#include "quotetypevalue.h"

QuoteTypeValue::QuoteTypeValue(QObject *parent) :
    QObject(parent)
{
}

//static
void QuoteTypeValue::declareQML()
{
    qmlRegisterType<QuoteTypeValue>("QuoteTypeValue", 1, 0, "QuoteType");
}






