// Implementación de la interfaz de cliente que define los métodos remotos
// para gestionar callbacks
package afs;

import java.rmi.*;
import java.rmi.server.*;

//private static final long serialVersionUID = 1L;

public class VenusCBImpl extends UnicastRemoteObject implements VenusCB {
    public VenusCBImpl() throws RemoteException {
    }
    public void invalidate(String fileName /* añada los parámetros que requiera */)
        throws RemoteException {
        return;
    }
}

