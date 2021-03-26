const temperatureCanvasCtx = document.getElementById('temperature-chart').getContext('2d')
var title=document.getElementById('chart-title')
var temp_dataset=[];
var CO2_dataset=[];
var humidity_dataset=[];
var light_dataset=[];
var TVOC_dataset=[];
var pressure_dataset=[];
var wind_dataset=[];
var chart_labels=[];
var parameter=document.getElementById("parameter");
var day_max=document.getElementById("max_day");
var max_value=document.getElementById("max_value");
var average=document.getElementById("average");
var suma, media, valuemax, daymax;

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
        ticks: {
          suggestedMin: 10,
          suggestedMax: 40
        },
      }]
    },
  }
}

const valuesChart = new Chart(temperatureCanvasCtx, LineChart)

const pushData = (arr, value) => {
  arr.push(value)
}

let valueSensors = databasesensor.collection('SENSORS');
let query = valueSensors.get()
  .then(snapshot => {
    if (snapshot.empty) {
      console.log('No matching documents.');
      return;
    }
    snapshot.forEach(doc => {
chart_labels.push(doc.data().TIMESTAMP);
 temp_dataset.push(doc.get('TemperatureDHT22'));
 CO2_dataset.push(doc.get('CO2'));
 humidity_dataset.push(doc.get('HumidityDHT22'));
 TVOC_dataset.push(doc.get('TVOC'));
 pressure_dataset.push(doc.get('PressureBMP180'));
// wind_dataset.push(doc.get('TemperatureDHT22'));
light_dataset.push(doc.get('LIGHT'));

  });  
    })
.catch(err => {
  console.log('Error getting documents', err);
});

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

