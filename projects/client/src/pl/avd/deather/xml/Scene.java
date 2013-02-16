package pl.avd.deather.xml;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "scene")
@XmlType(propOrder = {"properties", "objects", "camera"})
public class Scene {

  private Objects objects = new Objects();
  private Camera camera = new Camera();
  private Properties properties = new Properties();


  public Objects getObjects() {
    return objects;
  }

  public void setObjects(Objects objects) {
    this.objects = objects;
  }

  public Camera getCamera() {
    return camera;
  }

  public void setCamera(Camera camera) {
    this.camera = camera;
  }

  public Properties getProperties() {
    return properties;
  }

  public void setProperties(Properties properties) {
    this.properties = properties;
  }
}
