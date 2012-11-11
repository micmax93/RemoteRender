package pl.avd.deather.socket;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class TimeRequest {
  private String ip;
  private String port;


  public TimeRequest(String ip, String port) {
    this.ip = ip;
    this.port = port;
  }

  public String getResponse() {
    StringBuilder sb = new StringBuilder();
    Socket sock = null;

    try {
      sock = new Socket(ip, Integer.valueOf(port));
      Scanner s = new Scanner(sock.getInputStream());
      while (s.hasNext()) {
        sb.append(s.next());
      }
      sock.close();
    } catch (IOException e) {
      sb.append(e.toString());
    } catch(NumberFormatException e) {
      sb.append("Not a port number.");
    }

    return sb.toString();
  }
}
