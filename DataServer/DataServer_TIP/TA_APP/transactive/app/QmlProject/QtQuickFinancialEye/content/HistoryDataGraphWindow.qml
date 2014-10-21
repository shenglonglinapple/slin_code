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
    color: "#f7f2f2"

    function fun_update()
    {
        //当更新时需要调用画布的这个函数
        m_canvas.requestPaint();
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
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        //平行于x轴，4条横线
        property int m_n_H_GridSize : 4
        //平行于x轴，4条横线，横线之接的距离
        property real m_n_H_GridStep: id_qml_HistoryDataGraphWindow.height/m_n_H_GridSize

        //平行于y轴，4条竖线
        property int m_n_V_GridSize : 4
        //平行于y轴，4条竖线,竖线之接的距离
        property real m_n_V_GridStep: id_qml_HistoryDataGraphWindow.width/m_n_V_GridSize;

        //
        property string m_strColour_BackGround : id_qml_HistoryDataGraphWindow.color;//"#f7f2f2"
        property real m_n_BackGround_globalAlpha:0.3;
        property string m_strColour_H_GridLine : "blue";
        property real m_n_H_GridLine_lineWidth : 1;
        property real m_n_H_GridLine_globalAlpha:0.3;
        property string m_strColour_V_GridLine : "green";
        property real m_n_V_GridLine_lineWidth : 1;
        property real m_n_V_GridLine_globalAlpha:0.3;

        //data
        //创建一个数组
        /*
                m_Array_Points.push({m_n_HGridValue: (nIndexY * m_canvas.m_n_H_OneDataStep),
                                m_str_open: varListElement.m_str_open,
                                m_str_close: varListElement.m_str_close,
                                m_str_high: varListElement.m_str_high,
                                m_str_low: varListElement.m_str_low,
                                m_str_volume: varListElement.m_str_volume});
        */
        property variant m_Array_Points : [];//JSON.stringify(m_Array_Points) m_Array_Points.length
        property int m_Array_PointsCount: 0;// 存储数据点的个数
        property real m_n_HighestPrice : 0;
        property real m_n_LowestPrice : 0;
        property real m_n_HighestVolume : 0;
        property real m_n_LowestVolume : 0;
        property real m_n_H_OneDataStep : 0;//m_canvas.width/m_Array_PointsCount






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
            var ctx = m_canvas.getContext("2d");//object getContext(string contextId, any)
            //混合模式
            ctx.globalCompositeOperation = "source-over";
            ctx.lineWidth = 1;

            // 由StockModel取得startDate到现在的数据数

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","m_canvas.m_n_H_GridSize:", m_canvas.m_n_H_GridSize,
                        " ","m_canvas.m_n_H_GridStep:", m_canvas.m_n_H_GridStep,
                        " ","m_canvas.m_n_V_GridSize:", m_canvas.m_n_V_GridSize,
                        " ","m_canvas.m_n_V_GridStep:", m_canvas.m_n_V_GridStep);

            //计算每个点的x坐标
            fun_process_data();
            //画 背景
            fun_draw_backGround(ctx);
            //画 水平网格线
            fun_draw_H_gridLine(ctx);
            //画 垂直网格线
            fun_draw_V_gridLine(ctx);

            //数据曲线绘制
            fun_draw_Line(ctx);

        }//onPaint



        function fun_draw_backGround(ctx)
        {
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_backGround()");

            //保存之前绘制内容
            ctx.save();
            //填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            ctx.fillStyle = m_canvas.m_strColour_BackGround;//"red";//"#ffffff";
            ctx.lineWidth = 0;
            //透明度
            ctx.globalAlpha = m_n_BackGround_globalAlpha;
            //fillRect是一个便利函数，用来填充一个矩形区域
            ctx.beginPath();
            ctx.fillRect(0, 0, m_canvas.width, m_canvas.height);

            // 描边
            ctx.stroke();
            // 完成路径
            ctx.closePath();
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
            ctx.fillStyle = m_canvas.m_strColour_BackGround;//"red";//"#ffffff";
            ctx.lineWidth = m_n_H_GridLine_lineWidth;
            //透明度
            ctx.globalAlpha = m_n_H_GridLine_globalAlpha;
            //描边颜色
            ctx.strokeStyle = m_strColour_H_GridLine;//"blue";//"#d7d7d7";
            ctx.beginPath();


            //水平网格线
            for (nIndex = 0; nIndex < m_canvas.m_n_H_GridSize; nIndex++)
            {
                xValue1 = 0;
                yValue1 = nIndex * m_canvas.m_n_H_GridStep;
                ctx.moveTo(xValue1, yValue1);

                xValue2 = m_canvas.width;
                yValue2 = yValue1;
                ctx.lineTo(xValue2, yValue2);
            }//for 水平网格线

            ctx.stroke();
            // 完成路径
            ctx.closePath();
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
            ctx.fillStyle = m_canvas.m_strColour_BackGround;//"red";//"#ffffff";
            ctx.lineWidth = m_n_V_GridLine_lineWidth;
            //透明度
            ctx.globalAlpha = m_n_V_GridLine_globalAlpha;
            //描边颜色
            ctx.strokeStyle = m_strColour_V_GridLine;//"#d7d7d7";
            ctx.beginPath();

            //垂直网格线
            for (nIndex = 0; nIndex < m_canvas.m_n_V_GridSize; nIndex++)
            {
                xValue1 = nIndex * m_canvas.m_n_V_GridStep;
                yValue1 = 0;
                ctx.moveTo(xValue1, yValue1);

                xValue2 = xValue1;
                yValue2 = m_canvas.height;
                ctx.lineTo(xValue2, yValue2);
            }//垂直网格线

            // 描边
            ctx.stroke();
            // 完成路径
            ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }//function fun_draw_y_gridLine(ctx)


        //数据曲线绘制
        //fun_draw_Line(ctx, m_Array_Points, 0, m_Array_Points.count - 1, m_str_open, "red", m_n_HighestPrice, m_n_LowestPrice);
        //function fun_draw_Line(ctx, arrayPoints, nIndexFrom, nIndexTo, valueType, lineColor, highestValue, lowestValue)
        function fun_draw_Line(ctx)
        {
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var vCurrentValue = 0.0;
            //取值范围
            var range = m_n_HighestPrice - m_n_LowestPrice;

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_draw_Line()");

            // 保存之前绘制内容
            ctx.save();
            ctx.globalAlpha = 0.7;//透明度
            ctx.strokeStyle = "red";
            ctx.lineWidth = 3;
            ctx.beginPath();

            if (range == 0)
            {
                //range作为被除数不能为0
                range = 1;
            }


            //曲线
            for (nIndex = 0; nIndex < m_Array_Points.length; nIndex++)
            {
                vCurrentValue = 0.0;
                xValue1 = m_Array_Points[nIndex].m_n_HGridValue;
                //取出对应设置的价格数据
                vCurrentValue = m_Array_Points[nIndex].m_str_close;
                //
                yValue1 = (vCurrentValue - m_canvas.m_n_LowestPrice);

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

        //m_CurrentUserStockData  ListModel
        //计算每个点的x坐标
        function fun_process_data()
        {
            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_process_data",
                        " ","Array.isArray(m_Array_Points):", Array.isArray(m_canvas.m_Array_Points));

            m_canvas.m_Array_Points = [];
            m_canvas.m_Array_PointsCount = 0;
            m_canvas.m_n_HighestPrice = 0;
            m_canvas.m_n_LowestPrice = 0;
            m_canvas.m_n_HighestVolume = 0;
            m_canvas.m_n_LowestVolume = 0;
            m_canvas.m_n_H_OneDataStep = 0;

            var nIndexX = 0;
            var nIndexY = 0;
            var varListElement;

            //init first data
            m_canvas.m_Array_PointsCount = m_CurrentUserStockData.count;
            if (m_canvas.m_Array_PointsCount >= 0)
            {
               varListElement = m_CurrentUserStockData.get(0);
               m_canvas.m_n_HighestPrice = varListElement.m_str_high;
               m_canvas.m_n_LowestPrice = varListElement.m_str_low;
               m_canvas.m_n_HighestVolume = varListElement.m_str_volume;
               m_canvas.m_n_LowestVolume = varListElement.m_str_volume;
               m_canvas.m_n_H_OneDataStep = m_canvas.width / m_canvas.m_Array_PointsCount;
            }

            //m_CurrentUserStockData data 0, time is big
            //m_CurrentUserStockData data count, time is small, so we get small first
            nIndexY = 0;
            for (nIndexX = m_canvas.m_Array_PointsCount - 1; nIndexX >= 0; nIndexX--, nIndexY++)
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
                if (m_canvas.m_n_HighestPrice < parseFloat(varListElement.m_str_high))//parseFloat
                {
                    m_canvas.m_n_HighestPrice = varListElement.m_str_high;
                }
                //得到最低价
                if (m_canvas.m_n_LowestPrice > parseFloat(varListElement.m_str_low))//parseFloat
                {
                    m_canvas.m_n_LowestPrice = varListElement.m_str_low;
                }
                //得到最高价
                if (m_canvas.m_n_HighestVolume < parseInt(varListElement.m_str_volume, 10))
                {
                    m_canvas.m_n_HighestVolume = varListElement.m_str_volume;
                }
                //得到最低价
                if (m_canvas.m_n_LowestVolume > parseInt(varListElement.m_str_volume, 10))
                {
                    m_canvas.m_n_LowestVolume = varListElement.m_str_volume;
                }

                // 插入数据，它类似于Model，但多了一个 x 的坐标值
                m_Array_Points.push({m_n_HGridValue: (nIndexY * m_canvas.m_n_H_OneDataStep),
                                m_str_open: varListElement.m_str_open,
                                m_str_close: varListElement.m_str_close,
                                m_str_high: varListElement.m_str_high,
                                m_str_low: varListElement.m_str_low,
                                m_str_volume: varListElement.m_str_volume});
                //m_Array_Points

            }//for

            console.log("HistoryDataGraphWindow.qml",
                        " ","Canvas onPaint",
                        " ","fun_process_data",
                        " ","Array.isArray(m_Array_Points):", Array.isArray(m_canvas.m_Array_Points),
                        " ","m_canvas.m_Array_PointsCount:", m_canvas.m_Array_PointsCount,
                        " ","m_canvas.m_n_H_OneDataStep:", m_canvas.m_n_H_OneDataStep,
                        " ","m_canvas.m_n_HighestPrice:", m_canvas.m_n_HighestPrice,
                        " ","m_canvas.m_n_LowestPrice:", m_canvas.m_n_LowestPrice,
                        " ","m_canvas.m_n_HighestVolume:", m_canvas.m_n_HighestVolume,
                        " ","m_canvas.m_n_LowestVolume:", m_canvas.m_n_LowestVolume);


        }//fun_process_data

    }//Canvas


}//Rectangle


