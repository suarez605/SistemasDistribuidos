// Implementación de la interfaz de servidor que define los métodos remotos
// para completar la descarga de un fichero
package afs;
import java.io.*;

import java.rmi.*;
import java.rmi.server.*;

public class ViceReaderImpl extends UnicastRemoteObject implements ViceReader {
    /**
     *
     */
    //private static final long serialVersionUID = 1L;
    private static final String AFSDir = "AFSDir/";
    private RandomAccessFile files;

    public ViceReaderImpl(String file, String str) throws RemoteException, FileNotFoundException {
        files = new RandomAccessFile(AFSDir + file, str);
    }

    public byte[] read(int tam) throws RemoteException, IOException {
        byte[] arrBy = new byte[tam];
        int readBy = files.read(arrBy);
        if(readBy == -1) {
            return null;
        } else if(readBy < tam) {
            byte [] arrBy2 = new byte[readBy];
            for(int i = 0; i < readBy; i++){
                arrBy2[i]=arrBy[i];
            }
            return arrBy2;
        }
        return arrBy;
    }

    public void close() throws RemoteException, IOException {
        files.close();
    }
}

