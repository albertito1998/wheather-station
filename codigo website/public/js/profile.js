var userName=document.getElementById("userName");
var emailUser=document.getElementById("emailUser");
var changePassword=document.getElementById("changePassword");

var PhotoProfile=document.getElementById("PhotoProfile");
const verified=document.querySelectorAll('.verified');
const nonverified = document.querySelectorAll('.nonverified');
var numberOfStations=[];
// Get element references
var insertList = document.getElementById('insertList');


firebase.auth().onAuthStateChanged((user) => {
    if (user) {
     console.log(user);
    userName.innerHTML = '<strong>'+user.displayName+'</strong>';
    emailUser.innerHTML = '<strong>'+user.email+'</strong>';
    if(user.photoURL!= null){
     // email = user.email;
    PhotoProfile.src = user.photoURL;
}
    if(user.emailVerified){
        verified.forEach(item=>item.style.display = 'block');
nonverified.forEach(item=>item.style.display = 'none');
     
    }


    firebase.database().ref(user.uid).on('value', snapshot => {  // user.uid

      numberOfStations = Object.keys(snapshot.val());
      console.log(Object.keys(snapshot.val()));
      var contenido;
      for(var i = 0; i<numberOfStations.length; i++){
        contenido = contenido + `<li class="list-group-item list-group-item-light" >
        <div class="mr-10">
           <div>
                <div class="small text-gray-500">${numberOfStations[i]}</div>
                <span class="font-weight-bold">STATUS ON</span>
            </div> 
        </div>
        <div class="mr-2">
        <a href="#" class="btn btn-success btn-circle">
                                            <i class="fas fa-check"></i>
         </a>
        </div> 
    </li>`; 
      }
      insertList.innerHTML=contenido;
      });

      modify.addEventListener('submit',(e) =>{
        e.preventDefault();
        // get user info
        const newName=modify['nameChange'].value;
        const password=modify['photoChange'].value;
      
      user.updateProfile({
        displayName:  newName,
       // photoURL: "https://example.com/jane-q-user/profile.jpg"
      }).then(function() {
        // Update successful.
      }).catch(function(error) {
        // An error happened.
      }); 
      
      })
   
  
    } else {
      // User is signed out
      // ...
    }
  });

$("#changePassword").click(function() {
    auth.sendPasswordResetEmail(user.email).then(function() {
        // Email sent.
      }).catch(function(error) {
        // An error happened.
      });
  
    });

$("#sendEmail").click(function() {
    user.sendEmailVerification().then(function() {
        // Email sent.
        $('#element').toast('show');
      }).catch(function(error) {
        // An error happened.
      });
  
    });

