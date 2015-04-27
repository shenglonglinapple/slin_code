import QtQuick 2.0

Rectangle
{
    id: id_qml_ChooseHistoryDataTypeWindow

    width: 256
    height: 16

    anchors.left: parent.left
    //anchors.leftMargin: 10
    anchors.top: parent.top
    //anchors.topMargin: 1

    color: "PowderBlue"

    //UI
    Row
    {//1行 Row布局了4个自定义的按钮
        id: m_Row_Buttons;

        anchors.fill: parent;
        //spacing: 0

        onWidthChanged:
        {// 该函数保证宽度变化时优先压缩spacing，且不会造成按钮重叠
            var buttonsLen = m_Buttom_1days.width + m_Buttom_5days.width + m_Buttom_30days.width
                    + m_Buttom_3months.width + m_Buttom_6months.width;
            var space = (width - buttonsLen) / 10;
            spacing = Math.max(space, 4);
        }

        //1day
        Button
        {
            id: m_Buttom_1days
            text: "1d"
            buttonEnabled: m_CurrentUserStockData.m_str_HistoryDataTimeCount === "1d"
            onClicked:
            {
                m_CurrentUserStockData.m_str_HistoryDataCycle = "d";
                m_CurrentUserStockData.m_n_HistoryDataTimeCount = 1;
                m_CurrentUserStockData.m_str_HistoryDataTimeCount = "1d";
                //update
                m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
            }
        }

        //5day
        Button
        {
            id: m_Buttom_5days
            text: "5d"
            buttonEnabled: m_CurrentUserStockData.m_str_HistoryDataTimeCount === "5d"
            onClicked:
            {
                m_CurrentUserStockData.m_str_HistoryDataCycle = "d";
                m_CurrentUserStockData.m_n_HistoryDataTimeCount = 5;
                m_CurrentUserStockData.m_str_HistoryDataTimeCount = "5d";
                //update
                m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
            }
        }


        //1m
        Button
        {
            id: m_Buttom_30days
            text: "1m"
            buttonEnabled: m_CurrentUserStockData.m_str_HistoryDataTimeCount === "1m"
            onClicked:
            {
                m_CurrentUserStockData.m_str_HistoryDataCycle = "m";
                m_CurrentUserStockData.m_n_HistoryDataTimeCount = 1;
                m_CurrentUserStockData.m_str_HistoryDataTimeCount = "1m";
                //update
                m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
            }
        }

        //3m
        Button
        {
            id: m_Buttom_3months
            text: "3m"
            buttonEnabled: m_CurrentUserStockData.m_str_HistoryDataTimeCount === "3m"
            onClicked:
            {
                m_CurrentUserStockData.m_str_HistoryDataCycle = "m";
                m_CurrentUserStockData.m_n_HistoryDataTimeCount = 3;
                m_CurrentUserStockData.m_str_HistoryDataTimeCount = "3m";
                //update
                m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
            }
        }

        //6m
        Button
        {
            id: m_Buttom_6months
            text: "6m"
            buttonEnabled: m_CurrentUserStockData.m_str_HistoryDataTimeCount === "6m"
            onClicked:
            {
                m_CurrentUserStockData.m_str_HistoryDataCycle = "m";
                m_CurrentUserStockData.m_n_HistoryDataTimeCount = 6;
                m_CurrentUserStockData.m_str_HistoryDataTimeCount = "6m";
                //update
                m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
            }
        }

        //Button

    }//Row

}//Rectangle


