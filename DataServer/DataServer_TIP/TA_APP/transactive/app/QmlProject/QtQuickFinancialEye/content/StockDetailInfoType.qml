import QtQuick 2.0

Rectangle
{
    id: id_qml_StockDetailInfoType

    width: 320
    height: 200

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.topMargin: 4

    //UI
    Row
    {//1行 Row布局了4个自定义的按钮
        id: m_Row_activeChartRow;

        anchors.fill: parent;
        spacing: 52

        onWidthChanged:
        {                    // 该函数保证宽度变化时优先压缩spacing，且不会造成按钮重叠
            var buttonsLen = m_Buttom_max.width + m_Button_year.width + m_Button_month.width + m_Button_week.width;
            var space = (width - buttonsLen) / 3;
            spacing = Math.max(space, 10);
        }

        Button
        {
            id: m_Buttom_max
            text: "Max"
            buttonEnabled: id_qml_StockPriceChart.activeChart === "max"
            onClicked:
            {
                id_qml_StockPriceChart.activeChart = "max";          // 改变当前图表显示模式，这里的max 实际对应update中的'else'，即2005年作为起始年
                id_qml_StockPriceChart.update();                     // 更新
            }
        }
        Button
        {
            id: m_Button_year
            text: "Year"
            buttonEnabled: id_qml_StockPriceChart.activeChart === "year"
            onClicked:
            {
                id_qml_StockPriceChart.activeChart = "year";
                id_qml_StockPriceChart.update();
            }
        }
        Button
        {
            id: m_Button_month
            text: "Month"
            buttonEnabled: id_qml_StockPriceChart.activeChart === "month"
            onClicked:
            {
                id_qml_StockPriceChart.activeChart = "month";
                id_qml_StockPriceChart.update();
            }
        }

        Button
        {
            id: m_Button_week
            text: "Week"
            buttonEnabled: id_qml_StockPriceChart.activeChart === "week"
            onClicked:
            {
                id_qml_StockPriceChart.activeChart = "week";
                id_qml_StockPriceChart.update();
            }
        }
    }//Row

}//Rectangle


