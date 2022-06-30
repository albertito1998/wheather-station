var userName=document.getElementById("userName");
var PhotoProfile=document.getElementById("PhotoProfile");
var insertList=document.getElementById("contenido_dropdown");




var temp_dataset=[];
var CO2_dataset=[];
var humidity_dataset=[];
var light_dataset=[];
var TVOC_dataset=[];
var pressure_dataset=[];
var wind_dataset=[];
var battery_dataset=[];
var uv_dataset=[];
var waterLevel_dataset=[];
var watts_dataset=[];
var current_dataset=[];
var chart_labels=[];
var numberOfStations =[];
var lat_dataset=[];
var long_dataset=[];
var dataSet_lat_long = [];
var contenido=" ";
var scripts=" ";
var user1;
var scripts_relays=" ";




var temperature= document.getElementById("temperatureDHT22");
var humidity= document.getElementById("humidityDHT22");
var light=document.getElementById("light");
var bar_humididty=document.getElementById("bar_humidity");
var bar_light=document.getElementById("light_bar");
var water_bar=document.getElementById("water_bar");
var water_status=document.getElementById("water_status");
var pressure=document.getElementById("pressure");
var ultraviolet=document.getElementById("UV");
var co2=document.getElementById("co2");
var TVOC=document.getElementById("TVOC");
var wind=document.getElementById("wind");
var direction=document.getElementById("direction");
var forecast=document.getElementById("forecast");
var time=document.getElementById("time");
var solarVoltage=document.getElementById("voltageSolar");
var watts=document.getElementById("watts");
var status_rain=document.getElementById("rain_status");
var batteryVoltage=document.getElementById("batteryVoltage");
var currentSolar=document.getElementById("currentSolar");
var altitude=document.getElementById("altitude");
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

  
let resultOfRealtime = [];
let resultOfFirestore = [];

  //INIT OF CODE

