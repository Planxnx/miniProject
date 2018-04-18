var config = {
    apiKey: "AIzaSyCfUxVqAaobZHxwCeOFHJiAOKTFX4T-H6o",  
    authDomain: "miniproject-2560.firebaseapp.com",
    databaseURL: "https://miniproject-2560.firebaseio.com",
    projectId: "miniproject-2560",
    storageBucket: "miniproject-2560.appspot.com",
    messagingSenderId: "833789294851"
  };
  firebase.initializeApp(config);
  
  //auth การรับรองสิทธ
  /*firebase.auth().signInWithEmailAndPassword("admin@test.com", "123456789").catch(function(error) {
    // Handle Errors here.
    var errorCode = error.code;
    var errorMessage = error.message;
    
    // ...
  });*/