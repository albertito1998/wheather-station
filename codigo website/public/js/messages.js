var count_messages=0;
var messages_content=document.getElementById("messages_content");
var messages_number=document.getElementById("new_messages");
var previo={};

let valueMessages = firebase.firestore().collection("MESSAGES").doc("bzjXdYrrUBndTpNFugB7");
 let query = valueMessages.get()
 .then(doc=> {
   if (doc.empty) {
     console.log('No matching documents.');
     return;
   }
   Object.keys(doc.data()).forEach((name) => {
    messages_content.innerHTML=  '<a class="dropdown-item d-flex align-items-center" href="#"><div class="mr-3"><div class="icon-circle bg-primary"> <i class="fas fa-file-alt text-white"></i></div></div><div><div class="small text-gray-500">'+name+'</div><span class="font-weight-bold">'+doc.data()[name] +'"</span></div></a>'
   });  
   })
 .catch(err => {
 console.log('Error getting documents', err);
 });


 firebase.firestore().collection("MESSAGES").doc("bzjXdYrrUBndTpNFugB7")
 .onSnapshot((doc) => {
            if (Object.keys(doc.data()) != Object.keys(previo)) {
                count_messages=Object.keys(doc.data()).length-Object.keys(previo).length;
                messages_number.innerHTML=count_messages;
            }
            previo=doc.data();

        });
   

function countZero(){
    count_messages=0;
    messages_number.innerHTML=count_messages;
}