firebase.auth().onAuthStateChanged((user) => {
  if (user) {
  userName.innerHTML = '<strong>'+user.displayName+'</strong>';
  if(user.photoURL!= null){
   // email = user.email;
  PhotoProfile.src = user.photoURL;
  }
//-------------------------------------RELAY UPDATE QUERY TO BBDD--------------------------------------------------
//RELAY4
document.getElementById("relay4").addEventListener("change", function() {  if(relay4.style.backgroundColor =="rgb(217, 83, 79)"){  firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({  RELAY4: 1 }); relay4.style.backgroundColor="#5cb85c";document.getElementById("statusRelay4").innerHTML="ON";}else{relay4.style.backgroundColor="#d9534f";  document.getElementById("statusRelay4").innerHTML="OFF"; firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({   RELAY4: 0 });}});
//RELAY3
document.getElementById("relay3").addEventListener("change", function() {  if(relay3.style.backgroundColor =="rgb(217, 83, 79)"){  firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({  RELAY3: 1 }); relay3.style.backgroundColor="#5cb85c";document.getElementById("statusRelay3").innerHTML="ON";}else{relay3.style.backgroundColor="#d9534f";  document.getElementById("statusRelay3").innerHTML="OFF"; firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({   RELAY3: 0 });}});
//RELAY2
document.getElementById("relay2").addEventListener("change", function() {  if(relay2.style.backgroundColor =="rgb(217, 83, 79)"){  firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({  RELAY2: 1 }); relay4.style.backgroundColor="#5cb85c";document.getElementById("statusRelay2").innerHTML="ON";}else{relay2.style.backgroundColor="#d9534f";  document.getElementById("statusRelay2").innerHTML="OFF"; firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({   RELAY2: 0 });}});
//RELAY1
document.getElementById("relay1").addEventListener("change", function() {  if(relay1.style.backgroundColor =="rgb(217, 83, 79)"){  firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({  RELAY1: 1 }); relay1.style.backgroundColor="#5cb85c";document.getElementById("statusRelay1").innerHTML="ON";}else{relay1.style.backgroundColor="#d9534f";  document.getElementById("statusRelay1").innerHTML="OFF"; firebase.database().ref(user.uid+'/'+$(".btn_1").val()+'/statusActuators').update({   RELAY1: 0 });}});




//----------------------- REALTIME DATABASE ------------------------------------

firebase.database().ref(user.uid).on("value", snapshot =>  {
  numberOfStations = Object.keys(snapshot.val());
  contenido=[];
  
  
  for(var i = 0; i<numberOfStations.length; i++){
   
    contenido = contenido + '<li><a class="dropdown-item" href="#" id="'+numberOfStations[i]+'">'+numberOfStations[i]+'</a></li>'; 
    // HANDLE CLICK DISPLAY
   scripts=scripts+ 'document.getElementById("'+numberOfStations[i]+'").addEventListener("click", function() {    $(".btn_1:first-child").text($(this).text());$(".btn_1:first-child").val($(this).text());firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/CurrentValues").on("value", snapshot => {  var realtimedata = snapshot.val();  light.innerHTML ="<strong>"+ realtimedata.lux +"</strong>"; forecast.innerHTML ="<strong>"+ realtimedata.forecast +"</strong>"; wind.innerHTML ="<strong>"+ realtimedata.wind  +"</strong>";   direction.innerHTML ="<strong>"+ realtimedata.direction +"</strong>";  pressure.innerHTML ="<strong>" + realtimedata.Pressure +"</strong>"; ultraviolet.innerHTML="<strong>" +realtimedata.UV +"</strong>";solarVoltage.innerHTML ="<strong>" +realtimedata.solarVoltage+"</strong>"; watts.innerHTML ="<strong>" +realtimedata.watts+"</strong>";status_rain.innerHTML ="<strong>" +realtimedata.statusRain+"</strong>"; currentSolar.innerHTML ="<strong>" +realtimedata.currentSolar+"</strong>"; temperature.innerHTML ="<strong>" +realtimedata.TemperatureAir+"</strong>"; altitude.innerHTML ="<strong>" +realtimedata.Altitude+"</strong>";    humidity.innerHTML ="<strong>" +realtimedata.HumidityAir+ "</strong>";   co2.innerHTML ="<strong>" +realtimedata.eCO2+"</strong>";TVOC.innerHTML ="<strong>" +realtimedata.TVOC+"</strong>"; time.innerHTML ="<strong>" +realtimedata.TimeMeassure+"</strong>"; document.getElementById("water_status").innerHTML ="<strong>" +realtimedata.waterLevel + "</strong>"; document.getElementById("water_bar").innerHTML ="<strong>" +realtimedata.waterLevel + "</strong>"; document.getElementById("light_bar").innerHTML ="<strong>" +realtimedata.lux + "</strong>";  document.getElementById("bar_humidity").innerHTML ="<strong>" +realtimedata.HumidityAir + "</strong>";batterylevelChart.data.datasets[0].data=[];pushData(batterylevelChart.data.datasets[0].data, realtimedata.battery); pushData(batterylevelChart.data.datasets[0].data, (100-realtimedata.battery)); battery.innerHTML ="<strong>" +realtimedata.battery+ " % </strong>";batteryVoltage.innerHTML ="<strong>" +realtimedata.voltage+ " V </strong>"; batteryChart.update();  document.getElementsByClassName("progress-bar")[0].style.width = Math.floor(realtimedata.HumidityAir)+"%"; document.getElementsByClassName("progress-bar")[1].style.width = Math.floor((realtimedata.lux))+"%"; document.getElementsByClassName("progress-bar")[2].style.width = Math.floor(realtimedata.waterLevel)+"%";  dataSet_lat_long =[ {lat: realtimedata.lat, long: realtimedata.long},  ]; });    let valueSensors = databasesensor.collection("SENSORS/'+ user.uid+'/'+numberOfStations[i]+'"); let query = valueSensors.get().then(snapshot => { temp_dataset=[];uv_dataset=[];CO2_dataset=[];humidity_dataset=[];light_dataset=[];TVOC_dataset=[];pressure_dataset=[];wind_dataset=[];battery_dataset=[];current_dataset=[];chart_labels=[];numberOfStations =[];waterLevel_dataset=[];lat_dataset=[];long_dataset=[];dataSet_lat_long = [];if (snapshot.empty) {  console.log("No matching documents.");  return;}snapshot.forEach(doc => {chart_labels.push(doc.data().TIMESTAMP);temp_dataset.push(doc.get("TemperatureDHT22"));CO2_dataset.push(doc.get("CO2"));humidity_dataset.push(doc.get("HumidityDHT22"));uv_dataset.push(doc.get("UV"));TVOC_dataset.push(doc.get("TVOC"));pressure_dataset.push(doc.get("PressureBMP180"));current_dataset.push(doc.get("currentSolar"));battery_dataset.push(doc.get("battery"));wind_dataset.push(doc.get("TemperatureDHT22"));light_dataset.push(doc.get("LIGHT"));waterLevel_dataset.push(doc.get("waterLevel"));   });   }).catch(err => {console.log("Error getting documents", err);    });      document.getElementById("Submitpicker").addEventListener("click", function() { dateStringStart = $("#datetimepicker1").val();dateStringEnd = $("#datetimepicker2").val(); dateArgs1 = dateStringStart.match('+/\d{2,4}/g+'),  year1 = dateArgs1[2],  month1 = parseInt(dateArgs1[1]) - 1,  day1 = dateArgs1[0],  hour1 = dateArgs1[3],  minutes1 = dateArgs1[4];  dateArgs = dateStringEnd.match('+/\d{2,4}/g+'), year = dateArgs[2], month = parseInt(dateArgs[1]) - 1, day = dateArgs[0], hour = dateArgs[3], minutes = dateArgs[4]; var Startdate = new Date(year1, month1, day1, hour1, minutes1).getTime(); var Enddate = new Date(year, month, day, hour, minutes).getTime(); cleanArray ();  if($(".btn_1").val()=== "'+numberOfStations[i]+'"){ console.log("query lanzada"); let consulta = databasesensor.collection("SENSORS/'+user.uid+'/'+numberOfStations[i]+'").where("timestamp", ">=", Startdate/1000).where("timestamp", "<=", Enddate/1000).get()   .then(snapshot => {  if (snapshot.empty) {  console.log("No matching documents.");  return;        }; snapshot.forEach(doc => {chart_labels.push(doc.data().TIMESTAMP); temp_dataset.push(doc.get("TemperatureDHT22")); CO2_dataset.push(doc.get("CO2"));humidity_dataset.push(doc.get("HumidityDHT22"));TVOC_dataset.push(doc.get("TVOC"));pressure_dataset.push(doc.get("PressureBMP180"));battery_dataset.push(doc.get("batteryLevel"));watts_dataset.push(doc.get("watts"));wind_dataset.push(doc.get("WIND"));light_dataset.push(doc.get("LIGHT"));uv_dataset.push(doc.get("UV")); waterLevel_dataset.push(doc.get("waterLevel"));  });      }).catch(err => {  console.log("Error getting documents", err);});}   }); function cleanArray (){ temp_dataset=[],CO2_dataset=[],humidity_dataset=[], watts_dataset=[],light_dataset=[], uv_dataset=[],TVOC_dataset=[], pressure_dataset=[], wind_dataset=[], battery_dataset=[], chart_labels=[],waterLevel_dataset=[]; }                   if($(".btn_1").val()=== "'+numberOfStations[i]+'"){const RELAY1 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY1");const RELAY2 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY2");const RELAY3 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY3");const RELAY4 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY4");       RELAY4.on("value", data => { if(data.val()=="1"){  relay4.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay4").innerHTML="ON"; $("#customSwitch4").prop("checked", true)}else{  relay4.style.backgroundColor="#d9534f"; document.getElementById("statusRelay4").innerHTML="OFF"; $("#customSwitch4").prop("checked", false)  }});        RELAY3.on("value", data => { if(data.val()=="1"){  relay3.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay3").innerHTML="ON"; $("#customSwitch3").prop("checked", true)}else{  relay3.style.backgroundColor="#d9534f"; document.getElementById("statusRelay3").innerHTML="OFF"; $("#customSwitch3").prop("checked", false)  }});              RELAY2.on("value", data => { if(data.val()=="1"){  relay2.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay2").innerHTML="ON"; $("#customSwitch2").prop("checked", true)}else{  relay2.style.backgroundColor="#d9534f"; document.getElementById("statusRelay2").innerHTML="OFF"; $("#customSwitch2").prop("checked", false)  }});             RELAY1.on("value", data => { if(data.val()=="1"){  relay1.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay1").innerHTML="ON"; $("#customSwitch1").prop("checked", true)}else{  relay1.style.backgroundColor="#d9534f"; document.getElementById("statusRelay1").innerHTML="OFF"; $("#customSwitch1").prop("checked", false)  }})}                  });' 

  }


  insertList.innerHTML=contenido;
  var newScript = document.createElement("script");
  newScript.setAttribute('type', 'text/javascript');
  newScript.text=scripts;
  document.body.appendChild(newScript);
  

 
 
  });  
  } else {
    // User is signed out
    // ...
  }
})



