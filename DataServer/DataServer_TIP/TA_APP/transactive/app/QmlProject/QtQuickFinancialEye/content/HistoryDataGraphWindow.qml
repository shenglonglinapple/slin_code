import QtQuick 2.0

Rectangle
{
    id: id_qml_HistoryDataGraphWindow;
    width: 320
    height: 200

    // 作为Item的派生类型，我们同样可以设置它的布局与属性
    //anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    //anchors.bottom: parent.bottom;
    //color: "#FEFEFE"
    color:"LightYellow"


    //data
    ListModel
    {
        id:m_ListModel_PointArray
        //

        /*
                m_ListModel_PointArray.push({m_n_HGridValue: (nIndexY * m_canvas.m_n_H_OneDataStep),
                                m_str_open: varListElement.m_str_open,
                                m_str_close: varListElement.m_str_close,
                                m_str_high: varListElement.m_str_high,
                                m_str_low: varListElement.m_str_low,
                                m_str_volume: varListElement.m_str_volume});
        */
        //property variant m_Array_Points : [];//JSON.stringify(m_Array_Points) m_Array_Points.length
        property int m_Array_PointsCount: 0;// 存储数据点的个数
        property real m_n_HighestPrice : 0;//y
        property real m_n_LowestPrice : 0;//y
        property real m_n_HighestVolume : 0;
        property real m_n_LowestVolume : 0;

        property real m_yaxis_minmax_range : 0;//y
        property real m_volume_yaxis_minmax_range : 0;//y

        property real m_xaxis_min_value: 0.0;//time stamp seconds since 1970.1.1
        property real m_xaxis_max_value: 0.0;//time stamp seconds since 1970.1.1
        property real m_xaxis_minmax_range: 0.0;//time stamp seconds since

        property real  nMillSecondsInOneDay : (60 * 60 * 24 * 1000);
    }

    function fun_update()
    {
        //当更新时需要调用画布的这个函数
        m_canvas.requestPaint();
    }



    //m_CurrentUserStockData  ListModel
    //计算每个点的x坐标
    function fun_process_data()
    {
        console.log("HistoryDataGraphWindow.qml",
                    " ","fun_process_data");

        m_ListModel_PointArray.clear();
        m_ListModel_PointArray.m_Array_PointsCount = 0;
        m_ListModel_PointArray.m_n_HighestPrice = 0;
        m_ListModel_PointArray.m_n_LowestPrice = 0;
        m_ListModel_PointArray.m_n_HighestVolume = 0;
        m_ListModel_PointArray.m_n_LowestVolume = 0;


        var nIndexX = 0;
        var nDataIndex = 0;
        var varListElement;

        var strTimePos = "yyyy-MM-dd hh:mm:ss";
        var nTimePos = new Date();
        var nWidthPos = 0;
        var nMilSecondsSinceUTCPos = 0;
        /*
          The Qt.locale() function returns a JS Locale object representing the locale with the specified name,
            which has the format "language[_territory][.codeset][@modifier]" or "C".
        */
        var locale = Qt.locale("de_DE");
        //var locale = Qt.locale();

        //init first data
        m_ListModel_PointArray.m_Array_PointsCount = m_CurrentUserStockData.count;
        if (m_ListModel_PointArray.m_Array_PointsCount > 0)
        {
            varListElement = m_CurrentUserStockData.get(0);
            m_ListModel_PointArray.m_n_HighestPrice = varListElement.m_str_high;
            m_ListModel_PointArray.m_n_LowestPrice = varListElement.m_str_low;
            m_ListModel_PointArray.m_n_HighestVolume = varListElement.m_str_volume;
            m_ListModel_PointArray.m_n_LowestVolume = varListElement.m_str_volume;

            m_ListModel_PointArray.m_xaxis_min_value = m_CurrentUserStockData.m_n_HistoryRequest_StartTime_MillSeconds;
            m_ListModel_PointArray.m_xaxis_max_value = m_CurrentUserStockData.m_n_HistoryRequest_EndTime_MillSeconds;

            m_ListModel_PointArray.m_yaxis_minmax_range = m_ListModel_PointArray.m_n_HighestPrice - m_ListModel_PointArray.m_n_LowestPrice;
            m_ListModel_PointArray.m_volume_yaxis_minmax_range = m_ListModel_PointArray.m_n_HighestVolume - m_ListModel_PointArray.m_n_LowestVolume;

            m_ListModel_PointArray.m_xaxis_minmax_range = m_ListModel_PointArray.m_xaxis_max_value - m_ListModel_PointArray.m_xaxis_min_value;
            if (m_ListModel_PointArray.m_xaxis_minmax_range == 0)
            {
                console.error("HistoryDataGraphWindow.qml",
                              " ","fun_process_data",
                              " ","m_ListModel_PointArray.m_Array_PointsCount:", m_ListModel_PointArray.m_Array_PointsCount,
                              " ","m_ListModel_PointArray.m_yaxis_minmax_range:", m_ListModel_PointArray.m_yaxis_minmax_range,
                              " ","m_ListModel_PointArray.m_volume_yaxis_minmax_range:", m_ListModel_PointArray.m_volume_yaxis_minmax_range,
                              " ","m_ListModel_PointArray.m_xaxis_min_value:", m_ListModel_PointArray.m_xaxis_min_value,
                              " ","m_ListModel_PointArray.m_xaxis_max_value:", m_ListModel_PointArray.m_xaxis_max_value,
                              " ","m_ListModel_PointArray.m_xaxis_minmax_range:", m_ListModel_PointArray.m_xaxis_minmax_range);
                m_ListModel_PointArray.m_xaxis_minmax_range = 1;
                m_ListModel_PointArray.m_volume_yaxis_minmax_range = 1;
                return;
            }

        }
        console.log("HistoryDataGraphWindow.qml",
                    " ","fun_process_data",
                    " ","m_ListModel_PointArray.m_Array_PointsCount:", m_ListModel_PointArray.m_Array_PointsCount,
                    " ","m_ListModel_PointArray.m_yaxis_minmax_range:", m_ListModel_PointArray.m_yaxis_minmax_range,
                    " ","m_ListModel_PointArray.m_volume_yaxis_minmax_range:", m_ListModel_PointArray.m_volume_yaxis_minmax_range,
                    " ","m_ListModel_PointArray.m_xaxis_min_value:", m_ListModel_PointArray.m_xaxis_min_value,
                    " ","m_ListModel_PointArray.m_xaxis_max_value:", m_ListModel_PointArray.m_xaxis_max_value,
                    " ","m_ListModel_PointArray.m_xaxis_minmax_range:", m_ListModel_PointArray.m_xaxis_minmax_range,
                    " ","range days:", m_ListModel_PointArray.m_xaxis_minmax_range/m_ListModel_PointArray.nMillSecondsInOneDay);


        //m_CurrentUserStockData data 0, time is big
        //m_CurrentUserStockData data count, time is small, so we get small first
        nDataIndex = 0;
        for (nIndexX = m_CurrentUserStockData.count - 1; nIndexX >= 0; nIndexX--, nDataIndex++)
        {
            /*
                //Date,Open,High,Low,Close,Volume,Adj Close
                //2014-10-13,101.33,101.78,99.81,99.81,53485500,99.81
                "m_str_date": recordTmp[0],
                "m_str_open":recordTmp[1],
                "m_str_high":recordTmp[2],
                "m_str_low":recordTmp[3],
                "m_str_close":recordTmp[4],
                "m_str_volume":recordTmp[5],
                "m_str_adjusted":recordTmp[6]
            */
            varListElement = m_CurrentUserStockData.get(nIndexX);

            //得到最高价
            if (m_ListModel_PointArray.m_n_HighestPrice < parseFloat(varListElement.m_str_high))//parseFloat
            {
                m_ListModel_PointArray.m_n_HighestPrice = varListElement.m_str_high;
            }
            //得到最低价
            if (m_ListModel_PointArray.m_n_LowestPrice > parseFloat(varListElement.m_str_low))//parseFloat
            {
                m_ListModel_PointArray.m_n_LowestPrice = varListElement.m_str_low;
            }
            //得到最高价
            if (m_ListModel_PointArray.m_n_HighestVolume < parseInt(varListElement.m_str_volume, 10))
            {
                m_ListModel_PointArray.m_n_HighestVolume = parseInt(varListElement.m_str_volume, 10);
            }
            //得到最低价
            if (m_ListModel_PointArray.m_n_LowestVolume > parseInt(varListElement.m_str_volume, 10))
            {
                m_ListModel_PointArray.m_n_LowestVolume = parseInt(varListElement.m_str_volume, 10);
            }

            // 插入数据，它类似于Model，但多了一个 x 的坐标值
            var nHGridValue = 0.0;
            strTimePos = varListElement.m_str_date;//EDT time
            strTimePos = id_qml_HistoryDataGraphWindow.fun_process_data_time_check(strTimePos);
            if (strTimePos.length <= 0)
            {
                console.error("HistoryDataGraphWindow.qml",
                              " ","fun_process_data() length error",
                              " ","strTimePos:", strTimePos);
                return;
            }
            nTimePos = Date.fromLocaleString(locale, strTimePos, "yyyy-MM-dd hh:mm:ss");
            console.log("HistoryDataGraphWindow.qml",
                        " ","fun_process_data()",
                        " ","strTimePos:", strTimePos,
                        " ","nTimePos:", nTimePos,
                        " ","nTimePos.getTime():", nTimePos.getTime());


            nMilSecondsSinceUTCPos = nTimePos.getTime();
            nWidthPos = nMilSecondsSinceUTCPos - m_ListModel_PointArray.m_xaxis_min_value;
            nHGridValue = m_canvas.m_n_Grid_TopLeft_x + m_canvas.m_n_Grid_width * (nWidthPos/m_ListModel_PointArray.m_xaxis_minmax_range);
            console.log("HistoryDataGraphWindow.qml",
                        " ","fun_process_data()",
                        " ","nMilSecondsSinceUTCPos:", nMilSecondsSinceUTCPos,
                        " ","m_ListModel_PointArray.m_xaxis_min_value:", m_ListModel_PointArray.m_xaxis_min_value,
                        " ","nWidthPos:", nWidthPos,
                        " ","pos/range:", nWidthPos/m_ListModel_PointArray.m_xaxis_minmax_range,
                        " ","width*(pos/range):", m_canvas.m_n_Grid_width * (nWidthPos/m_ListModel_PointArray.m_xaxis_minmax_range),
                        " ","nHGridValue", nHGridValue);

            m_ListModel_PointArray.append({"m_n_HGridValue": nHGridValue,
                                              "m_str_open": varListElement.m_str_open,
                                              "m_str_close": varListElement.m_str_close,
                                              "m_str_high": varListElement.m_str_high,
                                              "m_str_low": varListElement.m_str_low,
                                              "m_str_volume": varListElement.m_str_volume,
                                              "m_str_date": varListElement.m_str_date});
            //m_ListModel_PointArray

        }//for

        m_ListModel_PointArray.m_Array_PointsCount = m_ListModel_PointArray.count;

        //range
        m_ListModel_PointArray.m_yaxis_minmax_range = m_ListModel_PointArray.m_n_HighestPrice - m_ListModel_PointArray.m_n_LowestPrice;
        m_ListModel_PointArray.m_volume_yaxis_minmax_range = m_ListModel_PointArray.m_n_HighestVolume - m_ListModel_PointArray.m_n_LowestVolume;

        console.log("HistoryDataGraphWindow.qml",
                    " ","fun_process_data",
                    " ","m_ListModel_PointArray.m_Array_PointsCount:", m_ListModel_PointArray.m_Array_PointsCount,
                    " ","m_ListModel_PointArray.m_n_HighestPrice:", m_ListModel_PointArray.m_n_HighestPrice,
                    " ","m_ListModel_PointArray.m_n_LowestPrice:", m_ListModel_PointArray.m_n_LowestPrice,
                    " ","m_ListModel_PointArray.m_yaxis_minmax_range:", m_ListModel_PointArray.m_yaxis_minmax_range,
                    " ","m_ListModel_PointArray.m_volume_yaxis_minmax_range:", m_ListModel_PointArray.m_volume_yaxis_minmax_range,
                    " ","m_ListModel_PointArray.m_n_HighestVolume:", m_ListModel_PointArray.m_n_HighestVolume,
                    " ","m_ListModel_PointArray.m_n_LowestVolume:", m_ListModel_PointArray.m_n_LowestVolume);


    }//fun_process_data


    function fun_process_data_time_check(varStrTimeTmp)
    {
        var varStrCheckShort = "yyyy-MM-dd";
        var varStrCheckLong = "yyyy-MM-dd hh:mm:ss";
        var varReturnValue = "";

        //varStrTimeTmp = varListElement.m_str_date;//EDT time

        if (varStrTimeTmp.length < varStrCheckShort.length)
        {
            console.error("HistoryDataGraphWindow.qml",
                          " ","fun_process_data_time_check",
                          " ","error varStrTimeTmp.length  varStrTimeTmp=", varStrTimeTmp);
            varReturnValue = "";
            return varReturnValue;
        }

        if (varStrTimeTmp.length < varStrCheckLong.length)
        {
            varReturnValue = varStrTimeTmp + " " + "23:59:59";
        }

        return varReturnValue;
    }



    //UI
    //画布，基本上与HTML的Canvas相同
    Canvas
    {
        id: m_canvas

        // Uncomment below lines to use OpenGL hardware accelerated rendering.
        // See Canvas documentation for available options.
        //renderTarget: Canvas.FramebufferObject  // 渲染到OpenGL的帧缓冲
        //renderStrategy: Canvas.Threaded        // 渲染工作在一个私有渲染线程中进行

        // 作为Item的派生类型，我们同样可以设置它的布局与属性
        //anchors.top: parent.top
        //anchors.left: parent.left
        //anchors.right: parent.right
        //anchors.bottom: parent.bottom
        anchors.fill: parent;//id_qml_HistoryDataGraphWindow

        //坐标线
        //红、绿、蓝。三原色
        property real m_n_Grid_TopLeft_x : 10;
        property real m_n_Grid_TopLeft_y : 10;
        property real m_n_Grid_width : m_canvas.width/2;
        property real m_n_Grid_height : m_canvas.height/2;
        property string m_str_BackGround_Colour : id_qml_HistoryDataGraphWindow.color;//"#f7f2f2"
        property real m_n_BackGround_globalAlpha:0.5;
        property string m_str_H_GridLine_Colour : "#F00000";//"red";//"#EEEEEE";
        property real m_n_H_GridLine_lineWidth : 1;
        property real m_n_H_GridLine_globalAlpha: 0.5;
        property string m_str_V_GridLine_Colour : "#F00000";//"red";//"#EEEEEE";
        property real m_n_V_GridLine_lineWidth : 1;
        property real m_n_V_GridLine_globalAlpha: 0.5;

        //平行于x轴，4条横线
        property int m_n_xaxix_GridSize : 8
        //平行于x轴，4条横线，横线之接的距离
        property real m_n_xaxix_GridStep: m_canvas.m_n_Grid_height/m_n_xaxix_GridSize

        //平行于y轴，4条竖线
        property int m_n_yaxix_GridSize : 8
        //平行于y轴，4条竖线,竖线之接的距离
        property real m_n_yaxix_GridStep: m_canvas.m_n_Grid_width/m_n_yaxix_GridSize;

        //
        property string m_str_Price_Line_Colour : "red";
        property real m_n_Price_Line_lineWidth : 1;
        property real m_n_Price_Line_globalAlpha : 1;//0.5

        //
        //bottom x axis
        property real m_n_Bottom_x_axis_x : m_n_Grid_TopLeft_x;
        property real m_n_Bottom_x_axis_y : m_n_Grid_TopLeft_y + m_n_Grid_height;
        property real m_n_Bottom_x_axis_width : m_n_Grid_width;
        property real m_n_Bottom_x_axis_globalAlpha : 1;
        property string m_str_Bottom_x_axis_Colour : "blue";//"#000000";//"#EEEEEE";
        property real m_n_Bottom_x_axis_lineWidth : 1;

        //right y axis
        property real m_n_Right_y_axis_x : m_n_Grid_TopLeft_x + m_n_Grid_width;
        property real m_n_Right_y_axis_y : m_n_Grid_TopLeft_y;
        property real m_n_Right_y_axis_height : m_n_Grid_height;
        property real m_n_Right_y_axis_globalAlpha : 1;
        property string m_str_Right_y_axis__Colour : "blue";//"#000000";//"#EEEEEE";
        property real m_str_Right_y_axis_lineWidth : 1;

        //bottom x axis Text
        property string m_str_Bottom_x_axis_Text_Colour : "DarkBlue";//"#000000";//"#EEEEEE";
        property string m_str_Bottom_x_axis_Text_Font : "Abel";//ctx.font = "Helvetica"
        property real m_n_Bottom_x_axis_Text_Step : 2;//间隔2格写个文字
        property real m_n_Bottom_x_axis_Text_globalAlpha : 1;
        property real m_n_Bottom_x_axis_Text_GridMargin : 10;//距离网格10像素

        //right y axis Text
        property string m_str_Right_y_axis_Text_Colour : "DarkBlue";//"#000000";//"#EEEEEE";
        property string m_str_Right_y_axis_Text_Font : "Abel";//ctx.font = "Helvetica"
        property real m_n_Right_y_axis_Text_Step : 2;//间隔2格写个文字
        property real m_n_Right_y_axis_Text_globalAlpha : 1;
        property real m_n_Right_y_axis_Text_GridMargin : 10;//距离网格10像素


        ///////////////////////////////////////
        ///////////////////////////////////////
        //volume grid     _volume
        property real m_n_volume_Grid_TopLeft_x : m_n_Grid_TopLeft_x;
        property real m_n_volume_Grid_TopLeft_y : m_n_Grid_TopLeft_y + m_n_Grid_height + 25;
        property real m_n_volume_Grid_width : m_n_Grid_width;
        property real m_n_volume_Grid_height : m_n_Grid_height/2;
        property string m_str_volume_BackGround_Colour : m_str_BackGround_Colour;//"#f7f2f2"
        property real m_n_volume_BackGround_globalAlpha:m_n_BackGround_globalAlpha;
        property string m_str_volume_H_GridLine_Colour : m_str_H_GridLine_Colour;//"red";//"#EEEEEE";
        property real m_n_volume_H_GridLine_lineWidth : m_n_H_GridLine_lineWidth;
        property real m_n_volume_H_GridLine_globalAlpha: m_n_H_GridLine_globalAlpha;
        property string m_str_volume_V_GridLine_Colour : m_str_V_GridLine_Colour;//"red";//"#EEEEEE";
        property real m_n_volume_V_GridLine_lineWidth : m_n_V_GridLine_lineWidth;
        property real m_n_volume_V_GridLine_globalAlpha: m_n_V_GridLine_globalAlpha;

        property int m_n_volume_xaxix_GridSize : m_n_xaxix_GridSize/2
        property real m_n_volume_xaxix_GridStep:m_n_volume_Grid_height/m_n_volume_xaxix_GridSize
        property int m_n_volume_yaxix_GridSize : m_n_yaxix_GridSize
        property real m_n_volume_yaxix_GridStep: m_n_volume_Grid_width/m_n_volume_yaxix_GridSize;
        //volume right y axis Text _volume
        property string m_str_volume_Right_y_axis_Text_Colour : m_str_Right_y_axis_Text_Colour;//"#000000";//"#EEEEEE";
        property string m_str_volume_Right_y_axis_Text_Font : m_str_Right_y_axis_Text_Font;//ctx.font = "Helvetica"
        property real m_n_volume_Right_y_axis_Text_Step : m_n_Right_y_axis_Text_Step;//间隔2格写个文字
        property real m_n_volume_Right_y_axis_Text_globalAlpha : m_n_Right_y_axis_Text_globalAlpha;
        property real m_n_volume_Right_y_axis_Text_GridMargin : m_n_Right_y_axis_Text_GridMargin;//距离网格10像素
        //
        property string m_str_volume_Price_Line_Colour : "SteelBlue";//m_str_Price_Line_Colour;
        property real m_n_volume_Price_Line_lineWidth : m_n_Price_Line_lineWidth;
        property real m_n_volume_Price_Line_globalAlpha : 0.6;//m_n_Price_Line_globalAlpha;//0.5

        //绘制入口
        onPaint:
        {
            //等待历史数据处理完成
            if (!m_CurrentUserStockData.m_bool_HistoryDataReady)
            {
                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","m_CurrentUserStockData.m_bool_HistoryDataReady:", m_CurrentUserStockData.m_bool_HistoryDataReady);
                return;
            }
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","m_CurrentUserStockData.m_bool_HistoryDataReady:", m_CurrentUserStockData.m_bool_HistoryDataReady);

            //创建ctx
            //Qt Quick QML Types  Context2D QML Type
            var ctx = m_canvas.getContext("2d");//object getContext(string contextId, any)
            //混合模式
            ctx.globalCompositeOperation = "source-over";
            //由于线宽影响绘制边界(参考HTML)，这里将线宽设置为0
            ctx.lineWidth = 3;
            //x方向的阴影
            //ctx.shadowOffsetX = 4;
            //模糊效果
            //ctx.shadowBlur = 3.5;
            //ctx.shadowColor = Qt.darker(color);

            // 由StockModel取得startDate到现在的数据数

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","m_canvas.m_n_H_GridSize:", m_canvas.m_n_xaxix_GridSize,
                        " ","m_canvas.m_n_H_GridStep:", m_canvas.m_n_xaxix_GridStep,
                        " ","m_canvas.m_n_V_GridSize:", m_canvas.m_n_yaxix_GridSize,
                        " ","m_canvas.m_n_V_GridStep:", m_canvas.m_n_yaxix_GridStep);

            //画 背景
            fun_draw_backGround(ctx);

            //计算每个点的x坐标
            id_qml_HistoryDataGraphWindow.fun_process_data();

            //fun_for_test_draw_top_bottom_left_right(ctx);


            //画 水平网格线
            fun_draw_H_gridLine(ctx);
            //画 垂直网格线
            fun_draw_V_gridLine(ctx);

            //画 水平坐标线
            //fun_draw_bottom_x_axis(ctx);
            //画 垂直坐标线
            //fun_draw_right_y_axis(ctx);

            fun_draw_bottom_x_axis_text(ctx);

            fun_draw_right_y_axis_text(ctx);

            //数据曲线绘制
            //fun_draw_price_Line(ctx);
            fun_draw_price_rect(ctx);
            fun_draw_price_rect_low_high_line(ctx);

            //_volume
            fun_draw_volume_H_gridLine(ctx);
            fun_draw_volume_V_gridLine(ctx);
            fun_draw_volume_right_y_axis_text(ctx);

            //fun_draw_volume_line(ctx);
            fun_draw_volume_rect(ctx);


        }//onPaint



        function fun_draw_backGround(ctx)
        {
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_backGround()");

            //object clearRect(real x, real y, real w, real h)
            //Clears all pixels on the canvas in the given rectangle to transparent black.
            ctx.clearRect(0, 0, m_canvas.width, m_canvas.height);//clear all

            //保存之前绘制内容
            ctx.save();
            //填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            ctx.fillStyle = m_canvas.m_str_BackGround_Colour;//"red";//"#ffffff";
            //ctx.lineWidth = 0;
            //透明度
            ctx.globalAlpha = m_n_BackGround_globalAlpha;
            //fillRect是一个便利函数，用来填充一个矩形区域
            ctx.beginPath();
            ctx.fillRect(0, 0, m_canvas.width, m_canvas.height);//all

            // 描边
            ctx.stroke();
            // 完成路径
            //ctx.closePath();
            // 载入保存的内容
            ctx.restore();
        }

        //界面的绘制由onPaint开始，这是绘制背景的一个函数。ctx作为传参，类似C++中的painter
        function fun_draw_H_gridLine(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_H_gridLine()");


            //保存之前绘制内容
            ctx.save();
            //填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            //ctx.fillStyle = m_canvas.m_str_BackGround_Colour;//"red";//"#ffffff";
            ctx.lineWidth = m_n_H_GridLine_lineWidth;
            //透明度
            ctx.globalAlpha = m_n_H_GridLine_globalAlpha;
            //描边颜色
            ctx.strokeStyle = m_str_H_GridLine_Colour;//"blue";//"#d7d7d7";
            ctx.beginPath();



            //水平网格线
            for (nIndex = 0; nIndex <= m_canvas.m_n_xaxix_GridSize; nIndex++)
            {
                xValue1 = m_n_Grid_TopLeft_x;
                yValue1 = m_n_Grid_TopLeft_y + (nIndex * m_canvas.m_n_xaxix_GridStep);
                ctx.moveTo(xValue1, yValue1);

                xValue2 = m_n_Grid_TopLeft_x + m_canvas.m_n_Grid_width;
                yValue2 = yValue1;//横向直线
                ctx.lineTo(xValue2, yValue2);
            }//for 水平网格线

            ctx.stroke();
            // 完成路径
            //ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//function fun_draw_x_gridLine(ctx)

        function fun_draw_V_gridLine(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_V_gridLine()");

            //保存之前绘制内容
            ctx.save();
            //填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            //ctx.fillStyle = m_canvas.m_str_BackGround_Colour;//"red";//"#ffffff";
            ctx.lineWidth = m_n_V_GridLine_lineWidth;
            //透明度
            ctx.globalAlpha = m_n_V_GridLine_globalAlpha;
            //描边颜色
            ctx.strokeStyle = m_str_V_GridLine_Colour;//"#d7d7d7";
            ctx.beginPath();



            //垂直网格线
            for (nIndex = 0; nIndex <= m_canvas.m_n_yaxix_GridSize; nIndex++)
            {
                xValue1 = m_n_Grid_TopLeft_x + (nIndex * m_canvas.m_n_yaxix_GridStep);
                yValue1 = m_n_Grid_TopLeft_y;
                ctx.moveTo(xValue1, yValue1);

                xValue2 = xValue1;//纵向直线
                yValue2 = m_n_Grid_TopLeft_y + m_canvas.m_n_Grid_height;
                ctx.lineTo(xValue2, yValue2);
            }//垂直网格线

            // 描边
            ctx.stroke();
            // 完成路径
            //ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//function fun_draw_y_gridLine(ctx)

        function fun_draw_bottom_x_axis(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_bottom_x_axis()");

            ctx.save();
            //ctx.fillStyle = m_canvas.m_str_BackGround_Colour;//"red";//"#ffffff";
            ctx.lineWidth = m_canvas.m_n_Bottom_x_axis_lineWidth;
            ctx.globalAlpha = m_canvas.m_n_Bottom_x_axis_globalAlpha;
            ctx.strokeStyle = m_canvas.m_str_Bottom_x_axis_Colour;//"#d7d7d7";
            ctx.beginPath();


            xValue1 = m_canvas.m_n_Bottom_x_axis_x;
            yValue1 = m_canvas.m_n_Bottom_x_axis_y;
            ctx.moveTo(xValue1, yValue1);

            xValue2 = xValue1 +  m_canvas.m_n_Bottom_x_axis_width;
            yValue2 =yValue1;//横向直线
            ctx.lineTo(xValue2, yValue2);

            //ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }//fun_draw_bottom_x_axis

        function fun_draw_right_y_axis(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_right_y_axis()");

            ctx.save();
            //ctx.fillStyle = m_canvas.m_str_BackGround_Colour;//"red";//"#ffffff";
            ctx.lineWidth = m_canvas.m_str_Right_y_axis_lineWidth;
            ctx.globalAlpha = m_canvas.m_n_Right_y_axis_globalAlpha;
            ctx.strokeStyle = m_canvas.m_str_Right_y_axis__Colour;//"#d7d7d7";
            ctx.beginPath();


            xValue1 = m_canvas.m_n_Right_y_axis_x;
            yValue1 = m_canvas.m_n_Right_y_axis_y;
            ctx.moveTo(xValue1, yValue1);

            xValue2 = xValue1;//竖向直线
            yValue2 =yValue1 +  m_canvas.m_n_Right_y_axis_height;
            ctx.lineTo(xValue2, yValue2);


            //ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }


        function fun_draw_bottom_x_axis_text(ctx)
        {
            //property real m_n_Bottom_x_axis_Text_Step : 1;//间隔1格写个文字
            var xValue = 0.0;
            var yValue = 0.0;
            var strValue = "";
            var bDrawText = false;
            var nIndex = 0;
            var nSkipStepCount = 0;


            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_bottom_x_axis_text()");

            ctx.save();
            ctx.fillStyle = m_canvas.m_str_Bottom_x_axis_Text_Colour;//"red";//"#ffffff";
            ctx.lineWidth = 0.5;
            ctx.globalAlpha = m_canvas.m_n_Bottom_x_axis_Text_globalAlpha;
            ctx.strokeStyle = m_canvas.m_str_Bottom_x_axis_Text_Colour;//"#d7d7d7";
            ctx.font = m_canvas.m_str_Bottom_x_axis_Text_Font;
            ctx.beginPath();


            //
            bDrawText = false;
            nSkipStepCount = m_n_Bottom_x_axis_Text_Step - 1;//nIndex=0 draw one text
            for (nIndex = 0; nIndex <= m_n_xaxix_GridSize; nIndex++)
            {
                if (nSkipStepCount >= m_n_Bottom_x_axis_Text_Step - 1)
                {
                    bDrawText = true;
                    nSkipStepCount = 0;
                }
                else
                {
                    nSkipStepCount++;
                }//if

                if (bDrawText)
                {
                    console.log("HistoryDataGraphWindow.qml",
                                " ","fun_draw_bottom_x_axis_text()",
                                " ","bDrawText=",bDrawText);

                    //x axis last one
                    if (nIndex >= m_n_xaxix_GridSize - 1)
                    {
                        xValue = m_canvas.m_n_Grid_TopLeft_x + (nIndex * m_canvas.m_n_yaxix_GridStep) - m_canvas.m_n_yaxix_GridStep/2;
                        //yValue 向下移动一些
                        yValue = m_canvas.m_n_Grid_TopLeft_y + m_canvas.m_n_Grid_height + m_n_Bottom_x_axis_Text_GridMargin;
                    }
                    else
                    {
                        xValue = m_canvas.m_n_Grid_TopLeft_x + (nIndex * m_canvas.m_n_yaxix_GridStep);
                        //yValue 向下移动一些
                        yValue = m_canvas.m_n_Grid_TopLeft_y + m_canvas.m_n_Grid_height + m_n_Bottom_x_axis_Text_GridMargin;
                    }

                    var varLength = (nIndex * m_canvas.m_n_yaxix_GridStep);
                    var varMillSeconds = m_ListModel_PointArray.m_xaxis_minmax_range * (varLength/m_canvas.m_n_Grid_width);
                    var varDate = new Date();
                    varDate.setTime(m_ListModel_PointArray.m_xaxis_min_value);
                    //varDate = m_ListModel_PointArray.m_xaxis_min_value;
                    //nTimePos = Date.fromLocaleString(locale, strTimePos, "yyyy-MM-dd hh:mm:ss");
                    varDate.setTime(varDate.getTime() + varMillSeconds);

                    var strYear = varDate.getFullYear();
                    var strMonth = varDate.getMonth() + 1;
                    var strDay = varDate.getDate();//.getDay();
                    //varDate.setTime(10000);//"ddd yyyy-MM-dd hh:mm:ss"//millseconds
                    //strValue = varDate.toDateString();//
                    //strValue = varDate.toLocaleDateString();//根据本地时间格式，把 Date 对象的日期部分转换为字符串。
                    strValue = strMonth + "-" + strDay;


                    ctx.text(strValue, xValue, yValue);

                    bDrawText = false;//reset
                }//if (bDrawText)

            }//for

            ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }//fun_draw_bottom_x_axis


        function fun_draw_right_y_axis_text(ctx)
        {
            //property real m_n_Right_y_axis_Text_Step : 1;//间隔1格写个文字
            var xValue = 0.0;
            var yValue = 0.0;
            var strValue = "";
            var bDrawText = false;
            var nIndex = 0;
            var nSkipStepCount = 0;


            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_right_y_axis_text()");


            ctx.save();
            ctx.fillStyle = m_canvas.m_str_Right_y_axis_Text_Colour;//"red";//"#ffffff";
            ctx.lineWidth = 0.5;
            ctx.globalAlpha = m_canvas.m_n_Right_y_axis_Text_globalAlpha;
            ctx.strokeStyle = m_canvas.m_str_Right_y_axis_Text_Colour;//"#d7d7d7";
            ctx.font = m_canvas.m_str_Right_y_axis_Text_Font;
            ctx.beginPath();


            //
            bDrawText = false;
            nSkipStepCount = m_n_Right_y_axis_Text_Step - 1;//nIndex=0 draw one text
            for (nIndex = 0; nIndex <= m_n_xaxix_GridSize; nIndex++)
            {
                if (nSkipStepCount >= m_n_Right_y_axis_Text_Step - 1)
                {
                    bDrawText = true;
                    nSkipStepCount = 0;
                }
                else
                {
                    nSkipStepCount++;
                }//if

                if (bDrawText)
                {
                    console.log("HistoryDataGraphWindow.qml",
                                " ","fun_draw_right_y_axis_text()",
                                " ","bDrawText=",bDrawText);

                    //right x axis last one
                    if (nIndex >= m_n_xaxix_GridSize - 1)
                    {
                        xValue = m_canvas.m_n_Grid_TopLeft_x + m_canvas.m_n_Grid_width + m_n_Right_y_axis_Text_GridMargin;
                        yValue = m_canvas.m_n_Grid_TopLeft_y + ((m_n_xaxix_GridSize - nIndex) * m_canvas.m_n_xaxix_GridStep) + m_n_xaxix_GridStep/2;
                    }
                    else
                    {
                        xValue = m_canvas.m_n_Grid_TopLeft_x + m_canvas.m_n_Grid_width + m_n_Right_y_axis_Text_GridMargin;
                        yValue = m_canvas.m_n_Grid_TopLeft_y + ((m_n_xaxix_GridSize - nIndex) * m_canvas.m_n_xaxix_GridStep);
                    }

                    var varLength = (nIndex * m_canvas.m_n_xaxix_GridStep);
                    var varPriceDiff = m_ListModel_PointArray.m_yaxis_minmax_range * (varLength/m_canvas.m_n_Grid_height);
                    var varPriceValue = m_ListModel_PointArray.m_n_LowestPrice + varPriceDiff;
                    strValue = varPriceValue.toFixed(3);//保留三位小数

                    ctx.text(strValue, xValue, yValue);

                    bDrawText = false;//reset
                }//if (bDrawText)

            }//for

            ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }//fun_draw_right_y_axis_text



        //
        function fun_draw_volume_H_gridLine(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_volume_H_gridLine()");

            ctx.save();
            ctx.lineWidth = m_n_volume_H_GridLine_lineWidth;
            ctx.globalAlpha = m_n_volume_H_GridLine_globalAlpha;
            ctx.strokeStyle = m_str_volume_H_GridLine_Colour;//"blue";//"#d7d7d7";
            ctx.beginPath();

            //水平网格线
            for (nIndex = 0; nIndex <= m_canvas.m_n_volume_xaxix_GridSize; nIndex++)
            {
                xValue1 = m_n_volume_Grid_TopLeft_x;
                yValue1 = m_n_volume_Grid_TopLeft_y + (nIndex * m_canvas.m_n_volume_xaxix_GridStep);
                ctx.moveTo(xValue1, yValue1);

                xValue2 = m_n_volume_Grid_TopLeft_x + m_canvas.m_n_volume_Grid_width;
                yValue2 = yValue1;//横向直线
                ctx.lineTo(xValue2, yValue2);
            }//for 水平网格线

            ctx.stroke();
            ctx.restore();
        }//function fun_draw_volume_H_gridLine(ctx)




        function fun_draw_volume_V_gridLine(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_volume_V_gridLine()");

            //保存之前绘制内容
            ctx.save();
            ctx.lineWidth = m_n_volume_V_GridLine_lineWidth;
            ctx.globalAlpha = m_n_volume_V_GridLine_globalAlpha;
            ctx.strokeStyle = m_str_volume_V_GridLine_Colour;//"#d7d7d7";
            ctx.beginPath();

            //垂直网格线
            for (nIndex = 0; nIndex <= m_canvas.m_n_volume_yaxix_GridSize; nIndex++)
            {
                xValue1 = m_n_volume_Grid_TopLeft_x + (nIndex * m_canvas.m_n_volume_yaxix_GridStep);
                yValue1 = m_n_volume_Grid_TopLeft_y;
                ctx.moveTo(xValue1, yValue1);

                xValue2 = xValue1;//纵向直线
                yValue2 = m_n_volume_Grid_TopLeft_y + m_canvas.m_n_volume_Grid_height;
                ctx.lineTo(xValue2, yValue2);
            }//垂直网格线

            ctx.stroke();
            ctx.restore();
        }//function fun_draw_y_gridLine(ctx)




        function fun_draw_volume_right_y_axis_text(ctx)
        {
            //property real m_n_Right_y_axis_Text_Step : 1;//间隔1格写个文字
            var xValue = 0.0;
            var yValue = 0.0;
            var strValue = "";
            var bDrawText = false;
            var nIndex = 0;
            var nSkipStepCount = 0;


            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_volume_right_y_axis_text()");

            ctx.save();
            ctx.fillStyle = m_canvas.m_str_volume_Right_y_axis_Text_Colour;//"red";//"#ffffff";
            ctx.lineWidth = 0.5;
            ctx.globalAlpha = m_canvas.m_n_volume_Right_y_axis_Text_globalAlpha;
            ctx.strokeStyle = m_canvas.m_str_volume_Right_y_axis_Text_Colour;//"#d7d7d7";
            ctx.font = m_canvas.m_str_volume_Right_y_axis_Text_Font;
            ctx.beginPath();


            //
            bDrawText = false;
            nSkipStepCount = m_n_volume_Right_y_axis_Text_Step - 1;//nIndex=0 draw one text
            for (nIndex = 0; nIndex <= m_n_volume_xaxix_GridSize; nIndex++)
            {
                if (nSkipStepCount >= m_n_volume_Right_y_axis_Text_Step - 1)
                {
                    bDrawText = true;
                    nSkipStepCount = 0;
                }
                else
                {
                    nSkipStepCount++;
                }//if

                if (bDrawText)
                {
                    console.log("HistoryDataGraphWindow.qml",
                                " ","fun_draw_volume_right_y_axis_text()",
                                " ","bDrawText=",bDrawText);

                    //right x axis last one
                    if (nIndex >= m_n_volume_xaxix_GridSize - 1)
                    {
                        xValue = m_canvas.m_n_volume_Grid_TopLeft_x + m_canvas.m_n_volume_Grid_width + m_n_volume_Right_y_axis_Text_GridMargin;
                        yValue = m_canvas.m_n_volume_Grid_TopLeft_y + ((m_n_volume_xaxix_GridSize - nIndex) * m_canvas.m_n_volume_xaxix_GridStep) + m_n_volume_xaxix_GridStep/2;
                    }
                    else
                    {
                        xValue = m_canvas.m_n_volume_Grid_TopLeft_x + m_canvas.m_n_volume_Grid_width + m_n_volume_Right_y_axis_Text_GridMargin;
                        yValue = m_canvas.m_n_volume_Grid_TopLeft_y + ((m_n_volume_xaxix_GridSize - nIndex) * m_canvas.m_n_volume_xaxix_GridStep);
                    }


                    var varLength = (nIndex * m_canvas.m_n_volume_xaxix_GridStep);
                    var varVolumeDiff = m_ListModel_PointArray.m_volume_yaxis_minmax_range * (varLength/m_canvas.m_n_volume_Grid_height);
                    var varVolumeValue = m_ListModel_PointArray.m_n_LowestVolume + varVolumeDiff;
                    strValue = varVolumeValue;//.toFixed(3);//保留三位小数

                    console.log("HistoryDataGraphWindow.qml",
                                " ","fun_draw_volume_right_y_axis_text()",
                                " ","xValue=",xValue,
                                " ","yValue=",yValue,
                                " ","strValue=",strValue);
                    ctx.text(strValue, xValue, yValue);

                    bDrawText = false;//reset
                }//if (bDrawText)

            }//for

            ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }//fun_draw_volume_right_y_axis_text


        function fun_for_test_draw_top_bottom_left_right(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test_draw_top_bottom_left_right()");

            ctx.save();
            //ctx.fillStyle = "green";//"#ffffff";
            ctx.lineWidth = 1;//must 1  2 will have error
            ctx.globalAlpha = 1;
            ctx.strokeStyle ="green";//"#d7d7d7";
            ctx.beginPath();

            //坐标线
            xValue1 = m_canvas.m_n_Grid_TopLeft_x;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1 +  m_canvas.m_n_Grid_width;
            yValue2 =yValue1;//横向直线
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);

            xValue1 = m_canvas.m_n_Grid_TopLeft_x;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y + m_canvas.m_n_Grid_height;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1 +  m_canvas.m_n_Grid_width;
            yValue2 =yValue1;//横向直线
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);

            xValue1 = m_canvas.m_n_Grid_TopLeft_x;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1;
            yValue2 =yValue1  + m_canvas.m_n_Grid_height;
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);

            xValue1 = m_canvas.m_n_Grid_TopLeft_x + m_canvas.m_n_Grid_width;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1;
            yValue2 =yValue1  + m_canvas.m_n_Grid_height;
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);


            //x
            xValue1 = m_canvas.m_n_Grid_TopLeft_x;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1 + m_canvas.m_n_Grid_width;
            yValue2 = yValue1  + m_canvas.m_n_Grid_height;
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);

            xValue1 = m_canvas.m_n_Grid_TopLeft_x;
            yValue1 = m_canvas.m_n_Grid_TopLeft_y + m_canvas.m_n_Grid_height;
            ctx.moveTo(xValue1, yValue1);
            xValue2 = xValue1 + m_canvas.m_n_Grid_width;
            yValue2 = m_canvas.m_n_Grid_TopLeft_y;
            ctx.lineTo(xValue2, yValue2);

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_for_test",
                        " ","xValue1=",xValue1,
                        " ","yValue1=",yValue1,
                        " ","xValue2=",xValue2,
                        " ","yValue2=",yValue2);


            //ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }//fun_draw_bottom_x_axis


        //数据曲线绘制
        //fun_draw_Line(ctx, m_Array_Points, 0, m_Array_Points.count - 1, m_str_open, "red", m_n_HighestPrice, m_n_LowestPrice);
        //function fun_draw_Line(ctx, arrayPoints, nIndexFrom, nIndexTo, valueType, lineColor, highestValue, lowestValue)
        //use    function fun_process_data()  first
        function fun_draw_price_Line(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var vCurrentValue = 0.0;
            //取值范围
            //var nGraph_heightRange = m_ListModel_PointArray.m_n_HighestPrice - m_ListModel_PointArray.m_n_LowestPrice;
            var nGraph_heightRange = m_ListModel_PointArray.m_yaxis_minmax_range;
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_Line()",
                        " ","nGraph_heightRange=",nGraph_heightRange);

            // 保存之前绘制内容
            ctx.save();
            ctx.globalAlpha = m_n_Price_Line_globalAlpha;//透明度
            ctx.strokeStyle = m_str_Price_Line_Colour;
            ctx.lineWidth = m_n_Price_Line_lineWidth;
            ctx.beginPath();

            if (nGraph_heightRange == 0)
            {
                //range作为被除数不能为0
                nGraph_heightRange = 1;
            }


            //曲线
            /*
              ----------------------------------------------> x
              |x=0 y=0
              |
              |
              |
              |
              V y
            */
            for (nIndex = 0; nIndex < m_ListModel_PointArray.count; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_ListModel_PointArray.get(nIndex).m_n_HGridValue;
                //取出对应设置的价格数据
                vCurrentValue = m_ListModel_PointArray.get(nIndex).m_str_low;//m_str_low//m_str_close
                //
                yValue1 = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - vCurrentValue)/nGraph_heightRange );
                yValue1 = m_canvas.m_n_Grid_TopLeft_y + yValue1;

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_Line()",
                            " ","m_n_HighestPrice:",m_ListModel_PointArray.m_n_HighestPrice,
                            " ","vCurrentValue:",vCurrentValue,
                            " ","nGraph_heightRange:",nGraph_heightRange,
                            " ","m_n_HighestPrice:",m_ListModel_PointArray.m_n_HighestPrice,
                            " ","m_n_Grid_height:",m_canvas.m_n_Grid_height,
                            " ","yValue1 add:",(m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - vCurrentValue)/nGraph_heightRange )),
                            " ","m_n_Grid_TopLeft_y:",m_canvas.m_n_Grid_TopLeft_y,
                            " ","yValue1:",yValue1);

                if (nIndex == 0)
                {
                    //移动到初始点
                    ctx.moveTo(xValue1, yValue1);
                }
                else
                {
                    //向后绘制
                    ctx.lineTo(xValue1, yValue1);
                }

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_Line()",
                            " ","xValue1:",xValue1,
                            " ","yValue1:",yValue1);

            }//曲线


            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//fun_draw_Line




        //数据矩形绘制
        function fun_draw_price_rect(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var yValueAdd = 0.0;
            var vCurrentValue = 0.0;
            var xHight = 0.0;
            var yHight = 0.0;
            var varHightValue = 0.0;
            var xLow = 0.0;
            var yLow = 0.0;
            var varLowValue = 0.0;
            var varCloseValue = 0.0;
            var varOpenValue = 0.0;
            var varStrColour = "green";


            //取值范围
            //var nGraph_heightRange = m_ListModel_PointArray.m_n_HighestPrice - m_ListModel_PointArray.m_n_LowestPrice;
            var nGraph_heightRange = m_ListModel_PointArray.m_yaxis_minmax_range;
            var oneRectWith = m_canvas.m_n_Grid_width *
                    (m_ListModel_PointArray.nMillSecondsInOneDay/m_ListModel_PointArray.m_xaxis_minmax_range);
            oneRectWith = oneRectWith * (14/16);//adjuset
            var oneRectheight = 0.0;
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_Line()",
                        " ","nGraph_heightRange=",nGraph_heightRange,
                        " ","oneRectWith=",oneRectWith);

            // 保存之前绘制内容
            ctx.save();
            ctx.fillStyle = m_str_Price_Line_Colour;
            ctx.globalAlpha = m_n_Price_Line_globalAlpha;//透明度
            ctx.strokeStyle = m_str_Price_Line_Colour;
            ctx.lineWidth = m_n_Price_Line_lineWidth;
            ctx.beginPath();

            if (nGraph_heightRange == 0)
            {
                //range作为被除数不能为0
                nGraph_heightRange = 1;
            }


            //曲线
            /*
              ----------------------------------------------> x
              |x=0 y=0
              |
              |
              |
              |
              V y
            */
            for (nIndex = 0; nIndex < m_ListModel_PointArray.count; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_ListModel_PointArray.get(nIndex).m_n_HGridValue;
                //取出对应设置的价格数据
                varCloseValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_close);
                varOpenValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_open);
                varHightValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_high);
                varLowValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_low);

                if (varCloseValue >= varOpenValue)
                {
                    //vCurrentValue = varOpenValue;//use min value
                    vCurrentValue = varCloseValue;
                    varStrColour = "green";
                    oneRectheight = m_canvas.m_n_Grid_height * ((varCloseValue - varOpenValue)/nGraph_heightRange);
                }
                else
                {
                    //vCurrentValue = varCloseValue;//use min value
                    vCurrentValue = varOpenValue;
                    varStrColour = "red";
                    oneRectheight = m_canvas.m_n_Grid_height * ((varOpenValue - varCloseValue)/nGraph_heightRange);
                }
                ctx.fillStyle = varStrColour;
                //ctx.strokeStyle = varStrColour;
                //
                yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - vCurrentValue)/nGraph_heightRange );
                yValue1 = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_price_rect()",
                            " ","vCurrentValue:",vCurrentValue,
                            " ","yValue1 add:",yValueAdd,
                            " ","xValue1:",xValue1,
                            " ","yValue1:",yValue1,
                            " ","oneRectWith:",oneRectWith,
                            " ","oneRectheight:",oneRectheight,
                            " ","varStrColour:",varStrColour);

                ctx.fillRect(xValue1, yValue1, oneRectWith, oneRectheight);

                /*
                //
                xHight = xValue1 + oneRectWith / 2;
                yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - varHightValue)/nGraph_heightRange );
                yHight = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;

                xLow = xHight;
                yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - varLowValue)/nGraph_heightRange );
                yLow = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;
                ctx.moveTo(xHight, yHight);
                ctx.lineTo(xLow, yLow);
                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_price_rect()",
                            " ","xHight:",xHight,
                            " ","yHight:",yHight,
                            " ","xLow:",xLow,
                            " ","yLow:",yLow,
                            " ","varStrColour:",varStrColour);

                */


            }//曲线


            ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//fun_draw_price_rect

        function fun_draw_price_rect_low_high_line(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var yValueAdd = 0.0;
            var vCurrentValue = 0.0;
            var xHight = 0.0;
            var yHight = 0.0;
            var varHightValue = 0.0;
            var xLow = 0.0;
            var yLow = 0.0;
            var varLowValue = 0.0;
            var varCloseValue = 0.0;
            var varOpenValue = 0.0;
            var varStrColour = "green";


            //取值范围
            //var nGraph_heightRange = m_ListModel_PointArray.m_n_HighestPrice - m_ListModel_PointArray.m_n_LowestPrice;
            var nGraph_heightRange = m_ListModel_PointArray.m_yaxis_minmax_range;
            var oneRectWith = m_canvas.m_n_Grid_width *
                    (m_ListModel_PointArray.nMillSecondsInOneDay/m_ListModel_PointArray.m_xaxis_minmax_range);
            oneRectWith = oneRectWith * (14/16);//adjuset
            var oneRectheight = 0.0;
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_price_rect_low_high_line()",
                        " ","nGraph_heightRange=",nGraph_heightRange,
                        " ","oneRectWith=",oneRectWith);

            // 保存之前绘制内容
            ctx.save();
            //ctx.fillStyle = m_str_Price_Line_Colour;
            ctx.fillStyle = "red";
            ctx.globalAlpha = m_n_Price_Line_globalAlpha;//透明度
            ctx.strokeStyle = m_str_Price_Line_Colour;
            //ctx.strokeStyle = "red";
            ctx.lineWidth = m_n_Price_Line_lineWidth;
            ctx.beginPath();

            if (nGraph_heightRange == 0)
            {
                //range作为被除数不能为0
                nGraph_heightRange = 1;
            }


            //曲线
            /*
              ----------------------------------------------> x
              |x=0 y=0
              |
              |
              |
              |
              V y
            */
            for (nIndex = 0; nIndex < m_ListModel_PointArray.count; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_ListModel_PointArray.get(nIndex).m_n_HGridValue;
                //取出对应设置的价格数据
                varCloseValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_close);
                varOpenValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_open);
                varHightValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_high);
                varLowValue = parseFloat(m_ListModel_PointArray.get(nIndex).m_str_low);

                if (varCloseValue >= varOpenValue)
                {
                    //vCurrentValue = varOpenValue;//use min value
                    vCurrentValue = varCloseValue;
                    varStrColour = "green";
                    oneRectheight = m_canvas.m_n_Grid_height * ((varCloseValue - varOpenValue)/nGraph_heightRange);
                }
                else
                {
                    //vCurrentValue = varCloseValue;//use min value
                    vCurrentValue = varOpenValue;
                    varStrColour = "red";
                    oneRectheight = m_canvas.m_n_Grid_height * ((varOpenValue - varCloseValue)/nGraph_heightRange);
                }
                //ctx.fillStyle = varStrColour;
                ctx.strokeStyle = varStrColour;
                //
                //yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - vCurrentValue)/nGraph_heightRange );
                //yValue1 = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;
                //ctx.fillRect(xValue1, yValue1, oneRectWith, oneRectheight);

                //
                xHight = xValue1 + oneRectWith / 2;
                yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - varHightValue)/nGraph_heightRange );
                yHight = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;

                xLow = xHight;
                yValueAdd = m_canvas.m_n_Grid_height * ((m_ListModel_PointArray.m_n_HighestPrice - varLowValue)/nGraph_heightRange );
                yLow = m_canvas.m_n_Grid_TopLeft_y + yValueAdd;
                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_price_rect_low_high_line()",
                            " ","xHight:",xHight,
                            " ","yHight:",yHight,
                            " ","xLow:",xLow,
                            " ","yLow:",yLow,
                            " ","varStrColour:",varStrColour);

                //ctx.strokeStyle = varStrColour;
                //ctx.strokeStyle = "red";
                ctx.moveTo(xHight, yHight);
                ctx.lineTo(xLow, yLow);




            }//曲线


            ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//fun_draw_price_rect


        function fun_draw_volume_line(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var vCurrentValue = 0.0;
            //取值范围
            var nGraph_heightRange = m_ListModel_PointArray.m_volume_yaxis_minmax_range;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_volume_line()",
                        " ","nGraph_heightRange=",nGraph_heightRange);


            // 保存之前绘制内容
            ctx.save();
            ctx.globalAlpha = m_n_volume_Price_Line_globalAlpha;//透明度
            ctx.strokeStyle = m_str_volume_Price_Line_Colour;
            ctx.lineWidth = m_n_volume_Price_Line_lineWidth;
            ctx.beginPath();

            if (nGraph_heightRange == 0)
            {
                //range作为被除数不能为0
                nGraph_heightRange = 1;
            }


            //曲线
            /*
              ----------------------------------------------> x
              |x=0 y=0
              |
              |
              |
              |
              V y
            */

            for (nIndex = 0; nIndex < m_ListModel_PointArray.count; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_ListModel_PointArray.get(nIndex).m_n_HGridValue;
                //取出对应设置的价格数据
                vCurrentValue = m_ListModel_PointArray.get(nIndex).m_str_volume;
                //

                yValue1 = m_canvas.m_n_volume_Grid_height * ((vCurrentValue - m_ListModel_PointArray.m_n_LowestVolume)/nGraph_heightRange );
                yValue1 = m_canvas.m_n_volume_Grid_TopLeft_y + yValue1;

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_volume_line()",
                            " ","vCurrentValue:",vCurrentValue,
                            " ","nGraph_heightRange:",nGraph_heightRange,
                            " ","m_n_HighestVolume:",m_ListModel_PointArray.m_n_HighestVolume,
                            " ","m_n_volume_Grid_height:",m_canvas.m_n_volume_Grid_height,
                            " ","yValue1 add:",(m_canvas.m_n_volume_Grid_height * ((m_ListModel_PointArray.m_n_HighestVolume - vCurrentValue)/nGraph_heightRange )),
                            " ","m_n_volume_Grid_TopLeft_y:",m_canvas.m_n_volume_Grid_TopLeft_y,
                            " ","yValue1:",yValue1);



                if (nIndex == 0)
                {
                    //移动到初始点
                    ctx.moveTo(xValue1, yValue1);
                }
                else
                {
                    //向后绘制
                    ctx.lineTo(xValue1, yValue1);
                }

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_volume_line()",
                            " ","xValue1:",xValue1,
                            " ","yValue1:",yValue1);

            }//曲线

            ctx.stroke();
            ctx.restore();
        }//fun_draw_volume_line




        function fun_draw_volume_rect(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var yValueAdd = 0.0;
            var vCurrentValue = 0.0;
            //取值范围
            var nGraph_heightRange = m_ListModel_PointArray.m_volume_yaxis_minmax_range;
            var oneRectWith = m_canvas.m_n_volume_Grid_width * (m_ListModel_PointArray.nMillSecondsInOneDay/m_ListModel_PointArray.m_xaxis_minmax_range);
            var oneRectheight = 0.0;
            /*
            m_ListModel_PointArray.m_xaxis_min_value = m_CurrentUserStockData.m_n_HistoryRequest_StartTime_MillSeconds;
            m_ListModel_PointArray.m_xaxis_max_value = m_CurrentUserStockData.m_n_HistoryRequest_EndTime_MillSeconds;
            m_ListModel_PointArray.m_xaxis_minmax_range = m_ListModel_PointArray.m_xaxis_max_value - m_ListModel_PointArray.m_xaxis_min_value;
            */

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_volume_rect()",
                        " ","nGraph_heightRange=",nGraph_heightRange,
                        " ","oneRectWith=",oneRectWith);


            // 保存之前绘制内容
            ctx.save();
            ctx.fillStyle = m_str_volume_Price_Line_Colour;
            ctx.globalAlpha = m_n_volume_Price_Line_globalAlpha;//透明度
            ctx.lineWidth = 1;
            ctx.beginPath();

            //ctx.shadowOffsetX = 4;
            //ctx.shadowBlur = 3.5;
            //ctx.shadowColor = Qt.darker(color);

            if (nGraph_heightRange == 0)
            {
                //range作为被除数不能为0
                nGraph_heightRange = 1;
            }


            //曲线
            /*
              ----------------------------------------------> x
              |x=0 y=0
              |
              |
              |
              |
              V y
            */

            for (nIndex = 0; nIndex < m_ListModel_PointArray.count; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_ListModel_PointArray.get(nIndex).m_n_HGridValue;
                //取出对应设置的价格数据
                vCurrentValue = m_ListModel_PointArray.get(nIndex).m_str_volume;
                //

                yValueAdd = m_canvas.m_n_volume_Grid_height * ((vCurrentValue - m_ListModel_PointArray.m_n_LowestVolume)/nGraph_heightRange );
                yValue1 = m_canvas.m_n_volume_Grid_TopLeft_y + yValueAdd;
                oneRectheight = m_canvas.m_n_volume_Grid_height - yValueAdd;

                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_volume_rect()",
                            " ","vCurrentValue:",vCurrentValue,
                            " ","xValue1:",xValue1,
                            " ","yValue1:",yValue1,
                            " ","oneRectWith:",oneRectWith,
                            " ","oneRectheight:",oneRectheight);


                //object fillRect(real x, real y, real w, real h)
                oneRectWith = 2;
                ctx.fillRect(xValue1, yValue1, oneRectWith, oneRectheight);


                if (nIndex == 0)
                {
                    //移动到初始点
                    ctx.moveTo(xValue1, yValue1);
                }
                else
                {
                    //向后绘制
                    ctx.lineTo(xValue1, yValue1);
                }


                console.log("HistoryDataGraphWindow.qml",
                            " ","Canvas onPaint",
                            " ","fun_draw_volume_rect()",
                            " ","xValue1:",xValue1,
                            " ","yValue1:",yValue1);

            }//曲线

            ctx.stroke();
            ctx.restore();
        }//fun_draw_volume_line

    }//Canvas


}//Rectangle


//doc begin
/*
  http://www.cnblogs.com/east-liujie/archive/2006/10/21/535784.html
javascript Date日期对象
new Date("month dd,yyyy hh:mm:ss");
   new  Date("month dd,yyyy");
   new  Date(yyyy,mth,dd,hh,mm,ss);
   new Date(yyyy,mth,dd);
   new Date(ms);需要注意最后一种形式，参数表示的是需要创建的时间和GMT时间1970年1月1日之间相差的毫秒数。

month:用英文表示月份名称，从January到December
mth:用整数表示月份，从（１月）到１１（１２月）
dd:表示一个月中的第几天，从1到31
yyyy:四位数表示的年份
hh:小时数，从0（午夜）到23（晚11点）
mm:分钟数，从0到59的整数
ss:秒数，从0到59的整数
ms:毫秒数，为大于等于0的整数

new Date("January 12,2006 22:19:35");
new Date("January 12,2006");
new Date(2006,0,12,22,19,35);
new Date(2006,0,12);
new Date(1137075575000);
上面的各种创建形式都表示2006　年1月12日这一天。



*/
//doc end
