package pl.avd.deather;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;
import pl.avd.deather.net.RenderSocket;
import pl.avd.deather.object.Cube;
import pl.avd.deather.object.Sphere;
import pl.avd.deather.storage.ObjectStorage;
import pl.avd.deather.ui.dialog.CubeDialog;
import pl.avd.deather.ui.dialog.SphereDialog;
import pl.avd.deather.ui.handler.CubeDialogOkHandler;
import pl.avd.deather.ui.handler.MenuClickHandler;
import pl.avd.deather.ui.handler.ObjectRemoveHandler;
import pl.avd.deather.ui.handler.SphereDialogOkHandler;
import pl.avd.deather.ui.main.MainFrame;
import pl.avd.deather.xml.XmlHelper;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Application {

  private MainFrame frame;
  private ObjectStorage storage;

  public Application() {

    storage = new ObjectStorage();

    frame = new MainFrame("Remote render client", new MenuClickHandler() {
      @Override
      public void onClick(String value) {
        if (value.equals("CUBE")) {
          showCubeDialog();//To change body of created methods use File | Settings | File Templates.
        } else if (value.equals("SPHERE")) {
          showSphereDialog();
        }
        frame.drawObjects(storage.getObjects());
      }
    });

    frame.drawObjects(storage.getObjects());

    frame.setRemoveHandler(new ObjectRemoveHandler() {
      @Override
      public void onRemove(int i) {
        storage.remove(i);
      }
    });

    frame.addDrawClickHandler(new MainFrame.ClickHandler() {
      @Override
      public void onClick() {
        new Thread() {
          @Override
          public void run() {
            try {
              if (storage.getObjects().size() == 0) {
                throw new Exception("There must be at least one object.");
              } else if (storage.getObjects().size() > 10) {
                throw new Exception("There must be at most 10 objects.");
              }
              Vector3<Float> eye = frame.getCameraEye();
              Vector3<Float> lookAt = frame.getCameraLookAt();

              XmlHelper xml = new XmlHelper();
              String xmlText = xml.createXml(eye, lookAt, storage, frame.getImageWidth(), frame.getImageHeight(), frame.getQuality());
              System.out.println(xmlText);

              String host = frame.getHost();
              int port = frame.getPort();

              if (host.isEmpty() || port <= 0) {
                throw new Exception("Not a valid server.");
              }

              RenderSocket socket = new RenderSocket(host, port);
              socket.sendXml(xmlText);
              byte[] bytes = socket.getImageBytes();
              File tmpFile = File.createTempFile(getClass().getName(), null);
              FileOutputStream fos = new FileOutputStream(tmpFile);
              fos.write(bytes);
              fos.close();
              showImageDialog(tmpFile);
            } catch (Exception e) {
              JOptionPane.showMessageDialog(frame, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
              return;
            }

          }
        }.run();

      }
    });

  }

  private void showImageDialog(File imageFile) throws IOException {
    Icon icon = new ImageIcon(ImageIO.read(imageFile));
    JOptionPane.showMessageDialog(null, "", "Image", JOptionPane.INFORMATION_MESSAGE, icon);
  }

  public void start() {
  }


  private void showCubeDialog() {
    CubeDialog dialog = new CubeDialog(new CubeDialogOkHandler() {
      @Override
      public void onOk(double x, double y, double z, double rX, double rY, double rZ, double angle, String color, double edge) {

        Cube cube = new Cube(
            new Vector3<Double>(x, y, z),
            new Vector4<Double>(rX, rY, rZ, angle),
            color,
            edge
        );
        storage.add(cube);
      }
    });
    dialog.setVisible(true);
  }

  private void showSphereDialog() {
    SphereDialog dialog = new SphereDialog(new SphereDialogOkHandler() {
      @Override
      public void onOk(double x, double y, double z, double rX, double rY, double rZ, double angle, String color, double radius) {
        // create sphere
        Sphere sphere = new Sphere(
            new Vector3<Double>(x, y, z),
            new Vector4<Double>(rX, rY, rZ, angle),
            color,
            radius
        );
        storage.add(sphere);
        System.out.println(sphere.info());
      }
    });
    dialog.setVisible(true);
  }
}
