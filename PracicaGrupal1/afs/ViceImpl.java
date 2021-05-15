// Implementación de la interfaz de servidor que define los métodos remotos
// para iniciar la carga y descarga de ficheros
package afs;
import java.io.*;
import java.rmi.*;
import java.rmi.server.*;

public class ViceImpl extends UnicastRemoteObject implements Vice {
  
  //private static final long serialVersionUID = 1L;

  public ViceImpl() throws RemoteException {}

  public ViceReader download(String file, String str) throws RemoteException, FileNotFoundException {
      ViceReader vicReader = new ViceReaderImpl(file, str);
      return vicReader;
  }

  public ViceWriter upload(String file, String str) throws RemoteException, FileNotFoundException {
      ViceWriter vicWriter = new ViceWriterImpl(file, str);
      return vicWriter;
  }
}