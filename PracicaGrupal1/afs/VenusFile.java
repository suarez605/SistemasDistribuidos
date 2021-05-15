// Clase de cliente que define la interfaz a las aplicaciones.
// Proporciona la misma API que RandomAccessFile.
package afs;

import java.rmi.*; 
import java.io.*; 

public class VenusFile {

    public static final String cacheDir = "Cache/";
    public boolean size;
    public boolean write;
    public String mode;
    public String fileName;
    public Venus venus;
    public RandomAccessFile files;
    

    public VenusFile(Venus venus, String fileName, String mode) throws RemoteException, IOException, FileNotFoundException {

        this.mode = mode;
        this.fileName = fileName;
        this.venus = venus;
        if (mode.equals("rw")) {
            if (existeEnCache(fileName)) {
                files = new RandomAccessFile(cacheDir + fileName, mode);
            } else {
                files = copiarDeCache(venus, fileName, mode);
            }
        } else if (mode.equals("r")) {
            try {
                files = new RandomAccessFile(cacheDir + fileName, mode);    
            } catch (FileNotFoundException e) {
                files = copiarDeCache(venus, fileName, mode);
            }
            
        }
    }
    public int read(byte[] b) throws RemoteException, IOException {
        return files.read(b);
    }

    public void write(byte[] b) throws RemoteException, IOException {
        write = true;
        files.write(b);
    }

    public void seek(long p) throws RemoteException, IOException {
        files.seek(p);
    }

    public void setLength(long l) throws RemoteException, IOException {
        size = true;
        files.setLength(l);
    }

    public void close() throws RemoteException, IOException {
        if (this.mode.equals("rw")) {
            if (this.write) {
                ViceWriter viceWriter = venus.getSrVic().upload(this.fileName, this.mode);
                int blockSize = Integer.parseInt(venus.getTamano());
                byte[] buf = new byte[blockSize];
                files.seek(0);
                int bytesRead = 0;
                while((bytesRead = files.read(buf)) != -1) {
                    if (bytesRead < blockSize) {
                        byte [] dest2 = new byte[bytesRead];
                        for(int i=0;i<bytesRead;i++){
                            dest2[i]=buf[i];
                        }
                        viceWriter.write(dest2);
                    } else {
                        viceWriter.write(buf);
                    }
                }
                if (this.size) {
                    viceWriter.setLength(files.length());
                }
                viceWriter.close();
            } else if (this.size) {
                ViceWriter viceWriter = venus.getSrVic().upload(this.fileName, this.mode);
                viceWriter.setLength(files.length());
                viceWriter.close();
            }
        }
        files.close();
    }

    private RandomAccessFile copiarDeCache(Venus venus, String fileName, String mode) throws IOException, RemoteException, FileNotFoundException{
        ViceReader viceReader = venus.getSrVic().download(fileName, mode);
        RandomAccessFile fichero = new RandomAccessFile(cacheDir + fileName, "rw");
        int blockSize = Integer.parseInt(venus.getTamano());
        byte[] buf;
        while ((buf = viceReader.read(blockSize)) != null) {
            fichero.write(buf);
        }
        fichero.close();
        viceReader.close();
        return new RandomAccessFile(cacheDir + fileName, mode);
    }

    private boolean existeEnCache(String filename) {
        File f = new File(cacheDir);
        File[] files = f.listFiles();
        for (File file : files) {
            if (file.getName().equals(filename)) {
                return true;
            }
        }
        return false;
    }

}

