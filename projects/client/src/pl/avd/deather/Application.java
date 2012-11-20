package pl.avd.deather;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;
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

    frame.setRemoveHandler(new ObjectRemoveHandler() {
      @Override
      public void onRemove(int i) {
        storage.remove(i);
      }
    });

  }

  public void start() {

  }


  private void showCubeDialog() {
    CubeDialog dialog = new CubeDialog(new CubeDialogOkHandler() {
      @Override
      public void onOk(double x, double y, double z, double rX, double rY, double rZ, double angle, double r, double g, double b, double edge) {
        // create cube
        Cube cube = new Cube(
            new Vector3<Double>(x, y, z),
            new Vector4<Double>(rX, rY, rZ, angle),
            new Vector3<Integer>((int) r, (int) g, (int) b),
            edge
        );
        storage.add(cube);
        System.out.println(cube.info());
      }
    });
    dialog.setVisible(true);
  }

  private void showSphereDialog() {
    SphereDialog dialog = new SphereDialog(new SphereDialogOkHandler() {
      @Override
      public void onOk(double x, double y, double z, double rX, double rY, double rZ, double angle, double r, double g, double b, double radius) {
        // create sphere
        Sphere sphere = new Sphere(
            new Vector3<Double>(x, y, z),
            new Vector4<Double>(rX, rY, rZ, angle),
            new Vector3<Integer>((int) r, (int) g, (int) b),
            radius
        );
        storage.add(sphere);
        System.out.println(sphere.info());
      }
    });
    dialog.setVisible(true);
  }
}
