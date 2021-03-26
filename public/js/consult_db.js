const RELAY1 = firebase.database().ref('statusActuators/RELAY1');
const RELAY2 = firebase.database().ref('statusActuators/RELAY2');
const RELAY3 = firebase.database().ref('statusActuators/RELAY3');
const RELAY4 = firebase.database().ref('statusActuators/RELAY4');



var temperature= document.getElementById("temperatureDHT22");
var humidity= document.getElementById("humidityDHT22");
var light=document.getElementById("light");
var bar_humididty=document.getElementById("bar_humidity");
var bar_light=document.getElementById("light_bar");
var water_bar=document.getElementById("water_bar");
var pressure=document.getElementById("pressure");
var co2=document.getElementById("co2");
var TVOC=document.getElementById("TVOC");
var wind=document.getElementById("wind");
var direction=document.getElementById("direction");
var time=document.getElementById("time");
var battery=document.getElementById("battery");
var relay4=document.getElementById("relay4");
var relay3=document.getElementById("relay3");
var relay2=document.getElementById("relay2");
var relay1=document.getElementById("relay1");

const batteryCanvasCtx = document.getElementById('battery-chart').getContext('2d')
const batterylevelChart = {
  type: 'doughnut',
  data: {
    labels: ["BATTERY LEFT",  "DISCHARGE"],
    datasets: [{
      data: [],
      backgroundColor: ['#f6c23e','#f8f9fc'],
      hoverBackgroundColor: ['#FFE633', '#f8f9fc'],
      hoverBorderColor: "rgba(234, 236, 244, 1)",
    }],
  },
  options: {
    maintainAspectRatio: false,
    tooltips: {
      backgroundColor: "rgb(255,255,255)",
      bodyFontColor: "#858796",
      borderColor: '#dddfeb',
      borderWidth: 1,
      xPadding: 15,
      yPadding: 15,
      displayColors: false,
      caretPadding: 10,
    },
    legend: {
      display: false
    },
    cutoutPercentage: 80,
  },
};
const batteryChart = new Chart(batteryCanvasCtx, batterylevelChart);

function logOut(){
firebase.auth().signOut().then(() => {
  // Sign-out successful.
}).catch((error) => {
  // An error happened.
});
}

firebase.database().ref('/CurrentValues').on('value', snapshot => { 
  const realtimedata = snapshot.val();
  //console.log(realtimedata);
  //console.log(realtimedata.lux);
  light.innerHTML ='<strong>'+ realtimedata.lux +'</strong>';
  wind.innerHTML ='<strong>'+ realtimedata.wind +'</strong>';
  direction.innerHTML ='<strong>'+ realtimedata.direction +'</strong>';
 
  pressure.innerHTML ='<strong>' + realtimedata.Pressure +'</strong>';
  temperature.innerHTML ='<strong>' +realtimedata.TemperatureAir+'</strong>';
  humidity.innerHTML ='<strong>' +realtimedata.HumidityAir+'</strong>';
  co2.innerHTML ='<strong>' +realtimedata.eCO2+'</strong>';
  TVOC.innerHTML ='<strong>' +realtimedata.TVOC+'</strong>';
  time.innerHTML ='<strong>' +realtimedata.TimeMeassure+'</strong>';
  document.getElementById("water_status").innerHTML ='<strong>' +realtimedata.waterLevel + ' % </strong>'; 
  pushData(batterylevelChart.data.datasets[0].data, realtimedata.battery);
  pushData(batterylevelChart.data.datasets[0].data, (100-realtimedata.battery));
  battery.innerHTML ='<strong>' +realtimedata.battery+ ' % </strong>';
  batteryChart.update();
  document.getElementsByClassName("progress-bar")[0].style.width = Math.floor(realtimedata.HumidityAir) + "%";
  document.getElementsByClassName("progress-bar")[1].style.width = Math.floor((realtimedata.lux)*100/65000) + "%";
  document.getElementsByClassName("progress-bar")[2].style.width = Math.floor(realtimedata.waterLevel);

 });


 // RELAY 4

 $("#relay4").change(function() {
   if(relay4.style.backgroundColor =="rgb(217, 83, 79)"){   // SI ESTA EN ROJO
    firebase.database().ref('statusActuators/').update({
      RELAY4: 1
    });
   relay4.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
   document.getElementById("statusRelay4").innerHTML="ON"
  }else{
    relay4.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
    document.getElementById("statusRelay4").innerHTML="OFF"
    firebase.database().ref('statusActuators/').update({
      RELAY4: 0
    });
  }
 })


RELAY4.on('value', data => {
  if(data.val()=='1'){
    relay4.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE   
    document.getElementById("statusRelay4").innerHTML="ON";
    $("#customSwitch4").prop("checked", true)
  }else{
    relay4.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
    document.getElementById("statusRelay4").innerHTML="OFF";

    $("#customSwitch4").prop("checked", false)
  }
});


// RELAY 3

$("#relay3").change(function() {
  if(relay3.style.backgroundColor =="rgb(217, 83, 79)"){   // SI ESTA EN ROJO
   firebase.database().ref('statusActuators/').update({
     RELAY3: 1
   });
  relay3.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay3").innerHTML="ON"
 }else{
   relay3.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay3").innerHTML="OFF"
   firebase.database().ref('statusActuators/').update({
     RELAY3: 0
   });
 }
})


RELAY3.on('value', data => {
 if(data.val()=='1'){
   relay3.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE   
   document.getElementById("statusRelay3").innerHTML="ON";
   $("#customSwitch3").prop("checked", true)
 }else{
   relay3.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay3").innerHTML="OFF";

   $("#customSwitch3").prop("checked", false)
 }
});

// RELAY 2

$("#relay2").change(function() {
  if(relay2.style.backgroundColor =="rgb(217, 83, 79)"){   // SI ESTA EN ROJO
   firebase.database().ref('statusActuators/').update({
     RELAY2: 1
   });
  relay2.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay2").innerHTML="ON"
 }else{
   relay2.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay2").innerHTML="OFF"
   firebase.database().ref('statusActuators/').update({
     RELAY2: 0
   });
 }
})


RELAY2.on('value', data => {
 if(data.val()=='1'){
   relay2.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE   
   document.getElementById("statusRelay2").innerHTML="ON";
   $("#customSwitch2").prop("checked", true)
 }else{
   relay2.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay2").innerHTML="OFF";

   $("#customSwitch2").prop("checked", false)
 }
});


// RELAY 1

$("#relay1").change(function() {
  if(relay1.style.backgroundColor =="rgb(217, 83, 79)"){   // SI ESTA EN ROJO
   firebase.database().ref('statusActuators/').update({
     RELAY1: 1
   });
  relay1.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay1").innerHTML="ON"
 }else{
   relay1.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay1").innerHTML="OFF"
   firebase.database().ref('statusActuators/').update({
     RELAY1: 0
   });
 }
})


RELAY1.on('value', data => {
 if(data.val()=='1'){
   relay1.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE   
   document.getElementById("statusRelay1").innerHTML="ON";
   $("#customSwitch1").prop("checked", true)
 }else{
   relay1.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay1").innerHTML="OFF";

   $("#customSwitch1").prop("checked", false)
 }
});