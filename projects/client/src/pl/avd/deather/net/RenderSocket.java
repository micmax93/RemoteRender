package pl.avd.deather.net;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Date;

public class RenderSocket {
  private static final int MAX_DELAY = 1000 * 10; // 10 secs
  private final Socket socket;
  private boolean interrupted = false;
  private int bufferSize;


//  c -> NEW_CLIENT_REQ
//  s -> BUF_SIZE
//  c -> xml_total_size
//  s -> xml_count
//  c -> xml_data[]
//  s -> jpg_total_size or {0,-1,...} if error
//  c -> jpg_count
//  s -> jpg_data[]

  public RenderSocket(Socket socket) throws InterruptException {
    this.socket = socket;
    readBufferSize();
  }

  private void readBufferSize() throws InterruptException {

    try {
      InputStream is = socket.getInputStream();
      DataInputStream dis = new DataInputStream(is);
      waitForData(4, MAX_DELAY);
      bufferSize = dis.readInt();
    } catch (IOException e) {
      throw new InterruptException("Interrupted.");
    }
  }

  public void sendXml(String xml) throws InterruptException {
    try {
      InputStream is = socket.getInputStream();
      OutputStream os = socket.getOutputStream();
      byte[] data = xml.getBytes("US-ASCII");
      int expectedCheckSum = (int) Math.ceil((double) data.length / (double) bufferSize);

      writeInt(data.length);
      int checkSum = readInt();

      if (checkSum != expectedCheckSum) {
        throw new InterruptException("Received checksum is different.");
      }

      os.write(data);
    } catch (IOException e) {
      throw new InterruptException("Interrupted.");
    }
  }

  public byte[] getImageBytes() throws InterruptException {
    try {
      int imageSize = readInt();
      int num = (int) Math.ceil((double) imageSize / (double) bufferSize);
      writeInt(num);

      InputStream is = socket.getInputStream();

      ByteArrayOutputStream baos = new ByteArrayOutputStream();

      int total = 0;
      int n;
      byte[] buffer = new byte[bufferSize];


      long timer = getTime();
      while (total < imageSize && ((n = is.read(buffer)) > 0)) {
        if(getTime() - timer > MAX_DELAY) {
          throw new InterruptException("Max delay exceed.");
        }
        timer = getTime();
        baos.write(buffer, 0, num);
        total += num;
      }
      return baos.toByteArray();
    } catch (IOException e) {
      throw new InterruptException("Image not received.");
    }
  }

  private void waitForData(int size, long delay) throws IOException, InterruptException {
    InputStream is = socket.getInputStream();
    long start = getTime();
    long cur;
    while (is.available() < size) {
      cur = getTime();
      if (cur - start > delay) {
        throw new InterruptException("Exception thrown due to delay.");
      }
    }
  }

  private void writeInt(int value) throws IOException {
    OutputStream os = socket.getOutputStream();
    ByteBuffer bb = ByteBuffer.allocate(4);
    bb.putInt(value);
    os.write(bb.array());
  }

  private int readInt() throws IOException, InterruptException {
    InputStream is = socket.getInputStream();
    DataInputStream dis = new DataInputStream(is);
    waitForData(4, MAX_DELAY);
    return dis.readInt();
  }

  public boolean isInterrupted() {
    return interrupted;
  }

  private long getTime() {
    return new Date().getTime();
  }
}
