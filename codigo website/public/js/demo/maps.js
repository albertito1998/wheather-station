


anychart.onDocumentReady(function() {
    // create map
    var map = anychart.map();
  
    // create data set
    var dataSet = anychart.data.set(
        [{"id":"ES.PV","value":0},
              {"id":"ES.CM","value":1},
              {"id":"ES.VC","value":2},
              {"id":"ES.AN","value":3},
              {"id":"ES.AS","value":4},
              {"id":"ES.CL","value":5},
              {"id":"ES.EX","value":6},
              {"id":"ES.PM","value":7},
              {"id":"ES.CT","value":8},
              {"id":"ES.7247","value":9},
              {"id":"ES.7269","value":10},
              {"id":"ES.7272","value":11},
              {"id":"ES.CB","value":12},
              {"id":"ES.7263","value":13},
              {"id":"ES.CE","value":14},
              {"id":"ES.393","value":15},
              {"id":"ES.392","value":16},
              {"id":"ES.7267","value":17},
              {"id":"ES.7261","value":18},
              {"id":"ES.7275","value":19},
              {"id":"ES.7266","value":20},
              {"id":"ES.7257","value":21},
              {"id":"ES.7271","value":22},
              {"id":"ES.AR","value":23},
              {"id":"ES.7274","value":24},
              {"id":"ES.GA","value":25},
              {"id":"ES.LO","value":26},
              {"id":"ES.CN","value":27},
              {"id":"ES.7255","value":28},
              {"id":"ES.7260","value":29},
              {"id":"ES.7244","value":30},
              {"id":"ES.MD","value":31},
              {"id":"ES.7273","value":32},
              {"id":"ES.1305","value":33},
              {"id":"ES.MU","value":34},
              {"id":"ES.NA","value":35},
              {"id":"ES.7246","value":36},
              {"id":"ES.7254","value":37},
              {"id":"ES.7245","value":38},
              {"id":"ES.7251","value":39},
              {"id":"ES.3626","value":40},
              {"id":"ES.7249","value":41},
              {"id":"ES.7270","value":42},
              {"id":"ES.7248","value":43},
              {"id":"ES.7262","value":44},
              {"id":"ES.7259","value":45},
              {"id":"ES.7265","value":46},
              {"id":"ES.3493","value":47},
              {"id":"ES.7253","value":48},
              {"id":"ES.7256","value":49},
              {"id":"ES.7252","value":50},
              {"id":"ES.3491","value":51}]
    );
    // create the dataset of points that are defined by latitude and longtitude values
   /*  
   var  dataSet_lat_long =[ 
        {lat: 40.416775, long: -3.703790},
           ];
          */  
  
    // create choropleth series
    series = map.choropleth(dataSet);
  
    // set geoIdField to 'id', this field contains in geo data meta properties
    series.geoIdField('id');
  
    // set map color settings
    series.colorScale(anychart.scales.linearColor('#deebf7', '#3182bd'));
    series.hovered().fill('#addd8e');
  
    // set geo data, you can find this map in our geo maps collection
    // https://cdn.anychart.com/#maps-collection
    map.geoData(anychart.maps['spain']);

       // Creates the marker series
       var series_lat_long = map.marker(dataSet_lat_long);
       series_lat_long.tooltip({title: false, separator: false});
   
       map.title("Location Wheather Stations");
  
    //set map container id (div)
    map.container('container');
  
    //initiate map drawing
    map.draw();
  });