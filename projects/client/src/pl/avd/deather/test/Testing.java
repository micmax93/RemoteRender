package pl.avd.deather.test;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Testing {
  public Testing() {
//    1) łączysz się ze mną
//    2) wysyłasz 1 bajt (char w cpp) = '#'
//    3) wysyłam tobie rozmiar całości w bajtach (jako int 4B)
//    4) wysyłam rozmiar bufora w bajtach (jako int 4B)
//    5) ty mi odpisujesz ile buforów powinieneś odebrać - czyli dzielisz total/buf zaokrąglając w górę (int 4B)
//    6) wysyłam ci bufory
  }

  public void run() throws UnsupportedEncodingException {
    String msg = "#";
    byte initCharacters[] = msg.getBytes("US-ASCII");

    Socket s = null;
    OutputStream os;
    InputStream is;

    try {
      s = new Socket("micmax93.pl", 55555);

      log("Connected to " + s.getInetAddress().toString());
      os = s.getOutputStream();
      is = s.getInputStream();


      os.write(initCharacters);
      waitAndCountData(is, 5);

      DataInputStream dis = new DataInputStream(is);
      int size = dis.readInt();
      int bufferSize = dis.readInt();
      log("size = " + size + ", bufferSize = " + bufferSize);

      int maxPackets = (int) Math.ceil((double) size / (double) bufferSize);
      DataOutputStream dos = new DataOutputStream(os);
      ByteBuffer bb = ByteBuffer.allocate(4);
      bb.putInt(maxPackets);
      os.write(bb.array());

      log("sent num packets = " + maxPackets);


      s.setReceiveBufferSize(size * 2);
      log("max buffer size = " + s.getReceiveBufferSize());

      int total = 0;
      int count = 0;
      byte buffer[] = new byte[bufferSize];
      FileOutputStream fos = new FileOutputStream("test.jpg");
      while(total < size && ((count = is.read(buffer)) > 0)) {
        fos.write(buffer, 0, count);
        total += count;
      }
      fos.close();

      s.close();
    } catch (IOException e) {
      log(e.toString());
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  public int waitAndCountDataSize(InputStream is, int sizeExpected, int maxSecs) throws IOException, InterruptedException {
    int mul = 500;
    maxSecs *= mul;
    while (maxSecs > 0) {
      maxSecs--;
      if (is.available() >= sizeExpected) {
        break;
      }
      Thread.sleep(1000 / mul);
    }
    return is.available();
  }

  public int waitAndCountData(InputStream is, int maxSecs) throws IOException, InterruptedException {
    maxSecs *= 5;
    while (maxSecs > 0) {
      maxSecs--;
      if (is.available() > 0) {
        break;
      }
      Thread.sleep(200);
    }
    return is.available();
  }

  public void log(String msg) {
    System.out.println(msg);
  }

  public static void main(String[] args) {
    try {
      new Testing().run();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    }
  }
}
