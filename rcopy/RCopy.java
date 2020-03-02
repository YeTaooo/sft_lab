import java.io.*;
import java.util.Arrays;
import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
public class RCopy
{
    static int BUFFER_SIZE = 1024;
	public static void main(String[] args) {
       // public static int BUFFER_SIZE = 10;
        try{
            RandomAccessFile inFile = new RandomAccessFile(args[0],"r");
            FileOutputStream outStream = new FileOutputStream(args[1]);
            byte[] buffer = new byte[BUFFER_SIZE];
            byte[] buffer2 =new byte[BUFFER_SIZE];
            long length=0;
            long m, n;
            int i=0,j=0,pos=1;
            byte ch;
            length = inFile.length();
            if(length==0){
                System.out.println("empty File");
                System.exit(0);
            }
            System.out.println(length);
            n = length/BUFFER_SIZE;
            m = length%BUFFER_SIZE;
            int bytesRead;
            
            if(n==0)
            {
                bytesRead = inFile.read(buffer);
                //System.out.println(Arrays.toString(buffer));
                for(i=(int)length-1; i>=0;i--)
                {
                    buffer2[j]=buffer[i];
                    //System.out.println('__'+buffer2[j]);
                    j = j + 1;
                }
                outStream.write(buffer2, 0, bytesRead);
            }
            else{
                do{
                    inFile.seek(length-BUFFER_SIZE*pos);//length-Buffer_SIZE
                    bytesRead = inFile.read(buffer);
                    //System.out.println(bytesRead);
                    //System.out.println(Arrays.toString(buffer));
                    j=0;
                    for(i=BUFFER_SIZE-1; i>=0;i--)
                    {
                        buffer2[j]=buffer[i];
                        j = j+1;
                    }
                    outStream.write(buffer2);
                    
                    pos = pos+1;
                }while(pos<=n);
                if(m!=0){
                    inFile.seek(0);
                    length = m;
                    bytesRead = inFile.read(buffer);
                    System.out.println(Arrays.toString(buffer));
                    j=0;
                    for(i=(int)length-1; i>=0;i--)
                    {
                        buffer2[j]=buffer[i];
                        j = j+1;
                        //System.out.println('__'+buffer2[j]);
                    }
                    pos = (int)m;
                    outStream.write(buffer2,0,pos);
                    System.out.println(Arrays.toString(buffer2));
                }
                
            }
            
            inFile.close();
            outStream.close();
        }catch(IOException e){
            System.out.println("IO-Exception while " + e.toString());
        }
	}
}