/*
  if($(".btn_1").val()=== "'+numberOfStations[i]+'"){const RELAY1 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY1");const RELAY2 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY2");const RELAY3 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY3");const RELAY4 = firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators/RELAY4");document.getElementById("relay4").addEventListener("change", function() { console.log("lanzado"); if(relay4.style.backgroundColor =="rgb(217, 83, 79)"){  firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators").update({  RELAY4: 1 }); relay4.style.backgroundColor="#5cb85c";document.getElementById("statusRelay4").innerHTML="ON";}else{relay4.style.backgroundColor="#d9534f";  document.getElementById("statusRelay4").innerHTML="OFF"; firebase.database().ref("'+user.uid+'/'+numberOfStations[i]+'/statusActuators").update({   RELAY4: 0 });}});             RELAY4.on("value", data => { if(data.val()=="1"){  relay4.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay4").innerHTML="ON"; $("#customSwitch4").prop("checked", true)}else{  relay4.style.backgroundColor="#d9534f"; document.getElementById("statusRelay4").innerHTML="OFF"; $("#customSwitch4").prop("checked", false)  }});}
     

 

// INITIALIZE HISTORICAL DATA

//for(var i = 0; i<numberOfStations.length; i++){
 let valueSensors = databasesensor.collection("SENSORS/'+ user.uid+'/'+numberOfStations[i]+'"); let query = valueSensors.get().then(snapshot => { temp_dataset=[];CO2_dataset=[];humidity_dataset=[];light_dataset=[];TVOC_dataset=[];pressure_dataset=[];wind_dataset=[];battery_dataset=[];chart_labels=[];numberOfStations =[];lat_dataset=[];long_dataset=[];dataSet_lat_long = [];if (snapshot.empty) {  console.log('No matching documents.');  return;}snapshot.forEach(doc => {chart_labels.push(doc.data().TIMESTAMP);temp_dataset.push(doc.get('TemperatureDHT22'));CO2_dataset.push(doc.get('CO2'));humidity_dataset.push(doc.get('HumidityDHT22'));TVOC_dataset.push(doc.get('TVOC'));pressure_dataset.push(doc.get('PressureBMP180'));battery_dataset.push(doc.get('battery'));// wind_dataset.push(doc.get('TemperatureDHT22'));light_dataset.push(doc.get('LIGHT'));});   })
.catch(err => {console.log('Error getting documents', err);});



RELAY4.on('value', data => { if(data.val()=='1'){  relay4.style.backgroundColor="#5cb85c";  document.getElementById("statusRelay4").innerHTML="ON"; $("#customSwitch4").prop("checked", true)}else{  relay4.style.backgroundColor="#d9534f"; 
    document.getElementById("statusRelay4").innerHTML="OFF"; $("#customSwitch4").prop("checked", false)  }});


// RELAY 3

$("#relay3").change(function() {
  if(relay3.style.backgroundColor =="rgb(217, 83, 79)"){   // SI ESTA EN ROJO
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
     RELAY3: 1
   });
  relay3.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay3").innerHTML="ON"
 }else{
   relay3.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay3").innerHTML="OFF"
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
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
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
     RELAY2: 1
   });
  relay2.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay2").innerHTML="ON"
 }else{
   relay2.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay2").innerHTML="OFF"
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
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
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
     RELAY1: 1
   });
  relay1.style.backgroundColor="#5cb85c"; // #5cb85c COLOR VERDE
  document.getElementById("statusRelay1").innerHTML="ON"
 }else{
   relay1.style.backgroundColor="#d9534f"; // #d9534f COLOR ROJO
   document.getElementById("statusRelay1").innerHTML="OFF"
   firebase.database().ref(user1+'/WHEATHER_1/statusActuators').update({
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

*/
