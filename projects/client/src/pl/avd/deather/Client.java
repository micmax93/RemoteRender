package pl.avd.deather;

import pl.avd.deather.event.RequestButtonClickHandler;
import pl.avd.deather.socket.TimeRequest;
import pl.avd.deather.ui.main.MainForm;

public class Client {
  public static void main(String[] args) {
    final MainForm form = new MainForm("Simple client");

    form.setHandler(new RequestButtonClickHandler() {
      @Override
      public void onClick(String ip, String port) {
        TimeRequest r = new TimeRequest(ip, port);
        String response = null;
        response = r.getResponse();
        form.setTextAreaContent(response);
      }
    });
  }
}
