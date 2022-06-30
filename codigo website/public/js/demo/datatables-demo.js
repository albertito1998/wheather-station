var userName=document.getElementById("userName");
var PhotoProfile=document.getElementById("PhotoProfile");
  //INIT OF CODE
  function logOut(){
    firebase.auth().signOut().then(() => {
      // Sign-out successful.
    }).catch((error) => {
      // An error happened.
    });
    }




// Call the dataTables jQuery plugin
$(document).ready(function() {
  firebase.auth().onAuthStateChanged((user) => {
    if (user) {
    userName.innerHTML = '<strong>'+user.displayName+'</strong>';
    if(user.photoURL!= null){
     // email = user.email;
    PhotoProfile.src = user.photoURL;
    }
 //------------------------QUERY OF TABLE-----------------------
  let valueSensors = firebase.firestore().collection('SENSORS/'+user.uid+'/WHEATHER_1'); // user.uid
  var valores;
  let datos = [];
  let query = valueSensors.get()
    .then(snapshot => {
      if (snapshot.empty) {
        console.log('No matching documents.');
        return;
      }
      snapshot.forEach(doc => {
       
  datos.push(doc.data());
          }); 
          var table =  $('#dataTable').DataTable( {
           
            data: datos,
            columns: [
              { data: 'TIMESTAMP' },
              { data: 'CO2' },
              { data: 'DIRECTION' },
              { data: 'HumidityDHT22'},{ data: 'LIGHT'},
              { data: 'TVOC'},
              { data: 'PressureBMP180'},
              { data: 'TemperatureBMP180'},
              { data: 'TemperatureDHT22'},
              { data: 'WIND'},
              { data: 'battery'}
            ],
            buttons: [
              'copy', 'csv', 'print',
              {
                  extend: 'excel',
                  text: 'Export Excel',
                  sheetName: 'EXCEL_REPORT_'+ new Date().toString(),
                  exportOptions: {
                      modifier: {
                          page: 'current'
                      }
                  }
              },

              {
                extend: 'pdf',
                text: 'Export PDF',
                filename: 'PDF_REPORT_'+ new Date().toString(),
                exportOptions: {
                    modifier: {
                        page: 'current'
                    }
                }
            },
            {
              extend: 'print',
              text: 'PRINT PDF',
              filename: 'PRINT_'+ new Date().toString(),
              exportOptions: {
                  modifier: {
                      page: 'current'
                  }
              }
          },
          ]
         
        } );
        table.buttons().container().appendTo( $('.col-sm-6:eq(0)', table.table().container() ) );
      })
  .catch(err => {
    console.log('Error getting documents', err);
  });
  
}
})
});
