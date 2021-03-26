// RETRIEVE INFO

var userName=document.getElementById("userName");
var PhotoProfile=document.getElementById("PhotoProfile");


// Initialize the FirebaseUI Widget using Firebase.
var ui = new firebaseui.auth.AuthUI(firebase.auth());
var uiConfig = {
  callbacks: {
    signInSuccessWithAuthResult: function(authResult, redirectUrl) {
      // User successfully signed in.
      // Return type determines whether we continue the redirect automatically

var user = firebase.auth().currentUser;
console.log(user);
var name, email, photoUrl, uid, emailVerified;
  userName.innerHTML = '<strong>'+user.displayName+'</strong>';
  if(user.photoURL!= null){
   // email = user.email;
  PhotoProfile.src = user.photoURL;
  }
    //  firebase.auth.setPersistence(firebase.auth.Auth.Persistence.LOCAL);
      return true;
    },
    uiShown: function() {
      // The widget is rendered.
      // Hide the loader.
      document.getElementById('loader').style.display = 'none';
    }
  },
  // Will use popup for IDP Providers sign-in flow instead of the default, redirect.
  signInFlow: 'popup',
  signInSuccessUrl: 'https://wheather-station-18cb0.web.app/dashboard.html',
  signInOptions: [
    // Leave the lines as is for the providers you want to offer your users.
    firebase.auth.GoogleAuthProvider.PROVIDER_ID,
    firebase.auth.FacebookAuthProvider.PROVIDER_ID,
    firebase.auth.TwitterAuthProvider.PROVIDER_ID,
    firebase.auth.GithubAuthProvider.PROVIDER_ID,
    firebase.auth.EmailAuthProvider.PROVIDER_ID,
    firebase.auth.PhoneAuthProvider.PROVIDER_ID
  ],
  // Terms of service url.
  tosUrl: '<your-tos-url>',
  // Privacy policy url.
  privacyPolicyUrl: '<your-privacy-policy-url>'
};


// The start method will wait until the DOM is loaded.
ui.start('#firebaseui-auth-container', uiConfig);




window.onload = function() {
  
/*var user = firebase.auth().currentUser;
console.log(user);
var name, email, photoUrl, uid, emailVerified;

if (user != null) {
  userName = user.displayName;
  if(user.photoURL!= null){
   // email = user.email;
  PhotoProfile.src = user.photoURL;
  }
 // email = user.email;
 // emailVerified = user.emailVerified;
  //uid = user.uid;  // The user's ID, unique to the Firebase project. Do NOT use
                   // this value to authenticate with your backend server, if
                   // you have one. Use User.getToken() instead.
} */
}

