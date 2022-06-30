


var title=document.getElementById('chart-title')

var parameter=document.getElementById("parameter");
var day_max=document.getElementById("max_day");
var max_value=document.getElementById("max_value");
var average=document.getElementById("average");
var suma, media, valuemax, daymax;
var dateStringStart;
var dateStringEnd;

const temperatureCanvasCtx = document.getElementById('temperature-chart').getContext('2d')
const LineChart = {
  type: 'line',
  data: {
    labels: [],
    datasets: [{
      data: [],
      backgroundColor: 'rgba(255, 205, 210, 0.5)'
    }]
  },
  options: {
    legend: {
      display: false
    },
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      yAxes: [{
        gridLines: {
          display: true
      },
        ticks: {
          suggestedMin: 0,
          suggestedMax: 100
        },
      }]
    },
  }
}

const valuesChart = new Chart(temperatureCanvasCtx, LineChart)

const pushData = (arr, value) => {
  arr.push(value)
}

 
  


$("#0").click(function() {
  suma=0, media=0, valuemax=0, daymax=0;
  LineChart.data.datasets[0].data= temp_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Temperature ºC";
  parameter.innerHTML="TEMPERATURE ºC"

for (let step = 0; step < temp_dataset.length; step++) {
  if(valuemax <temp_dataset[step]){
    valuemax= temp_dataset[step];
    daymax=chart_labels[step];
  }

  suma += temp_dataset[step];
}


media= suma/temp_dataset.length;
average.innerHTML = '<strong>' + media + '</strong>'
max_value.innerHTML = '<strong>' +valuemax + '</strong>'
day_max.innerHTML = '<strong>' + daymax + '</strong>'
  valuesChart.update();
});
$("#1").click(function() {
  LineChart.data.datasets[0].data= humidity_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Humidity %";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="HUMIDITY %"
  for (let step = 0; step < humidity_dataset.length; step++) {
    if(valuemax <humidity_dataset[step]){
      valuemax= humidity_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += humidity_dataset[step];
  }
  
  
  media= suma/humidity_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});
$("#2").click(function() {
  LineChart.data.datasets[0].data= CO2_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "CO2 ppm";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="CO2 ppm"
  for (let step = 0; step < CO2_dataset.length; step++) {
    if(valuemax <CO2_dataset[step]){
      valuemax= CO2_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += CO2_dataset[step];
  }
  
  
  media= suma/CO2_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'
});
$("#3").click(function() {
  LineChart.data.datasets[0].data= TVOC_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "TVOC ppm";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="TVOC ppm"
  for (let step = 0; step < TVOC_dataset.length; step++) {
    if(valuemax <TVOC_dataset[step]){
      valuemax= TVOC_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += TVOC_dataset[step];
  }
  
  
  media= suma/TVOC_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'
});
$("#4").click(function() {
  LineChart.data.datasets[0].data= pressure_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Pressure Pa";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="PRESSURE [PA]"
  for (let step = 0; step < pressure_dataset.length; step++) {
    if(valuemax <pressure_dataset[step]){
      valuemax= pressure_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += pressure_dataset[step];
  }
  
  
  media= suma/pressure_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'
});
$("#5").click(function() {
  LineChart.data.datasets[0].data= light_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "LIGHT lux";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="LIGHT (lux)"
  for (let step = 0; step < light_dataset.length; step++) {
    if(valuemax <light_dataset[step]){
      valuemax=light_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += light_dataset[step];
  }
  
  
  media= suma/light_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'
});
$("#6").click(function() {
  LineChart.data.datasets[0].data= wind_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Wind m/s";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="LIGHT (lux)"
  for (let step = 0; step < wind_dataset.length; step++) {
    if(valuemax <wind_dataset[step]){
      valuemax=wind_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += wind_dataset[step];
  }
  
  
  media= suma/wind_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'
});

$("#7").click(function() {
  LineChart.data.datasets[0].data= battery_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Battery V";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="BATTERY V"
  for (let step = 0; step < humidity_dataset.length; step++) {
    if(valuemax <battery_dataset[step]){
      valuemax= battery_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += battery_dataset[step];
  }
  
  
  media= suma/battery_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});

$("#8").click(function() {
  LineChart.data.datasets[0].data= waterLevel_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Rain L/M<sub>2</sub>";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="Rain L/M<sub>2</sub>"
  for (let step = 0; step < waterLevel_dataset.length; step++) {
    if(valuemax <waterLevel_dataset[step]){
      valuemax= waterLevel_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += waterLevel_dataset[step];
  }
  
  
  media= suma/waterLevel_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});

$("#9").click(function() {
  LineChart.data.datasets[0].data= uv_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "UV Indicator";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="UV Indicator"
  for (let step = 0; step < uv_dataset.length; step++) {
    if(valuemax <uv_dataset[step]){
      valuemax= uv_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += uv_dataset[step];
  }
  
  
  media= suma/uv_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});


$("#10").click(function() {
  LineChart.data.datasets[0].data= watts_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Watts solar panel (mW)";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="Watts solar panel (mW)"
  for (let step = 0; step < watts_dataset.length; step++) {
    if(valuemax <watts_dataset[step]){
      valuemax= watts_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += watts_dataset[step];
  }
  
  
  media= suma/watts_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});


$("#11").click(function() {
  LineChart.data.datasets[0].data= current_dataset;
  LineChart.data.labels = chart_labels;
  title.innerHTML= "Current solar panel (mA)";
  valuesChart.update();
  suma=0, media=0, valuemax=0, daymax=0;
  parameter.innerHTML="Current solar panel (mA)"
  for (let step = 0; step < current_dataset.length; step++) {
    if(valuemax <current_dataset[step]){
      valuemax= current_dataset[step];
      daymax=chart_labels[step];
    }
  
    suma += current_dataset[step];
  }
  
  
  media= suma/current_dataset.length;
  average.innerHTML = '<strong>' + media + '</strong>'
  max_value.innerHTML = '<strong>' +valuemax + '</strong>'
  day_max.innerHTML = '<strong>' + daymax + '</strong>'

});

     
/*
$("#Submitpicker").click(function() {

dateStringStart = $("#datetimepicker1").val();
dateStringEnd = $("#datetimepicker2").val();


    dateArgs1 = dateStringStart.match(/\d{2,4}/g),
    year1 = dateArgs1[2],
    month1 = parseInt(dateArgs1[1]) - 1,
    day1 = dateArgs1[0],
    hour1 = dateArgs1[3],
    minutes1 = dateArgs1[4];
    dateArgs = dateStringEnd.match(/\d{2,4}/g),
    year = dateArgs[2],
    month = parseInt(dateArgs[1]) - 1,
    day = dateArgs[0],
    hour = dateArgs[3],
    minutes = dateArgs[4];
    var Startdate = new Date(year1, month1, day1, hour1, minutes1).getTime();
    var Enddate = new Date(year, month, day, hour, minutes).getTime();
    cleanArray ();

    let consulta = databasesensor.collection("SENSORS/ViF2hDkYzkTO5SySGrFzyB3Mk4A2/WHEATHER_1").where('timestamp', '>=', Startdate/1000).where('timestamp', '<=', Enddate/1000).get()
      .then(snapshot => {
        if (snapshot.empty) {
          console.log("No matching documents.");
          return;
                }
        snapshot.forEach(doc => {
    chart_labels.push(doc.data().TIMESTAMP);
     temp_dataset.push(doc.get("TemperatureDHT22"));
     CO2_dataset.push(doc.get("CO2"));
     humidity_dataset.push(doc.get("HumidityDHT22"));
     TVOC_dataset.push(doc.get("TVOC"));
     pressure_dataset.push(doc.get("PressureBMP180"));
     battery_dataset.push(doc.get("batteryLevel"));
    wind_dataset.push(doc.get("TemperatureDHT22"));
    light_dataset.push(doc.get("LIGHT"));
      });  
        })
    .catch(err => {
      console.log("Error getting documents", err);
    });

  });

  function cleanArray (){
 temp_dataset=[],CO2_dataset=[],humidity_dataset=[], light_dataset=[], TVOC_dataset=[], pressure_dataset=[], wind_dataset=[], battery_dataset=[], chart_labels=[];
  }

 
'document.getElementById("Submitpicker").addEventListener("click", function() { dateStringStart = $("#datetimepicker1").val();dateStringEnd = $("#datetimepicker2").val(); dateArgs1 = dateStringStart.match(/\d{2,4}/g),  year1 = dateArgs1[2],  month1 = parseInt(dateArgs1[1]) - 1,  day1 = dateArgs1[0],  hour1 = dateArgs1[3],  minutes1 = dateArgs1[4];  dateArgs = dateStringEnd.match(/\d{2,4}/g), year = dateArgs[2], month = parseInt(dateArgs[1]) - 1, day = dateArgs[0], hour = dateArgs[3], minutes = dateArgs[4]; var Startdate = new Date(year1, month1, day1, hour1, minutes1).getTime(); var Enddate = new Date(year, month, day, hour, minutes).getTime(); cleanArray ();  if($(".btn_1").val()=== '+numberOfStations[i]+'){ let consulta = databasesensor.collection("SENSORS/'+user.uid+'/'+numberOfStations[i]+'").where("timestamp", ">=", Startdate/1000).where("timestamp", "<=", Enddate/1000).get()   .then(snapshot => {  if (snapshot.empty) {  console.log("No matching documents.");  return;        }; snapshot.forEach(doc => {chart_labels.push(doc.data().TIMESTAMP); temp_dataset.push(doc.get("TemperatureDHT22")); CO2_dataset.push(doc.get("CO2"));humidity_dataset.push(doc.get("HumidityDHT22"));TVOC_dataset.push(doc.get("TVOC"));pressure_dataset.push(doc.get("PressureBMP180"));battery_dataset.push(doc.get("batteryLevel"));wind_dataset.push(doc.get("TemperatureDHT22"));light_dataset.push(doc.get("LIGHT"));  });      }).catch(err => {  console.log("Error getting documents", err);});}   }); function cleanArray (){ temp_dataset=[],CO2_dataset=[],humidity_dataset=[], light_dataset=[], TVOC_dataset=[], pressure_dataset=[], wind_dataset=[], battery_dataset=[], chart_labels=[]; }'

 */

