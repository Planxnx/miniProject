var db = firebase.database();//ใช้งานดาต้าเบส
    var a = "test4"
    
    //อัพข้อมูล A ไปที่ test/test2
    firebase.database().ref('test/test2/' ).set("A");  
    //อัพข้อมูลหลายๆข้อมูลไปที่ test/test3/test4
    firebase.database().ref('test/test3/' + a).set({
    testA: "ab",
    testB: "cd"});
    
    //อ่านข้อมูลจาก ReadTest แล้วแสดงผลใน console ว่า ok
    var b = firebase.database().ref('ReadTest/');//หรือ var b = db.ref('ReadTest');
    
    b.on('value', function(snapshot){ 
        var c = snapshot.val();
        console.log("Read Test "+ c );

    });