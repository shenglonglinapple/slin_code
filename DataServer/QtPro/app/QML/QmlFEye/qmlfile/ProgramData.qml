import QtQuick 2.0

Item
{
    id:id_qml_ProgamData

    //
    property int m_nDEF_LOG_INFO : 1;
    property int m_nDEF_LOG_DEBUG : 2;
    property int m_nDEF_LOG_WARNING : 3;
    property int m_nDEF_LOG_ERROR : 4;
    property int m_nDEF_LOG_TRACE : 5;
    //
    property int m_nLOGLevel : 5;



    function fun_log_trace(strlog)
    {
        if (id_qml_ProgamData.m_nLOGLevel >= id_qml_ProgamData.m_nDEF_LOG_TRACE)
        {
            console.log("[TRACE]", " ", strlog);
        }

    }

}//Item id_qml_ProgamData
