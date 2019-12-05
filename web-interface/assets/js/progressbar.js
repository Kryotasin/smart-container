// Counter To Count Number Visit
// var a = 0;
var p = 0;
var q = 0;
var TOTAL1 = 10;
var TOTAL2 = 10;
$('window').ready(function () {

    $('#get_btn').click(function () {
        getInput()
        getDepth()
        getWeight()

        $("#value1").text(p + "%");
        $("#value2").text(q + "%");

        $('#progress1').attr('aria-valuenow', p)
        $('#progress1').find('span').text(p + '%');
        $('#progress1').css({
            width: p + '%'
        })

        $('#progress2').attr('aria-valuenow', q)
        $('#progress2').find('span').text(q + '%');
        $('#progress2').css({
            width: q + '%'
        })
        warnDisplay()
    });
})


function getInput() {
    TOTAL1 = $('#total_input1').val() ? $('#total_input1').val() : TOTAL1;
    TOTAL2 = $('#total_input1').val() ? $('#total_input2').val() : TOTAL2;
}

function getDepth() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', 'https://api.particle.io/v1/devices/420034000447373336323230/dist?access_token=3c33433343294cd46363a060ff449c00e18854ba', true);
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            var data = JSON.parse(xhr.responseText);
            if (data.hasOwnProperty('result')) {

                var tempdist = parseFloat(data.result)
                p = (TOTAL1 - tempdist) / TOTAL1 * 100;
                p.toFixed(2);
                // p = typeof(data.result);

                if(p<0){
                    p=0
                }
            }
        }
    }
    xhr.send(null);

    
    // p = 3 / TOTAL1 * 100;

}

function getWeight() {
    // var xhr = new XMLHttpRequest();
    // xhr.open('GET', 'https://api.particle.io/v1/devices/550048000751373238323937/weight?access_token=498ab0c21d0a86ccdf69a7c33d3152822f3aafa7', true);
    // xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    // xhr.onreadystatechange = function () {
    //     if (xhr.readyState === 4 && xhr.status === 200) {
    //         var data = JSON.parse(xhr.responseText);
    //         if (data.hasOwnProperty('result')) {
    //             var tempweight = parseFloat(data.result) 
    //             q = tempweight / TOTAL2 * 100;
    //             if(q < 0){
    //             q = 0
    //             }
    //         }
    //     }
    // }
    // xhr.send(null);

    q = 4 / TOTAL2 * 100;
}


function warnDisplay() {
    var x = document.getElementById("warning");
    if (p <= 30) {
        x.style.visibility = "visible";
    }
    else {
        x.style.visibility = "hidden";
    }
}