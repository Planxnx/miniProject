/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package plant.monitor;

/**
 *
 * @author 60010465
 */
public class PlantMonitor {
    public static void main(String[] args) {
        FileInputStream serviceAccount = new FileInputStream("path/to/serviceAccountKey.json");

    FirebaseOptions options = new FirebaseOptions.Builder()
    .setCredentials(GoogleCredentials.fromStream(serviceAccount))
    .setDatabaseUrl("https://<DATABASE_NAME>.firebaseio.com/")
    .build();

    FirebaseApp.initializeApp(options);
   
        
        FirebaseApp.initializeApp();
    }
    
}
