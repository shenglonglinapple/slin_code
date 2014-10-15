import QtQuick 2.0

Rectangle {
    id: id_qml_StockChart
    width: 320
    height: 200

    property var stockModel: null
    property var startDate: new Date()             // new Date()初始化得到的是当前时间
    property var endDate: new Date()
    property string activeChart: "year"            // 设置表格显示的时间跨度为一年
    property var settings
    property int gridSize: 4                      // 每个网格宽度为4px
    property real gridStep: gridSize ? (width - canvas.tickMargin) / gridSize : canvas.xGridStep                                                                                                            // 网格数为（宽度 - 最右方那一栏的宽度）/ 网格宽度，如果gridSize为0，采用画布中的计算方式

    function update() {                           // 更新函数
        endDate = new Date();
        if (id_qml_StockChart.activeChart === "year") {                 // 显示一年数据
            id_qml_StockChart.startDate = new Date(id_qml_StockChart.endDate.getFullYear() - 1,       // 在当前时间的基础上减一年
                                       id_qml_StockChart.endDate.getMonth(),
                                       id_qml_StockChart.endDate.getDate());
            id_qml_StockChart.gridSize = 12;                                              // 设置网格宽度为12，以固定网格数
        }
        else if (id_qml_StockChart.activeChart === "month") {          // 显示一个月数据
            id_qml_StockChart.startDate = new Date(id_qml_StockChart.endDate.getFullYear(),           // 在当前时间基础上减一个月
                                       id_qml_StockChart.endDate.getMonth() - 1,
                                       id_qml_StockChart.endDate.getDate());
            gridSize = 0;                                     // gridSize为0时，采用canvas中定义的网格宽度计算。使每个数据都绘制在坐标线上
        }
        else if (id_qml_StockChart.activeChart === "week") {           // 显示一周数据
            id_qml_StockChart.startDate = new Date(id_qml_StockChart.endDate.getFullYear(),            // 在当前时间基础上减七天
                                       id_qml_StockChart.endDate.getMonth(),
                                       id_qml_StockChart.endDate.getDate() - 7);
            gridSize = 0;
        }
        else {
            id_qml_StockChart.startDate = new Date(2005, 3, 25);         // 否则以2005年为初始年，并定义网格宽度为4
            gridSize = 4;
        }

        canvas.requestPaint();                            // 当更新时需要调用画布的这个函数
    }

    Row {                                       // Row布局了4个自定义的按钮
        id: activeChartRow
        anchors.left: id_qml_StockChart.left
        anchors.right: id_qml_StockChart.right
        anchors.top: id_qml_StockChart.top
        anchors.topMargin: 4
        spacing: 52
        onWidthChanged: {                    // 该函数保证宽度变化时优先压缩spacing，且不会造成按钮重叠
            var buttonsLen = maxButton.width + yearButton.width + monthButton.width + weekButton.width;
            var space = (width - buttonsLen) / 3;
            spacing = Math.max(space, 10);
        }

        Button {
            id: maxButton
            text: "Max"
            buttonEnabled: id_qml_StockChart.activeChart === "max"
            onClicked: {
                id_qml_StockChart.activeChart = "max";          // 改变当前图表显示模式，这里的max 实际对应update中的'else'，即2005年作为起始年
                id_qml_StockChart.update();                     // 更新
            }
        }
        Button {
            id: yearButton
            text: "Year"
            buttonEnabled: id_qml_StockChart.activeChart === "year"
            onClicked: {
                id_qml_StockChart.activeChart = "year";
                id_qml_StockChart.update();
            }
        }
        Button {
            id: monthButton
            text: "Month"
            buttonEnabled: id_qml_StockChart.activeChart === "month"
            onClicked: {
                id_qml_StockChart.activeChart = "month";
                id_qml_StockChart.update();
            }
        }
        Button {
            id: weekButton
            text: "Week"
            buttonEnabled: id_qml_StockChart.activeChart === "week"
            onClicked: {
                id_qml_StockChart.activeChart = "week";
                id_qml_StockChart.update();
            }
        }
    }

    Text {                                    // 下方的起始日期显示
        id: fromDate
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 8
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        text: "| " + startDate.toDateString()
    }

    Text {                                    // 结束日期显示
        id: toDate
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 8
        anchors.right: parent.right
        anchors.rightMargin: canvas.tickMargin
        anchors.bottom: parent.bottom
        text: endDate.toDateString() + " |"
    }

    Canvas {                                 // 画布，基本上与HTML的Canvas相同
        id: canvas
                                                                                                                                                                  // 注释介绍将下面两行语句取消注释以获得OpenGL的硬件加速渲染，为什么没有开？有些平台不支持嘛...
        // Uncomment below lines to use OpenGL hardware accelerated rendering.
        // See Canvas documentation for available options.
        //renderTarget: Canvas.FramebufferObject  // 渲染到OpenGL的帧缓冲
        //renderStrategy: Canvas.Threaded        // 渲染工作在一个私有渲染线程中进行

        anchors.top: activeChartRow.bottom    // 作为Item的派生类型，我们同样可以设置它的布局与属性
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: fromDate.top

        property int pixelSkip: 1
        property int numPoints: 1           // 存储数据点的个数
        property int tickMargin: 32         // 右边格的宽度

        property real xGridStep: (width - tickMargin) / numPoints // 网格宽度
        property real yGridOffset: height / 26                // y方向向下的偏移度，用在水平线的绘制
        property real yGridStep: height / 12                  // 网格高度

        function drawBackground(ctx) {        // 界面的绘制由onPaint开始，这是绘制背景的一个函数。ctx作为传参，类似C++中的painter
            ctx.save();                                     // 保存之前绘制内容
            ctx.fillStyle = "#ffffff";                      // 填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            ctx.fillRect(0, 0, canvas.width, canvas.height);  // fillRect是一个便利函数，用来填充一个矩形区域
            ctx.strokeStyle = "#d7d7d7";                    // 描边颜色
            ctx.beginPath();
                                                             // 水平网格线
            for (var i = 0; i < 12; i++) {
                ctx.moveTo(0, canvas.yGridOffset + i * canvas.yGridStep);
                ctx.lineTo(canvas.width, canvas.yGridOffset + i * canvas.yGridStep);
            }

                                                             // 垂直网格线
            var height = 35 * canvas.height / 36;            // 垂直线的高度为画布高度的 35/36
            var yOffset = canvas.height - height;            // 垂直线离顶部距离为高度的 1/36
            var xOffset = 0;
            for (i = 0; i < id_qml_StockChart.gridSize; i++) {
                ctx.moveTo(xOffset + i * id_qml_StockChart.gridStep, yOffset);
                ctx.lineTo(xOffset + i * id_qml_StockChart.gridStep, height);
            }
            ctx.stroke();                                    // 描线

                                                             // 右方以及下方颜色较深的那几根线
            ctx.strokeStyle = "#666666";
            ctx.beginPath();
            var xStart = canvas.width - tickMargin;          // x = 画布宽度 - 价格部分宽度
            ctx.moveTo(xStart, 0);
            ctx.lineTo(xStart, canvas.height);               // 向下画直线
            for (i = 0; i < 12; i++) {
                ctx.moveTo(xStart, canvas.yGridOffset + i * canvas.yGridStep);       // 12根短横线
                ctx.lineTo(canvas.width, canvas.yGridOffset + i * canvas.yGridStep);
            }
            ctx.moveTo(0, canvas.yGridOffset + 9 * canvas.yGridStep);           // 移动绘制点到第九根横线左端
            ctx.lineTo(canvas.width, canvas.yGridOffset + 9 * canvas.yGridStep);  // 向右绘制横线
            ctx.closePath();                                                     // 完成路径
            ctx.stroke();                                                      // 描边

            ctx.restore();                                                     // 载入保存的内容
        }

        function drawScales(ctx, high, low, vol)         // 绘制右方股票价格标尺函数
        {
            ctx.save();
            ctx.strokeStyle = "#888888";
            ctx.font = "10px Open Sans"
            ctx.beginPath();

            // prices on y-axis
            var x = canvas.width - tickMargin + 3;       // 离右边实线3px
            var priceStep = (high - low) / 9.0;          // 相隔最高价与最低价的差值除以9
            for (var i = 0; i < 10; i += 2) {            // 隔一级显示
                var price = parseFloat(high - i * priceStep).toFixed(1);
                ctx.text(price, x, canvas.yGridOffset + i * yGridStep - 2); // 绘制text的坐标在文字的左下角
            }

            // highest volume
            ctx.text(vol, 0, canvas.yGridOffset + 9 * yGridStep + 12);   // 绘制最高成交量

            ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }

        function drawPrice(ctx, from, to, color, price, points, highest, lowest)     // 数据曲线绘制
        {
            ctx.save();
            ctx.globalAlpha = 0.7;                  // 透明度
            ctx.strokeStyle = color;                // color由StockSettingPanel指定
            ctx.lineWidth = 3;
            ctx.beginPath();

            var end = points.length;                // 数据长度

            var range = highest - lowest;          // 取值范围
            if (range == 0) {
                range = 1;                         // range作为被除数不能为0
            }

            for (var i = 0; i < end; i += pixelSkip) {
                var x = points[i].x;
                var y = points[i][price];           // 取出对应设置的价格数据
                var h = 9 * yGridStep;              // 设置绘制高度为九倍的网格高度

                y = h * (lowest - y)/range + h + yGridOffset;   // lowest - y为非正数，h + yGridOffset为曲线绘制的底部

                if (i == 0) {
                    ctx.moveTo(x, y);               // 移动到初始点
                } else {
                    ctx.lineTo(x, y);               // 向后绘制
                }
            }
            ctx.stroke();
            ctx.restore();
        }

        function drawVolume(ctx, from, to, color, price, points, highest)            // 成交量绘制函数
        {
            ctx.save();
            ctx.fillStyle = color;
            ctx.globalAlpha = 0.8;
            ctx.lineWidth = 0;                 // 由于线宽影响绘制边界(参考HTML)，这里将线宽设置为0
            ctx.beginPath();

            var end = points.length;
            var margin = 0;

            if (id_qml_StockChart.activeChart === "month" || id_qml_StockChart.activeChart === "week") {
                margin = 8;
                ctx.shadowOffsetX = 4;             // x方向的阴影
                ctx.shadowBlur = 3.5;              // 模糊效果
                ctx.shadowColor = Qt.darker(color);
            }
                                                                                                                                                                      // 由于柱状图的宽度限制，柱状图比实际的数据少一个
            // To match the volume graph with price grid, skip drawing the initial
            // volume of the first day on chart.
            for (var i = 1; i < end; i += pixelSkip) {
                var x = points[i - 1].x;
                var y = points[i][price];
                y = canvas.height * (y / highest);
                y = 3 * y / 12;                               // 柱状图高度占画布的1/4
                ctx.fillRect(x, canvas.height - y + yGridOffset,
                             canvas.xGridStep - margin, y);    // "周"与"月"时有间隔，其他则没有
            }

            ctx.stroke();
            ctx.restore();
        }

        onPaint: {                                            // 绘制入口
            if (!stockModel.ready) {                          // 等待数据完成
                return;
            }

            numPoints = stockModel.indexOf(id_qml_StockChart.startDate);  // 由StockModel取得startDate到现在的数据数

            if (id_qml_StockChart.gridSize == 0)
                id_qml_StockChart.gridSize = numPoints                    // 使gridStep绑定到(width - canvas.tickMargin) / numPoints上

            var ctx = canvas.getContext("2d");                // 创建ctx
            ctx.globalCompositeOperation = "source-over";     // 混合模式
            ctx.lineWidth = 1;

            drawBackground(ctx);                              // 背景绘制

            var highestPrice = 0;
            var highestVolume = 0;
            var lowestPrice = -1;
            var points = [];                                  // 创建一个数组
            for (var i = numPoints, j = 0; i >= 0 ; i -= pixelSkip, j += pixelSkip) {   // pixelSkip被定义为 1
                var price = stockModel.get(i);
                if (parseFloat(highestPrice) < parseFloat(price.high))           // 得到最高价
                    highestPrice = price.high;
                if (parseInt(highestVolume, 10) < parseInt(price.volume, 10))    // 得到最低价
                    highestVolume = price.volume;
                if (lowestPrice < 0 || parseFloat(lowestPrice) > parseFloat(price.low))   // 注意这里如果设置lowestPrice = 0或是别的数
                    lowestPrice = price.low;            // 就有可能一直无法满足条件，因此添加这个负数使第一个price.low被赋予lowestPrice
                points.push({                           // 插入数据，它类似于Model，但多了一个 x 的坐标值
                                x: j * xGridStep,
                                open: price.open,
                                close: price.close,
                                high: price.high,
                                low: price.low,
                                volume: price.volume
                            });
            }

            if (settings.drawHighPrice)                 // 判断StockSettingPanel中相应的选项是否被勾选，然后绘制数据线段
                drawPrice(ctx, 0, numPoints, settings.highColor, "high", points, highestPrice, lowestPrice);
            if (settings.drawLowPrice)
                drawPrice(ctx, 0, numPoints, settings.lowColor, "low", points, highestPrice, lowestPrice);
            if (settings.drawOpenPrice)
                drawPrice(ctx, 0, numPoints,settings.openColor, "open", points, highestPrice, lowestPrice);
            if (settings.drawClosePrice)
                drawPrice(ctx, 0, numPoints, settings.closeColor, "close", points, highestPrice, lowestPrice);

            drawVolume(ctx, 0, numPoints, settings.volumeColor, "volume", points, highestVolume);   // 成交量绘制
            drawScales(ctx, highestPrice, lowestPrice, highestVolume);            // 价格标尺绘制
        }
    }
}


