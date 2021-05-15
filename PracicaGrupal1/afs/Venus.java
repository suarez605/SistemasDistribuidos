// Clase de cliente que inicia la interacción con el servicio de
// ficheros remotos
package afs;

import java.rmi.*; 

public class Venus {

    private Vice srVic;
    private String tamano;
    
    public Venus() {
        try {
            this.tamano = System.getenv("BLOCKSIZE");
            String host = System.getenv("REGISTRY_HOST");
            String port = System.getenv("REGISTRY_PORT");
            this.srVic = (Vice) Naming.lookup("//" + host + ":" + port + "/AFS");
        } catch(RemoteException e){
            System.err.println("Error: " + e.toString());
        } catch(Exception e1) {
            e1.printStackTrace();
        }
    }

    public Vice getSrVic() {
        return this.srVic;
    }

    public String getTamano() {
        return this.tamano;
    }
}